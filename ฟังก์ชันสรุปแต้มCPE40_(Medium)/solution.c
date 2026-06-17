#include <stdio.h>

int calculatePoints(int win, int draw)
{
    return win * 3 + draw;
}

int main()
{
    int n;
    int bestTeam = 1;
    int bestPoints = -1;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int win, draw, lose;
        scanf("%d %d %d", &win, &draw, &lose);
        (void)lose;

        int points = calculatePoints(win, draw);
        printf("Team %d: %d\n", i, points);

        if (points > bestPoints) {
            bestPoints = points;
            bestTeam = i;
        }
    }

    printf("Best Team: %d", bestTeam);
    return 0;
}
