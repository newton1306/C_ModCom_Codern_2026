# C_ModCom_Codern_2026

<!-- PROBLEM_COUNT_START -->
## Problem count

| Level | Count |
| --- | --- |
| Easy | 39 |
| Medium | 16 |
| Hard | 5 |
| **Total** | **60** |
<!-- PROBLEM_COUNT_END -->

## How to contribute

1. **Clone this repository**
   ```sh
   git clone https://github.com/newton1306/C_ModCom_Codern_2026.git
   cd C_ModCom_Codern_2026
   ```

2. **Go back to the main branch** **(Start from this step every time you continue working.)**
   - Always start from the latest `main` branch before working.

   ```sh
   git checkout main
   git pull origin main
   ```

3. **Choose the prepared branch for your problem level**
   - Do not create a new branch for each problem.
   - Use the prepared branch that matches the problem level.

   For Easy problems:

   ```sh
   git fetch origin
   git checkout problem-set/easy
   git pull origin problem-set/easy
   ```

   For Medium problems:

   ```sh
   git fetch origin
   git checkout problem-set/medium
   git pull origin problem-set/medium
   ```

   For Hard problems:

   ```sh
   git fetch origin
   git checkout problem-set/hard
   git pull origin problem-set/hard
   ```

4. **Add your problem set**
   - If you are already on the correct prepared branch and want to add another problem, start from this step.
   - Create a new folder at the repository root.
   - Folder names must use this format:

   ```text
   Problem_Name_(Level)
   ```

   Example folder names:

   ```text
   ค่าอาหารกลางวัน_(Easy)
   สรุปคะแนนสอบ_(Medium)
   ยอดขายร้านน้ำ_(Hard)
   ```

   Each problem folder must contain:
   - `Description.md`
   - `solution.c`
   - `Testcases/`

   Example folder structure:

   ```text
   Problem_Name_(Level)/
     Description.md
     solution.c
     Testcases/
       1in.txt
       1out.txt
       2in.txt
       2out.txt
   ```

5. **Check your changes**
   - Make sure only the files related to your work are changed.
   - Do not commit build files such as `.exe`.

   ```sh
   git status
   git diff
   ```

6. **Stage and commit your changes**
   - If you added one problem folder, stage that folder.

   Example only:

   ```sh
   git add "ค่าอาหารกลางวัน_(Easy)"
   git commit -m "Add easy lunch cost problem"
   ```

   If you changed multiple related files and already checked them carefully, you may stage all changes.

   ```sh
   git add .
   git commit -m "Update problem set"
   ```

7. **Push to the prepared branch**
   - Push to the same branch you worked on.

   For Easy problems:

   ```sh
   git push origin problem-set/easy
   ```

   For Medium problems:

   ```sh
   git push origin problem-set/medium
   ```

   For Hard problems:

   ```sh
   git push origin problem-set/hard
   ```

8. **Open a Pull Request**
   - Open GitHub.
   - Create a Pull Request from your prepared branch into `main`.
   Example: base `main`, compare `problem-set/easy`.
   - Write a short summary of what you added or changed.
   - Wait for review before merging.

--------------------------------------------------------------

## > If you already cloned this repository

Start from **Step 2: Go back to the main branch** every time you continue working.

## > If you are already on the correct prepared branch

Start from **Step 4: Add your problem set** when you want to add another problem.
