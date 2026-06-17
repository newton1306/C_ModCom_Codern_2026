#include <stdio.h>

int main()
{
    int score[3][2];
    int totalGoals = 0;
    int ourWins = 0;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            scanf("%d", &score[i][j]);
            totalGoals += score[i][j];
        }

        if (score[i][0] > score[i][1]) {
            ourWins++;
        }
    }

    printf("Total Goals: %d\n", totalGoals);
    printf("Our Wins: %d", ourWins);
    return 0;
}
