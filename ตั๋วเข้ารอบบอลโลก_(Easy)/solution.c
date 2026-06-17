#include <stdio.h>

int main()
{
    int points;

    scanf("%d", &points);

    if (points >= 4) {
        printf("Qualified");
    } else {
        printf("Try Again");
    }

    return 0;
}
