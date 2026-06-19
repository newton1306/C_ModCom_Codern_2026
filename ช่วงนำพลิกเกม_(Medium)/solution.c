#include <stdio.h>

int absolute_value(int x)
{
    if (x < 0) {
        return -x;
    }
    return x;
}

int current_leader(int score1, int score2)
{
    if (score1 > score2) {
        return 1;
    }
    if (score2 > score1) {
        return 2;
    }
    return 0;
}

int main()
{
    int n;
    int score1 = 0;
    int score2 = 0;
    int last_leader = 0;
    int lead_changes = 0;
    int max_lead = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        int minute, team;
        scanf("%d %d", &minute, &team);
        (void)minute;

        if (team == 1) {
            score1++;
        } else {
            score2++;
        }

        int leader = current_leader(score1, score2);
        if (leader != 0) {
            if (last_leader != 0 && leader != last_leader) {
                lead_changes++;
            }
            last_leader = leader;
        }

        int lead = absolute_value(score1 - score2);
        if (lead > max_lead) {
            max_lead = lead;
        }
    }

    printf("Score: %d-%d\n", score1, score2);
    printf("Lead changes: %d\n", lead_changes);
    printf("Max lead: %d\n", max_lead);

    if (score1 > score2) {
        printf("Winner: Team 1");
    } else if (score2 > score1) {
        printf("Winner: Team 2");
    } else {
        printf("Winner: Tie");
    }

    return 0;
}
