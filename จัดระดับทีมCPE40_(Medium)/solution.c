#include <stdio.h>

int main()
{
    int points, goalDifference, goalFor;

    scanf("%d", &points);
    scanf("%d", &goalDifference);
    scanf("%d", &goalFor);

    if (points >= 7 && goalDifference >= 3) {
        printf("Status: Top Seed");
    } else if (points >= 4 && (goalDifference >= 0 || goalFor >= 4)) {
        printf("Status: Qualified");
    } else if (points >= 3) {
        printf("Status: Playoff");
    } else {
        printf("Status: Eliminated");
    }

    return 0;
}
