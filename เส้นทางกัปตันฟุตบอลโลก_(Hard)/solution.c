#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int max2(int a, int b) { return a > b ? a : b; }

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    int *value = (int *)malloc(((size_t)n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) scanf("%d", &value[i]);

    int *head = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *to = (int *)malloc(((size_t)2 * n + 1) * sizeof(int));
    int *next = (int *)malloc(((size_t)2 * n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) head[i] = -1;
    int edges = 0;
    for (int i = 1; i < n; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        to[edges] = v; next[edges] = head[u]; head[u] = edges++;
        to[edges] = u; next[edges] = head[v]; head[v] = edges++;
    }

    int *parent = (int *)calloc((size_t)n + 1, sizeof(int));
    int *depth = (int *)calloc((size_t)n + 1, sizeof(int));
    int *order = (int *)malloc((size_t)n * sizeof(int));
    int *stack = (int *)malloc((size_t)n * sizeof(int));
    int top = 0, count = 0;
    stack[top++] = 1;
    while (top) {
        int v = stack[--top];
        order[count++] = v;
        for (int e = head[v]; e != -1; e = next[e]) {
            int u = to[e];
            if (u == parent[v]) continue;
            parent[u] = v; depth[u] = depth[v] + 1; stack[top++] = u;
        }
    }

    int *size = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *heavy = (int *)malloc(((size_t)n + 1) * sizeof(int));
    for (int i = n - 1; i >= 0; --i) {
        int v = order[i]; size[v] = 1; heavy[v] = 0;
        for (int e = head[v]; e != -1; e = next[e]) {
            int u = to[e];
            if (parent[u] == v) {
                size[v] += size[u];
                if (!heavy[v] || size[u] > size[heavy[v]]) heavy[v] = u;
            }
        }
    }

    int *chainHead = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *pos = (int *)malloc(((size_t)n + 1) * sizeof(int));
    int *startNode = (int *)malloc((size_t)n * sizeof(int));
    int *startHead = (int *)malloc((size_t)n * sizeof(int));
    top = 0; startNode[top] = 1; startHead[top++] = 1;
    int timer = 0;
    while (top) {
        --top;
        int v = startNode[top], h = startHead[top];
        while (v) {
            chainHead[v] = h; pos[v] = timer++;
            for (int e = head[v]; e != -1; e = next[e]) {
                int u = to[e];
                if (parent[u] == v && u != heavy[v]) {
                    startNode[top] = u; startHead[top++] = u;
                }
            }
            v = heavy[v];
        }
    }

    int base = 1;
    while (base < n) base *= 2;
    int *seg = (int *)malloc((size_t)2 * base * sizeof(int));
    for (int i = 0; i < 2 * base; ++i) seg[i] = INT_MIN;
    for (int v = 1; v <= n; ++v) seg[base + pos[v]] = value[v];
    for (int i = base - 1; i; --i) seg[i] = max2(seg[i * 2], seg[i * 2 + 1]);

    while (q--) {
        char type; int u, x;
        scanf(" %c %d %d", &type, &u, &x);
        if (type == 'U') {
            int p = base + pos[u]; seg[p] = x;
            for (p /= 2; p; p /= 2) seg[p] = max2(seg[p * 2], seg[p * 2 + 1]);
        } else {
            int v = x, answer = INT_MIN;
            while (chainHead[u] != chainHead[v]) {
                if (depth[chainHead[u]] < depth[chainHead[v]]) { int t = u; u = v; v = t; }
                int l = base + pos[chainHead[u]], r = base + pos[u];
                while (l <= r) {
                    if (l & 1) answer = max2(answer, seg[l++]);
                    if (!(r & 1)) answer = max2(answer, seg[r--]);
                    l /= 2; r /= 2;
                }
                u = parent[chainHead[u]];
            }
            if (pos[u] > pos[v]) { int t = u; u = v; v = t; }
            int l = base + pos[u], r = base + pos[v];
            while (l <= r) {
                if (l & 1) answer = max2(answer, seg[l++]);
                if (!(r & 1)) answer = max2(answer, seg[r--]);
                l /= 2; r /= 2;
            }
            printf("%d\n", answer);
        }
    }
    return 0;
}
