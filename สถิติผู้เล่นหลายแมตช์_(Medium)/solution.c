#include <stdio.h>

int better_player(int x, int y, int goals[], int active[])
{
    if (goals[x] != goals[y]) {
        return goals[x] > goals[y];
    }
    if (active[x] != active[y]) {
        return active[x] > active[y];
    }
    return x < y;
}

int main()
{
    int p, m, q;
    int goals[101] = {0};
    int active[101] = {0};

    scanf("%d %d %d", &p, &m, &q);

    for (int match = 0; match < m; match++) {
        for (int player = 1; player <= p; player++) {
            int value;
            scanf("%d", &value);
            goals[player] += value;
            if (value > 0) {
                active[player]++;
            }
        }
    }

    int top = 1;
    int qualified = 0;

    for (int player = 1; player <= p; player++) {
        if (better_player(player, top, goals, active)) {
            top = player;
        }
        if (goals[player] >= q) {
            qualified++;
        }
    }

    printf("Top: %d\n", top);
    printf("Goals: %d\n", goals[top]);
    printf("Active matches: %d\n", active[top]);
    printf("Qualified: %d", qualified);

    return 0;
}
