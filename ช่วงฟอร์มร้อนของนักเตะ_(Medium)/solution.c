#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);

    int streak = 0;
    int is_hot = 0;

    for (int i = 0; i < n; i++) {
        int result;
        scanf("%d", &result);

        if (result == 1) {
            streak++;
            if (streak >= k) {
                is_hot = 1;
            }
        } else {
            streak = 0;
        }
    }

    if (is_hot) {
        printf("HOT");
    } else {
        printf("NORMAL");
    }

    return 0;
}

