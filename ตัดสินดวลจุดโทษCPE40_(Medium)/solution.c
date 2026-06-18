#include <stdio.h>

int main()
{
    int cpeScore, rivalScore, cpePenalty, rivalPenalty;

    scanf("%d %d", &cpeScore, &rivalScore);
    scanf("%d %d", &cpePenalty, &rivalPenalty);

    if (cpeScore > rivalScore) {
        printf("CPE 40 wins in regular time");
    } else if (cpeScore < rivalScore) {
        printf("CPE 40 loses in regular time");
    } else if (cpePenalty > rivalPenalty) {
        printf("CPE 40 wins on penalties");
    } else if (cpePenalty < rivalPenalty) {
        printf("CPE 40 loses on penalties");
    } else {
        printf("Sudden death needed");
    }

    return 0;
}
