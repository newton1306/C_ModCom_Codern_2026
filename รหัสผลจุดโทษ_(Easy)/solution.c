#include <stdio.h>

int main()
{
    int n;
    char a[101], b[101];
    scanf("%d", &n);
    scanf("%100s", a);
    scanf("%100s", b);

    int score_a = 0;
    int score_b = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] == 'O') {
            score_a++;
        }
        if (b[i] == 'O') {
            score_b++;
        }
    }

    printf("Team 1: %d\n", score_a);
    printf("Team 2: %d\n", score_b);

    if (score_a > score_b) {
        printf("Result: Team 1");
    } else if (score_b > score_a) {
        printf("Result: Team 2");
    } else {
        printf("Result: Tie");
    }

    return 0;
}
