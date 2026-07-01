#!/usr/bin/env python3
import argparse
import re
import sys
from pathlib import Path


PROBLEM_DIR_RE = re.compile(r".+_\((Easy|Medium|Hard)\)$")
LEVELS = ["Easy", "Medium", "Hard"]

START_MARKER = "<!-- PROBLEM_COUNT_START -->"
END_MARKER = "<!-- PROBLEM_COUNT_END -->"

if hasattr(sys.stdout, "reconfigure"):
    sys.stdout.reconfigure(encoding="utf-8")
if hasattr(sys.stderr, "reconfigure"):
    sys.stderr.reconfigure(encoding="utf-8")


def count_problems(root):
    counts = {level: 0 for level in LEVELS}
    for path in root.iterdir():
        if not path.is_dir() or path.name.startswith("."):
            continue
        if path.name in {"local-notes", "scripts"}:
            continue
        match = PROBLEM_DIR_RE.fullmatch(path.name)
        if match:
            counts[match.group(1)] += 1
    return counts


def render_table(counts):
    total = sum(counts.values())
    lines = [
        START_MARKER,
        "## Problem count",
        "",
        "| Level | Count |",
        "| --- | --- |",
    ]
    for level in LEVELS:
        lines.append(f"| {level} | {counts[level]} |")
    lines.append(f"| **Total** | **{total}** |")
    lines.append(END_MARKER)
    return "\n".join(lines)


def update_readme(readme_path, table):
    text = readme_path.read_text(encoding="utf-8")
    block_re = re.compile(
        re.escape(START_MARKER) + r".*?" + re.escape(END_MARKER),
        re.DOTALL,
    )
    if block_re.search(text):
        new_text = block_re.sub(table, text)
    else:
        h1_re = re.compile(r"^(# .*?)(\n)", re.MULTILINE)
        h1_match = h1_re.search(text)
        if h1_match:
            insert_at = h1_match.end()
            new_text = text[:insert_at] + "\n" + table + "\n" + text[insert_at:]
        else:
            new_text = table + "\n\n" + text
    if new_text != text:
        readme_path.write_text(new_text, encoding="utf-8")
        return True
    return False


def main():
    parser = argparse.ArgumentParser(description="Count problem sets per level and update README.")
    parser.add_argument("--root", default=".", help="Repository root")
    parser.add_argument("--check", action="store_true", help="Fail if README is out of date instead of writing")
    args = parser.parse_args()

    root = Path(args.root).resolve()
    counts = count_problems(root)
    total = sum(counts.values())

    for level in LEVELS:
        print(f"{level}: {counts[level]}")
    print(f"Total: {total}")

    table = render_table(counts)
    readme_path = root / "README.md"
    if not readme_path.exists():
        print("README.md not found.", file=sys.stderr)
        return 1

    if args.check:
        current = readme_path.read_text(encoding="utf-8")
        if table not in current:
            print("README problem count is out of date. Run scripts/count_problems.py.", file=sys.stderr)
            return 1
        print("README problem count is up to date.")
        return 0

    changed = update_readme(readme_path, table)
    print("README updated." if changed else "README already up to date.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
