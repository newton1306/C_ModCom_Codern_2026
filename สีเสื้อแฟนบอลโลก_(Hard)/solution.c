#include <stdio.h>
#include <stdlib.h>

typedef struct { char type; int u, x; } Operation;
typedef struct { int node, oldColor, newColor; } Modification;
typedef struct { int l, r, time, index; } Query;

static Query *queries;
static int blockSize;

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

static int lower_bound_int(int *a, int n, int x) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] < x) l = m + 1; else r = m;
    }
    return l;
}

static int cmp_query(const void *a, const void *b) {
    const Query *x = (const Query *)a, *y = (const Query *)b;
    int bx = x->l / blockSize, by = y->l / blockSize;
    if (bx != by) return bx - by;
    int rx = x->r / blockSize, ry = y->r / blockSize;
    if (rx != ry) return (bx & 1) ? ry - rx : rx - ry;
    return (rx & 1) ? y->time - x->time : x->time - y->time;
}

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    int *initialRaw = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *all = (int *)malloc(((size_t)n + q + 1) * sizeof(int));
    int allCount = 0;
    for (int i = 1; i <= n; ++i) { scanf("%d", &initialRaw[i]); all[allCount++] = initialRaw[i]; }

    int *head = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *to = (int *)malloc(((size_t)2 * n + 1) * sizeof(int));
    int *next = (int *)malloc(((size_t)2 * n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) head[i] = -1;
    int edgeCount = 0;
    for (int i = 1; i < n; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        to[edgeCount] = v; next[edgeCount] = head[u]; head[u] = edgeCount++;
        to[edgeCount] = u; next[edgeCount] = head[v]; head[v] = edgeCount++;
    }

    int *tin = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *tout = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *euler = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *parent = (int *)calloc((size_t)n + 1, sizeof(int));
    int *events = (int *)malloc((size_t)2 * n * sizeof(int));
    int top = 0, timer = 0; events[top++] = 1;
    while (top) {
        int event = events[--top];
        if (event > 0) {
            int v = event;
            tin[v] = ++timer; euler[timer] = v;
            events[top++] = -v;
            for (int e = head[v]; e != -1; e = next[e]) {
                int u = to[e];
                if (u == parent[v]) continue;
                parent[u] = v; events[top++] = u;
            }
        } else {
            tout[-event] = timer;
        }
    }

    Operation *ops = (Operation *)malloc((size_t)q * sizeof(Operation));
    for (int i = 0; i < q; ++i) {
        scanf(" %c %d", &ops[i].type, &ops[i].u);
        if (ops[i].type == 'C') {
            scanf("%d", &ops[i].x);
            all[allCount++] = ops[i].x;
        } else ops[i].x = 0;
    }
    qsort(all, allCount, sizeof(int), cmp_int);
    int colors = 0;
    for (int i = 0; i < allCount; ++i)
        if (!i || all[i] != all[i - 1]) all[colors++] = all[i];

    int *initial = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *temp = (int *)malloc(((size_t)n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i)
        initial[i] = temp[i] = lower_bound_int(all, colors, initialRaw[i]);

    Modification *mods = (Modification *)malloc(((size_t)q + 1) * sizeof(Modification));
    queries = (Query *)malloc((size_t)q * sizeof(Query));
    int modCount = 0, queryCount = 0;
    for (int i = 0; i < q; ++i) {
        if (ops[i].type == 'C') {
            int node = ops[i].u;
            int nc = lower_bound_int(all, colors, ops[i].x);
            mods[++modCount] = (Modification){node, temp[node], nc};
            temp[node] = nc;
        } else {
            int node = ops[i].u;
            queries[queryCount] = (Query){tin[node], tout[node], modCount, queryCount};
            queryCount++;
        }
    }

    blockSize = 1;
    while ((long long)blockSize * blockSize * blockSize < (long long)n * n) blockSize++;
    qsort(queries, queryCount, sizeof(Query), cmp_query);

    int *current = (int *)malloc(((size_t)n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) current[i] = initial[i];
    int *frequency = (int *)calloc((size_t)colors, sizeof(int));
    int *answer = (int *)malloc((size_t)queryCount * sizeof(int));
    int curL = 1, curR = 0, curT = 0, distinct = 0;

#define ADD_POS(P) do { int cc = current[euler[(P)]]; if (frequency[cc]++ == 0) distinct++; } while (0)
#define REMOVE_POS(P) do { int cc = current[euler[(P)]]; if (--frequency[cc] == 0) distinct--; } while (0)

    for (int qi = 0; qi < queryCount; ++qi) {
        Query qu = queries[qi];
        while (curT < qu.time) {
            Modification md = mods[++curT]; int p = tin[md.node];
            if (curL <= p && p <= curR) { REMOVE_POS(p); current[md.node] = md.newColor; ADD_POS(p); }
            else current[md.node] = md.newColor;
        }
        while (curT > qu.time) {
            Modification md = mods[curT--]; int p = tin[md.node];
            if (curL <= p && p <= curR) { REMOVE_POS(p); current[md.node] = md.oldColor; ADD_POS(p); }
            else current[md.node] = md.oldColor;
        }
        while (curL > qu.l) ADD_POS(--curL);
        while (curR < qu.r) ADD_POS(++curR);
        while (curL < qu.l) { REMOVE_POS(curL); curL++; }
        while (curR > qu.r) { REMOVE_POS(curR); curR--; }
        answer[qu.index] = distinct;
    }
    for (int i = 0; i < queryCount; ++i) printf("%d\n", answer[i]);
    return 0;
}
