#include <stdio.h>

int main()
{
    int n, goal, total = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &goal);
        total += goal;
    }

    printf("Total Goals: %d", total);
    return 0;
}
