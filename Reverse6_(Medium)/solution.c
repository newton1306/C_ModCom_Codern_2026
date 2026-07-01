#include <stdio.h>

int main()
{
    int n;

    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        printf("%d", i * i);
        if (i < n) {
            printf(" ");
        }
    }

    return 0;
}
