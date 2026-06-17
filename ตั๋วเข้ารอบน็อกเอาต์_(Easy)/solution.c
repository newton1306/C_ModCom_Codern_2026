#include <stdio.h>

int main()
{
    int p, g;
    scanf("%d", &p);
    scanf("%d", &g);

    if (p >= 6 || (p >= 4 && g > 0)) {
        printf("Advance");
    } else {
        printf("Eliminated");
    }

    return 0;
}
