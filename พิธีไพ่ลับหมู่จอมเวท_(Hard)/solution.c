#include <stdio.h>

int seen[200010];

static long long mod_norm(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

int main(void) {
    int K, N;
    scanf("%d %d", &K, &N);

    long long M = 1LL * K * N + 1;
    long long my_sum = 0;

    for (int i = 0; i < N; i++) {
        int card;
        scanf("%d", &card);
        my_sum += card;
        seen[card] = 1;
    }

    int invalid = 0;
    long long code_sum = 0;

    for (int i = 0; i < K - 1; i++) {
        long long x, y;
        scanf("%lld %lld", &x, &y);

        if (x < 1 || x > M || y < 1 || y > M) {
            invalid = 1;
        } else {
            if (x == y) invalid = 1;
            if (seen[x] || seen[y]) invalid = 1;
            seen[x] = 1;
            seen[y] = 1;
        }

        code_sum = (code_sum + mod_norm(x, M) + mod_norm(y, M)) % M;
    }

    long long total = M * (M + 1) / 2;
    long long secret = mod_norm(total - my_sum - code_sum, M);
    if (secret == 0) secret = M;

    if (seen[secret]) invalid = 1;

    if (invalid) {
        printf("INVALID\n");
    } else {
        printf("SECRET %lld\n", secret);
    }

    return 0;
}
