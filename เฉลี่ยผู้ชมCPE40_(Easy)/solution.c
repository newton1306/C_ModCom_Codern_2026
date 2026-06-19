#include <stdio.h>

int main()
{
    int matches, spectators;
    double hours;

    scanf("%d", &matches);
    scanf("%d", &spectators);
    scanf("%lf", &hours);

    printf("Per Match: %.2f\n", spectators / (double)matches);
    printf("Per Hour: %.2f", spectators / hours);
    return 0;
}
