#include <stdio.h>

int main()
{
    int n, score;
    int pass = 0;
    int fail = 0;
    int total = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &score);
        total += score;

        if (score >= 50) {
            pass++;
        } else {
            fail++;
        }
    }

    printf("Pass: %d\n", pass);
    printf("Fail: %d\n", fail);
    printf("Average: %.2f", (float)total / n);

    return 0;
}

