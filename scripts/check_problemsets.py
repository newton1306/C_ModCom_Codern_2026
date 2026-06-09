#!/usr/bin/env python3
import argparse
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


PROBLEM_DIR_RE = re.compile(r".+_\((Easy|Medium|Hard)\)$")

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8")
if hasattr(sys.stderr, "reconfigure"):
    sys.stderr.reconfigure(encoding="utf-8")


def normalize_output(text):
    return text.replace("\r\n", "\n").rstrip()


def find_problem_dirs(root):
    return sorted(
        path
        for path in root.iterdir()
        if path.is_dir()
        and not path.name.startswith(".")
        and path.name not in {"local-notes", "scripts"}
        and PROBLEM_DIR_RE.fullmatch(path.name)
    )


def require_path(path, label, failures):
    if not path.exists():
        failures.append(f"{path.parent.name}: missing {label}")
        return False
    return True


def testcase_pairs(testcases_dir):
    inputs = {}
    outputs = {}

    for path in testcases_dir.iterdir():
        if path.is_file():
            in_match = re.fullmatch(r"(\d+)in\.txt", path.name)
            out_match = re.fullmatch(r"(\d+)out\.txt", path.name)

            if in_match:
                inputs[int(in_match.group(1))] = path
            elif out_match:
                outputs[int(out_match.group(1))] = path

    return inputs, outputs


def compile_solution(problem_dir, build_dir):
    exe_suffix = ".exe" if sys.platform.startswith("win") else ""
    executable = build_dir / f"solution{exe_suffix}"
    command = ["gcc", str(problem_dir / "solution.c"), "-std=c11", "-Wall", "-Wextra", "-O2", "-o", str(executable)]
    result = subprocess.run(command, capture_output=True, text=True)
    return result, executable


def run_testcase(executable, input_path):
    with input_path.open("rb") as input_file:
        return subprocess.run(
            [str(executable)],
            stdin=input_file,
            capture_output=True,
            text=True,
            timeout=5,
        )


def check_problem(problem_dir, build_dir):
    failures = []
    print(f"Checking {problem_dir.name}")

    has_description = require_path(problem_dir / "Description.md", "Description.md", failures)
    has_solution = require_path(problem_dir / "solution.c", "solution.c", failures)
    has_testcases = require_path(problem_dir / "Testcases", "Testcases/", failures)

    if not (has_description and has_solution and has_testcases):
        return failures

    testcases_dir = problem_dir / "Testcases"
    if not testcases_dir.is_dir():
        failures.append(f"{problem_dir.name}: Testcases is not a directory")
        return failures

    inputs, outputs = testcase_pairs(testcases_dir)
    if not inputs:
        failures.append(f"{problem_dir.name}: no input testcases found")
    if set(inputs) != set(outputs):
        missing_outputs = sorted(set(inputs) - set(outputs))
        missing_inputs = sorted(set(outputs) - set(inputs))
        if missing_outputs:
            failures.append(f"{problem_dir.name}: missing output files for cases {missing_outputs}")
        if missing_inputs:
            failures.append(f"{problem_dir.name}: missing input files for cases {missing_inputs}")

    if failures:
        return failures

    compile_result, executable = compile_solution(problem_dir, build_dir)
    if compile_result.returncode != 0:
        failures.append(
            f"{problem_dir.name}: compile failed\n"
            f"{compile_result.stdout}{compile_result.stderr}"
        )
        return failures

    for case_number in sorted(inputs):
        run_result = run_testcase(executable, inputs[case_number])
        expected = normalize_output(outputs[case_number].read_text(encoding="utf-8"))
        actual = normalize_output(run_result.stdout)

        if run_result.returncode != 0:
            failures.append(
                f"{problem_dir.name}: testcase {case_number} exited with code {run_result.returncode}\n"
                f"{run_result.stderr}"
            )
            continue

        if actual != expected:
            failures.append(
                f"{problem_dir.name}: testcase {case_number} output mismatch\n"
                f"Expected:\n{expected}\n"
                f"Actual:\n{actual}"
            )

    return failures


def main():
    parser = argparse.ArgumentParser(description="Compile and test C problem sets.")
    parser.add_argument("--root", default=".", help="Repository root")
    args = parser.parse_args()

    root = Path(args.root).resolve()
    if shutil.which("gcc") is None:
        print("gcc was not found. Install gcc before running this check.", file=sys.stderr)
        return 1

    problem_dirs = find_problem_dirs(root)
    if not problem_dirs:
        print("No problem directories found.", file=sys.stderr)
        return 1

    all_failures = []
    with tempfile.TemporaryDirectory(prefix="problemset_build_", dir=root) as temp_dir:
        build_dir = Path(temp_dir)
        for problem_dir in problem_dirs:
            all_failures.extend(check_problem(problem_dir, build_dir))

    if all_failures:
        print("\nProblem set check failed:\n", file=sys.stderr)
        for failure in all_failures:
            print(f"- {failure}\n", file=sys.stderr)
        return 1

    print(f"\nAll {len(problem_dirs)} problem set(s) passed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
