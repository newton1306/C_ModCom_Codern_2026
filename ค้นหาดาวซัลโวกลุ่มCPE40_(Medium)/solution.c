#include <stdio.h>

int main()
{
    int n;
    int goals[20];
    int topGoals = 0;
    int topPlayers = 0;

    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &goals[i]);
        if (i == 0 || goals[i] > topGoals) {
            topGoals = goals[i];
            topPlayers = 1;
        } else if (goals[i] == topGoals) {
            topPlayers++;
        }
    }

    printf("Top Goals: %d\n", topGoals);
    printf("Top Players: %d", topPlayers);
    return 0;
}
