#include <stdio.h>

int main()
{
    int n, result;
    int attempts = 0;
    int goals = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &result);
        if (result == -1) {
            break;
        }
        attempts++;
        if (result == 1) {
            goals++;
        }
    }

    printf("Attempts: %d\n", attempts);
    printf("Goals: %d", goals);
    return 0;
}
