#include <stdio.h>

int main()
{
    int scored, conceded;

    scanf("%d", &scored);
    scanf("%d", &conceded);

    printf("Goal Difference: %d\n", scored - conceded);
    printf("Total Goals: %d", scored + conceded);
    return 0;
}
