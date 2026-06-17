#include <stdio.h>

void printResult(char team1[], int score1, char team2[], int score2)
{
    if (score1 > score2) {
        printf("Winner: %s", team1);
    } else if (score2 > score1) {
        printf("Winner: %s", team2);
    } else {
        printf("Draw");
    }
}

int main()
{
    char team1[50], team2[50];
    int score1, score2;

    scanf("%49s %d", team1, &score1);
    scanf("%49s %d", team2, &score2);

    printResult(team1, score1, team2, score2);
    return 0;
}
