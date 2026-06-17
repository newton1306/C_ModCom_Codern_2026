#include <stdio.h>

int main()
{
    int win, draw, lose, goalFor, goalAgainst;

    scanf("%d %d %d", &win, &draw, &lose);
    scanf("%d %d", &goalFor, &goalAgainst);

    int played = win + draw + lose;
    int points = win * 3 + draw;
    int goalDifference = goalFor - goalAgainst;

    printf("Played: %d\n", played);
    printf("Points: %d\n", points);
    printf("Goal Difference: %d\n", goalDifference);
    printf("Ready: %s", (points >= 4 && goalDifference >= 0) ? "yes" : "no");
    return 0;
}
