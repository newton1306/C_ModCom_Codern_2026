#include <stdio.h>

int main()
{
    int win, draw, lose;

    scanf("%d", &win);
    scanf("%d", &draw);
    scanf("%d", &lose);
    (void)lose;

    printf("Points: %d", win * 3 + draw);
    return 0;
}
