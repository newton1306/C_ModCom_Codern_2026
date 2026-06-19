#include <stdio.h>

int better_team(int x, int y, int points[], int gf[], int ga[])
{
    int gd_x = gf[x] - ga[x];
    int gd_y = gf[y] - ga[y];

    if (points[x] != points[y]) {
        return points[x] > points[y];
    }
    if (gd_x != gd_y) {
        return gd_x > gd_y;
    }
    if (gf[x] != gf[y]) {
        return gf[x] > gf[y];
    }
    return x < y;
}

int main()
{
    int n, m;
    int points[11] = {0};
    int gf[11] = {0};
    int ga[11] = {0};

    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b, score_a, score_b;
        scanf("%d %d %d %d", &a, &b, &score_a, &score_b);

        gf[a] += score_a;
        ga[a] += score_b;
        gf[b] += score_b;
        ga[b] += score_a;

        if (score_a > score_b) {
            points[a] += 3;
        } else if (score_b > score_a) {
            points[b] += 3;
        } else {
            points[a]++;
            points[b]++;
        }
    }

    int best = 1;
    for (int i = 2; i <= n; i++) {
        if (better_team(i, best, points, gf, ga)) {
            best = i;
        }
    }

    printf("Team %d\n", best);
    printf("Points: %d\n", points[best]);
    printf("GD: %d\n", gf[best] - ga[best]);
    printf("GF: %d", gf[best]);

    return 0;
}
