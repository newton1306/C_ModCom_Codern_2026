#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LOG 20

typedef struct { int u, v, w, id, used; } Edge;
typedef struct { int to, w, next; } Arc;

static int cmp_edge(const void *a, const void *b) {
    const Edge *x = (const Edge *)a, *y = (const Edge *)b;
    if (x->w != y->w) return (x->w > y->w) - (x->w < y->w);
    return (x->id > y->id) - (x->id < y->id);
}

static int find(int *p, int x) {
    while (p[x] != x) { p[x] = p[p[x]]; x = p[x]; }
    return x;
}

static int max2(int a, int b) { return a > b ? a : b; }

int main(void) {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;
    Edge *e = (Edge *)malloc((size_t)m * sizeof(Edge));
    for (int i = 0; i < m; ++i) {
        scanf("%d %d %d", &e[i].u, &e[i].v, &e[i].w);
        e[i].id = i; e[i].used = 0;
    }
    qsort(e, m, sizeof(Edge), cmp_edge);

    int *dsu = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *sz = (int *)malloc(((size_t)n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) { dsu[i] = i; sz[i] = 1; }
    long long mst = 0;
    int chosen = 0;
    for (int i = 0; i < m; ++i) {
        int a = find(dsu, e[i].u), b = find(dsu, e[i].v);
        if (a == b) continue;
        if (sz[a] < sz[b]) { int t = a; a = b; b = t; }
        dsu[b] = a; sz[a] += sz[b];
        e[i].used = 1; mst += e[i].w; chosen++;
    }
    if (chosen != n - 1) { puts("-1 -1"); return 0; }

    int *head = (int *)malloc(((size_t)n + 1) * sizeof(int));
    Arc *arc = (Arc *)malloc((size_t)2 * (n - 1) * sizeof(Arc));
    for (int i = 1; i <= n; ++i) head[i] = -1;
    int ac = 0;
    for (int i = 0; i < m; ++i) if (e[i].used) {
        arc[ac] = (Arc){e[i].v, e[i].w, head[e[i].u]}; head[e[i].u] = ac++;
        arc[ac] = (Arc){e[i].u, e[i].w, head[e[i].v]}; head[e[i].v] = ac++;
    }

    int **up = (int **)malloc(LOG * sizeof(int *));
    int **mx = (int **)malloc(LOG * sizeof(int *));
    for (int j = 0; j < LOG; ++j) {
        up[j] = (int *)calloc((size_t)n + 1, sizeof(int));
        mx[j] = (int *)calloc((size_t)n + 1, sizeof(int));
    }
    int *depth = (int *)calloc((size_t)n + 1, sizeof(int));
    int *stack = (int *)malloc((size_t)n * sizeof(int));
    int top = 0; stack[top++] = 1; up[0][1] = 0;
    while (top) {
        int v = stack[--top];
        for (int a = head[v]; a != -1; a = arc[a].next) {
            int u = arc[a].to;
            if (u == up[0][v]) continue;
            up[0][u] = v; mx[0][u] = arc[a].w;
            depth[u] = depth[v] + 1; stack[top++] = u;
        }
    }
    for (int j = 1; j < LOG; ++j)
        for (int v = 1; v <= n; ++v) {
            up[j][v] = up[j - 1][up[j - 1][v]];
            mx[j][v] = max2(mx[j - 1][v], mx[j - 1][up[j - 1][v]]);
        }

    long long second = LLONG_MAX;
    for (int i = 0; i < m; ++i) if (!e[i].used) {
        int u = e[i].u, v = e[i].v, pathMax = 0;
        if (depth[u] < depth[v]) { int t = u; u = v; v = t; }
        int diff = depth[u] - depth[v];
        for (int j = LOG - 1; j >= 0; --j) if (diff & (1 << j)) {
            pathMax = max2(pathMax, mx[j][u]); u = up[j][u];
        }
        if (u != v) {
            for (int j = LOG - 1; j >= 0; --j) if (up[j][u] != up[j][v]) {
                pathMax = max2(pathMax, mx[j][u]);
                pathMax = max2(pathMax, mx[j][v]);
                u = up[j][u]; v = up[j][v];
            }
            pathMax = max2(pathMax, mx[0][u]);
            pathMax = max2(pathMax, mx[0][v]);
        }
        long long candidate = mst + (long long)e[i].w - pathMax;
        if (candidate < second) second = candidate;
    }
    if (second == LLONG_MAX) printf("%lld -1\n", mst);
    else printf("%lld %lld\n", mst, second);
    return 0;
}
