#include <stdio.h>

int main()
{
    int n, c;
    scanf("%d", &n);
    scanf("%d", &c);

    printf("%d", (n + c - 1) / c);
    return 0;
}

