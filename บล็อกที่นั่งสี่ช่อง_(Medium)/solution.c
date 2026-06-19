#include <stdio.h>

int main()
{
    int r, c;
    char grid[100][101];
    scanf("%d %d", &r, &c);

    for (int i = 0; i < r; i++) {
        scanf("%100s", grid[i]);
    }

    int blocks = 0;
    for (int i = 0; i + 1 < r; i++) {
        for (int j = 0; j + 1 < c; j++) {
            if (grid[i][j] == '.' && grid[i][j + 1] == '.' &&
                grid[i + 1][j] == '.' && grid[i + 1][j + 1] == '.') {
                blocks++;
            }
        }
    }

    int best_row = 1;
    int best_empty = -1;
    int longest = 0;

    for (int i = 0; i < r; i++) {
        int empty = 0;
        int current = 0;

        for (int j = 0; j < c; j++) {
            if (grid[i][j] == '.') {
                empty++;
                current++;
                if (current > longest) {
                    longest = current;
                }
            } else {
                current = 0;
            }
        }

        if (empty > best_empty) {
            best_empty = empty;
            best_row = i + 1;
        }
    }

    printf("Blocks: %d\n", blocks);
    printf("Row: %d\n", best_row);
    printf("Longest: %d", longest);

    return 0;
}
