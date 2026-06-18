#include <stdio.h>

int main()
{
    int goals[4][3];
    int totals[4] = {0};
    int topTeam = 0;

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &goals[i][j]);
            totals[i] += goals[i][j];
        }
        if (totals[i] > totals[topTeam]) {
            topTeam = i;
        }
    }

    for (int i = 0; i < 4; i++) {
        printf("Team %d: %d\n", i + 1, totals[i]);
    }
    printf("Top Team: %d", topTeam + 1);
    return 0;
}
