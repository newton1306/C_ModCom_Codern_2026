#include <stdio.h>

int main() {
    int x;
    int position = 1;
    int odd_sum = 0;
    int even_sum = 0;

    while (scanf("%d", &x) == 1 && x != 0) {
        if (position % 2 == 1) {
            odd_sum += x;
        } else {
            even_sum += x;
        }
        position++;
    }

    if ((odd_sum - even_sum) % 11 == 0) {
        printf("OPEN");
    } else {
        printf("LOCKED");
    }

    return 0;
}

