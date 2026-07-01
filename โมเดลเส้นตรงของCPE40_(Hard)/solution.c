#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { long long m, b; } Line;
typedef struct { int type; long long a, b; } Operation;

static Line *lines;
static int *tree;
static long long *xs;

static int cmp_ll(const void *a, const void *b) {
    long long x = *(const long long *)a, y = *(const long long *)b;
    return (x > y) - (x < y);
}

static long long value(int id, long long x) {
    return lines[id].m * x + lines[id].b;
}

static void insert_line(int p, int l, int r, int id) {
    if (!tree[p]) { tree[p] = id; return; }
    int mid = (l + r) / 2;
    if (value(id, xs[mid]) < value(tree[p], xs[mid])) {
        int t = tree[p]; tree[p] = id; id = t;
    }
    if (l == r) return;
    if (value(id, xs[l]) < value(tree[p], xs[l]))
        insert_line(p * 2, l, mid, id);
    else if (value(id, xs[r]) < value(tree[p], xs[r]))
        insert_line(p * 2 + 1, mid + 1, r, id);
}

static long long query_tree(int p, int l, int r, int at) {
    long long best = tree[p] ? value(tree[p], xs[at]) : 9223372036854775807LL;
    if (l == r) return best;
    int mid = (l + r) / 2;
    long long other = at <= mid ? query_tree(p * 2, l, mid, at)
                                : query_tree(p * 2 + 1, mid + 1, r, at);
    return best < other ? best : other;
}

static int lower_bound_ll(long long *a, int n, long long x) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] < x) l = m + 1; else r = m;
    }
    return l;
}

int main(void) {
    int q;
    if (scanf("%d", &q) != 1) return 0;
    Operation *ops = (Operation *)malloc((size_t)q * sizeof(Operation));
    xs = (long long *)malloc((size_t)q * sizeof(long long));
    int xCount = 0;
    char command[8];
    for (int i = 0; i < q; ++i) {
        scanf("%s", command);
        if (command[0] == 'A') {
            ops[i].type = 1; scanf("%lld %lld", &ops[i].a, &ops[i].b);
        } else {
            ops[i].type = 2; scanf("%lld", &ops[i].a);
            xs[xCount++] = ops[i].a;
        }
    }
    qsort(xs, xCount, sizeof(long long), cmp_ll);
    int distinct = 0;
    for (int i = 0; i < xCount; ++i)
        if (!i || xs[i] != xs[i - 1]) xs[distinct++] = xs[i];

    lines = (Line *)calloc((size_t)q + 1, sizeof(Line));
    tree = (int *)calloc((size_t)4 * (distinct ? distinct : 1) + 8, sizeof(int));
    int lineCount = 0;
    for (int i = 0; i < q; ++i) {
        if (ops[i].type == 1) {
            lines[++lineCount] = (Line){ops[i].a, ops[i].b};
            if (distinct) insert_line(1, 0, distinct - 1, lineCount);
        } else if (!lineCount) {
            puts("EMPTY");
        } else {
            int at = lower_bound_ll(xs, distinct, ops[i].a);
            long long answer = query_tree(1, 0, distinct - 1, at);
            printf("%lld\n", answer);
        }
    }
    return 0;
}
