#include <stdio.h>

int main()
{
    int r, c, k;
    char row[101];
    scanf("%d %d %d", &r, &c, &k);

    int valid_rows = 0;
    int longest = 0;

    for (int i = 0; i < r; i++) {
        scanf("%100s", row);

        int current = 0;
        int row_best = 0;

        for (int j = 0; j < c; j++) {
            if (row[j] == '.') {
                current++;
                if (current > row_best) {
                    row_best = current;
                }
                if (current > longest) {
                    longest = current;
                }
            } else {
                current = 0;
            }
        }

        if (row_best >= k) {
            valid_rows++;
        }
    }

    printf("Rows: %d\n", valid_rows);
    printf("Longest: %d", longest);

    return 0;
}
