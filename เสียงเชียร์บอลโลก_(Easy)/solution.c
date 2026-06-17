#include <stdio.h>

int main()
{
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Goal!");
        if (i < n - 1) {
            printf("\n");
        }
    }

    return 0;
}
