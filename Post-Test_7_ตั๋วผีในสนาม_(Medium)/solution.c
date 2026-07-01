#include <stdio.h>

#define MAX 100005

int diff[MAX + 1];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);

        diff[a]++;
        diff[b + 1]--;
    }

    int current = 0;
    int answer = 0;

    for (int i = 1; i <= n; i++) {
        current += diff[i];
        if (current > 1) {
            answer++;
        }
    }

    printf("%d", answer);

    return 0;
}

