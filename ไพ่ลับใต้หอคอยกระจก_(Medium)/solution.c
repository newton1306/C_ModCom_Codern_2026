#include <stdio.h>

int in_my_hand[200005];

static long long mod_norm(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

int main(void) {
    int N;
    if (scanf("%d", &N) != 1) return 0;

    long long M = 2LL * N + 1;
    long long my_sum = 0;

    for (int i = 0; i < N; i++) {
        int card;
        scanf("%d", &card);
        my_sum += card;
        in_my_hand[card] = 1;
    }

    long long x, y;
    scanf("%lld %lld", &x, &y);

    int invalid = 0;

    if (x < 1 || x > M || y < 1 || y > M) invalid = 1;
    if (x == y) invalid = 1;

    if (!invalid) {
        if (in_my_hand[x] || in_my_hand[y]) invalid = 1;
    }

    long long total = M * (M + 1) / 2;
    long long code = (mod_norm(x, M) + mod_norm(y, M)) % M;
    long long secret = mod_norm(total - my_sum - code, M);
    if (secret == 0) secret = M;

    if (!invalid) {
        if (in_my_hand[secret]) invalid = 1;
        if (secret == x || secret == y) invalid = 1;
    }

    if (invalid) {
        printf("INVALID\n");
    } else {
        printf("SECRET %lld\n", secret);
    }

    return 0;
}
