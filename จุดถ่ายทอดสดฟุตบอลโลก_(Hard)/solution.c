#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define LOG 20

typedef struct { int *a, size, capacity; } Heap;

static int n;
static int *head, *to, *nextEdge;
static int *blocked, *centroidParent, *tmpParent, *subtree, *work, *order;
static int **up, *depth;
static Heap *added, *removed;

static void heap_push(Heap *h, int x) {
    if (h->size == h->capacity) {
        h->capacity = h->capacity ? h->capacity * 2 : 4;
        h->a = (int *)realloc(h->a, (size_t)h->capacity * sizeof(int));
    }
    int i = h->size++;
    while (i && h->a[(i - 1) / 2] > x) {
        h->a[i] = h->a[(i - 1) / 2]; i = (i - 1) / 2;
    }
    h->a[i] = x;
}

static void heap_pop(Heap *h) {
    int x = h->a[--h->size], i = 0;
    while (i * 2 + 1 < h->size) {
        int c = i * 2 + 1;
        if (c + 1 < h->size && h->a[c + 1] < h->a[c]) c++;
        if (h->a[c] >= x) break;
        h->a[i] = h->a[c]; i = c;
    }
    if (h->size) h->a[i] = x;
}

static void clean_heap(int c) {
    while (added[c].size && removed[c].size && added[c].a[0] == removed[c].a[0]) {
        heap_pop(&added[c]); heap_pop(&removed[c]);
    }
}

static void decompose(int start, int parentCentroid) {
    int top = 0, count = 0;
    work[top++] = start; tmpParent[start] = 0;
    while (top) {
        int v = work[--top]; order[count++] = v;
        for (int e = head[v]; e != -1; e = nextEdge[e]) {
            int u = to[e];
            if (blocked[u] || u == tmpParent[v]) continue;
            tmpParent[u] = v; work[top++] = u;
        }
    }
    for (int i = count - 1; i >= 0; --i) {
        int v = order[i]; subtree[v] = 1;
        for (int e = head[v]; e != -1; e = nextEdge[e]) {
            int u = to[e];
            if (!blocked[u] && tmpParent[u] == v) subtree[v] += subtree[u];
        }
    }
    int centroid = start, best = count + 1;
    for (int i = 0; i < count; ++i) {
        int v = order[i], largest = count - subtree[v];
        for (int e = head[v]; e != -1; e = nextEdge[e]) {
            int u = to[e];
            if (!blocked[u] && tmpParent[u] == v && subtree[u] > largest) largest = subtree[u];
        }
        if (largest < best) { best = largest; centroid = v; }
    }
    blocked[centroid] = 1;
    centroidParent[centroid] = parentCentroid;
    for (int e = head[centroid]; e != -1; e = nextEdge[e])
        if (!blocked[to[e]]) decompose(to[e], centroid);
}

static int lca(int a, int b) {
    if (depth[a] < depth[b]) { int t = a; a = b; b = t; }
    int diff = depth[a] - depth[b];
    for (int j = LOG - 1; j >= 0; --j) if (diff & (1 << j)) a = up[j][a];
    if (a == b) return a;
    for (int j = LOG - 1; j >= 0; --j) if (up[j][a] != up[j][b]) {
        a = up[j][a]; b = up[j][b];
    }
    return up[0][a];
}

static int distance_between(int a, int b) {
    int c = lca(a, b);
    return depth[a] + depth[b] - 2 * depth[c];
}

int main(void) {
    int q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    head = (int *)malloc(((size_t)n + 1) * sizeof(int));
    to = (int *)malloc(((size_t)2 * n + 1) * sizeof(int));
    nextEdge = (int *)malloc(((size_t)2 * n + 1) * sizeof(int));
    for (int i = 1; i <= n; ++i) head[i] = -1;
    int ec = 0;
    for (int i = 1; i < n; ++i) {
        int u, v; scanf("%d %d", &u, &v);
        to[ec] = v; nextEdge[ec] = head[u]; head[u] = ec++;
        to[ec] = u; nextEdge[ec] = head[v]; head[v] = ec++;
    }

    up = (int **)malloc(LOG * sizeof(int *));
    for (int j = 0; j < LOG; ++j) up[j] = (int *)calloc((size_t)n + 1, sizeof(int));
    depth = (int *)calloc((size_t)n + 1, sizeof(int));
    work = (int *)malloc((size_t)n * sizeof(int));
    int top = 0; work[top++] = 1;
    while (top) {
        int v = work[--top];
        for (int e = head[v]; e != -1; e = nextEdge[e]) {
            int u = to[e];
            if (u == up[0][v]) continue;
            up[0][u] = v; depth[u] = depth[v] + 1; work[top++] = u;
        }
    }
    for (int j = 1; j < LOG; ++j)
        for (int v = 1; v <= n; ++v) up[j][v] = up[j - 1][up[j - 1][v]];

    blocked = (int *)calloc((size_t)n + 1, sizeof(int));
    centroidParent = (int *)calloc((size_t)n + 1, sizeof(int));
    tmpParent = (int *)calloc((size_t)n + 1, sizeof(int));
    subtree = (int *)malloc(((size_t)n + 1) * sizeof(int));
    order = (int *)malloc((size_t)n * sizeof(int));
    decompose(1, 0);

    added = (Heap *)calloc((size_t)n + 1, sizeof(Heap));
    removed = (Heap *)calloc((size_t)n + 1, sizeof(Heap));
    int *active = (int *)calloc((size_t)n + 1, sizeof(int));
    while (q--) {
        char type; int u; scanf(" %c %d", &type, &u);
        if (type == 'T') {
            active[u] ^= 1;
            for (int c = u; c; c = centroidParent[c]) {
                int d = distance_between(u, c);
                if (active[u]) heap_push(&added[c], d); else heap_push(&removed[c], d);
            }
        } else {
            int answer = INT_MAX;
            for (int c = u; c; c = centroidParent[c]) {
                clean_heap(c);
                if (added[c].size) {
                    int candidate = distance_between(u, c) + added[c].a[0];
                    if (candidate < answer) answer = candidate;
                }
            }
            printf("%d\n", answer == INT_MAX ? -1 : answer);
        }
    }
    return 0;
}
