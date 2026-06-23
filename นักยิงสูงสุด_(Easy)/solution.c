#include <stdio.h>
#include <string.h>

int main(void) {
    int n;
    scanf("%d", &n);

    char best[64] = "";
    long best_goals = -1;

    for (int i = 0; i < n; i++) {
        char name[64];
        long goals;
        scanf("%63s %ld", name, &goals);

        if (goals > best_goals) {
            best_goals = goals;
            strcpy(best, name);
        }
    }

    printf("%s %ld\n", best, best_goals);
    return 0;
}
