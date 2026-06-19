#include <stdio.h>

int main()
{
    int totalMinutes, stoppage;

    scanf("%d", &totalMinutes);
    scanf("%d", &stoppage);

    int matchMinutes = 90 + stoppage;

    printf("Full Matches: %d\n", totalMinutes / matchMinutes);
    printf("Remaining Minutes: %d", totalMinutes % matchMinutes);
    return 0;
}
