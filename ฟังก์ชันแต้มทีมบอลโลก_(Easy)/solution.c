#include <stdio.h>

int calculatePoints(int win, int draw)
{
    return win * 3 + draw;
}

int main()
{
    int win, draw;

    scanf("%d", &win);
    scanf("%d", &draw);

    printf("Points: %d", calculatePoints(win, draw));
    return 0;
}
