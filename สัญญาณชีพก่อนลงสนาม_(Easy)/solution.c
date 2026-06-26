#include <stdio.h>

int absolute(int x) {
    if (x < 0) {
        return -x;
    }
    return x;
}

int main() {
    int x;
    int max_value = 0;
    int first = 1;

    while (scanf("%d", &x) == 1 && x != 999) {
        int value = absolute(x);

        if (!first) {
            printf(" ");
        }
        printf("%d", value);
        first = 0;

        if (value > max_value) {
            max_value = value;
        }
    }

    printf("\nMax: %d", max_value);

    return 0;
}
