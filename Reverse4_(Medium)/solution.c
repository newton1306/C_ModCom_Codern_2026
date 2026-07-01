#include <stdio.h>

int main()
{
    int n, sum = 0;

    scanf("%d", &n);
    if (n == 0) {
        printf("0");
        return 0;
    }

    while (n > 0) {
        sum += n % 10;
        n /= 10;
    }

    printf("%d", sum);

    return 0;
}
