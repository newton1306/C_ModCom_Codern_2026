#include <stdio.h>

int prefix[100005][21];

int main() {
    int N, K, Q;
    scanf("%d %d %d", &N, &K, &Q);

    for (int i = 1; i <= N; i++) {
        int species;
        scanf("%d", &species);

        for (int j = 1; j <= K; j++) {
            prefix[i][j] = prefix[i - 1][j];
        }

        prefix[i][species]++;
    }

    for (int q = 0; q < Q; q++) {
        int L, R;
        scanf("%d %d", &L, &R);

        for (int j = 1; j <= K; j++) {
            if (j > 1) {
                printf(" ");
            }
            printf("%d", prefix[R][j] - prefix[L - 1][j]);
        }

        if (q < Q - 1) {
            printf("\n");
        }
    }

    return 0;
}
