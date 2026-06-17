#include <stdio.h>

int main()
{
    int shirt;
    char position;
    float rating;

    scanf("%d", &shirt);
    scanf(" %c", &position);
    scanf("%f", &rating);

    printf("Player: %d\n", shirt);
    printf("Position: %c\n", position);
    printf("Rating: %.1f", rating);
    return 0;
}
