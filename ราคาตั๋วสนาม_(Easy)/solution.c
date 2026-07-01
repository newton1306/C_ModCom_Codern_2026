#include <stdio.h>

int main(void) {
    long long total = 0;
    for (int i = 0; i < 3; i++) {
        long long price, qty;
        scanf("%lld %lld", &price, &qty);
        total += price * qty;
    }
    printf("%lld\n", total);
    return 0;
}
