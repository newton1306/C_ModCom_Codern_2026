#include <stdio.h>

int sumProperDivisors(int x)
{
    if (x == 1) {
        return 0;
    }

    int sum = 1;

    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) {
            sum += i;

            if (i != x / i) {
                sum += x / i;
            }
        }
    }

    return sum;
}

int classifyNumber(int x, int sum)
{
    if (sum == x) {
        return 1;
    }

    if (sum > x) {
        return 2;
    }

    return 3;
}

int main()
{
    int n;
    int perfect = 0;
    int abundant = 0;
    int deficient = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int x;
        scanf("%d", &x);

        int sum = sumProperDivisors(x);
        int type = classifyNumber(x, sum);

        if (type == 1) {
            perfect++;
            printf("%d %d PERFECT\n", x, sum);
        } else if (type == 2) {
            abundant++;
            printf("%d %d ABUNDANT\n", x, sum);
        } else {
            deficient++;
            printf("%d %d DEFICIENT\n", x, sum);
        }
    }

    printf("Perfect: %d\n", perfect);
    printf("Abundant: %d\n", abundant);
    printf("Deficient: %d", deficient);

    return 0;
}

