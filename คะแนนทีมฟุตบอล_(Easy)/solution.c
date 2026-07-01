#include <stdio.h>

int main(void) {
    long w, d, l;
    scanf("%ld %ld %ld", &w, &d, &l);
    long points = 3 * w + d;
    long games = w + d + l;
    printf("%.2f\n", (double)points / games);
    return 0;
}
