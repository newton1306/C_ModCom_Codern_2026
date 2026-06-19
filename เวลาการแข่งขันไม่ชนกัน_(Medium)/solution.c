#include <stdio.h>

int main()
{
    int n;
    int start[100], end[100];
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &start[i], &end[i]);
    }

    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (start[i] < end[j] && start[j] < end[i]) {
                count++;
            }
        }
    }

    printf("%d", count);
    return 0;
}
