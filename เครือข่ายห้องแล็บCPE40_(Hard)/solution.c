#include <stdio.h>
#include <stdlib.h>

typedef struct { int u, v, next; } Link;

static int *head, *parent_, *size_, *stkChild, *stkRoot, *stkOld;
static Link *links;
static int linkCount = 0, linkCap = 0, stackTop = 0;
static char *op;
static int *oa, *ob;

static void add_link(int node, int u, int v) {
    if (linkCount + 1 >= linkCap) {
        linkCap = linkCap ? linkCap * 2 : 1024;
        links = (Link *)realloc(links, (size_t)linkCap * sizeof(Link));
    }
    ++linkCount;
    links[linkCount].u = u;
    links[linkCount].v = v;
    links[linkCount].next = head[node];
    head[node] = linkCount;
}

static void add_interval(int node, int l, int r, int ql, int qr, int u, int v) {
    if (ql <= l && r <= qr) {
        add_link(node, u, v);
        return;
    }
    int mid = (l + r) / 2;
    if (ql <= mid) add_interval(node * 2, l, mid, ql, qr, u, v);
    if (qr > mid) add_interval(node * 2 + 1, mid + 1, r, ql, qr, u, v);
}

static int find_root(int x) {
    while (parent_[x] != x) x = parent_[x];
    return x;
}

static void unite(int a, int b) {
    a = find_root(a);
    b = find_root(b);
    if (a == b) return;
    if (size_[a] < size_[b]) { int t = a; a = b; b = t; }
    stkChild[stackTop] = b;
    stkRoot[stackTop] = a;
    stkOld[stackTop++] = size_[a];
    parent_[b] = a;
    size_[a] += size_[b];
}

static void rollback(int snapshot) {
    while (stackTop > snapshot) {
        --stackTop;
        int b = stkChild[stackTop];
        int a = stkRoot[stackTop];
        parent_[b] = b;
        size_[a] = stkOld[stackTop];
    }
}

static void solve_time(int node, int l, int r) {
    int snapshot = stackTop;
    for (int e = head[node]; e; e = links[e].next)
        unite(links[e].u, links[e].v);

    if (l == r) {
        if (op[l] == '?')
            puts(find_root(oa[l]) == find_root(ob[l]) ? "YES" : "NO");
    } else {
        int mid = (l + r) / 2;
        solve_time(node * 2, l, mid);
        solve_time(node * 2 + 1, mid + 1, r);
    }
    rollback(snapshot);
}

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;

    op = (char *)calloc((size_t)q + 1, sizeof(char));
    oa = (int *)calloc((size_t)q + 1, sizeof(int));
    ob = (int *)calloc((size_t)q + 1, sizeof(int));
    int *eu = (int *)calloc((size_t)q + 1, sizeof(int));
    int *ev = (int *)calloc((size_t)q + 1, sizeof(int));
    int *begin = (int *)calloc((size_t)q + 1, sizeof(int));
    int *finish = (int *)calloc((size_t)q + 1, sizeof(int));
    int edgeCount = 0;

    for (int t = 1; t <= q; ++t) {
        scanf(" %c", &op[t]);
        if (op[t] == '+') {
            scanf("%d %d", &oa[t], &ob[t]);
            ++edgeCount;
            eu[edgeCount] = oa[t]; ev[edgeCount] = ob[t]; begin[edgeCount] = t;
        } else if (op[t] == '-') {
            scanf("%d", &oa[t]);
            finish[oa[t]] = t - 1;
        } else {
            scanf("%d %d", &oa[t], &ob[t]);
        }
    }

    head = (int *)calloc((size_t)4 * q + 8, sizeof(int));
    for (int id = 1; id <= edgeCount; ++id) {
        int end = finish[id] ? finish[id] : q;
        if (begin[id] <= end)
            add_interval(1, 1, q, begin[id], end, eu[id], ev[id]);
    }

    parent_ = (int *)malloc(((size_t)n + 1) * sizeof(int));
    size_ = (int *)malloc(((size_t)n + 1) * sizeof(int));
    stkChild = (int *)malloc(((size_t)n + q + 5) * sizeof(int));
    stkRoot = (int *)malloc(((size_t)n + q + 5) * sizeof(int));
    stkOld = (int *)malloc(((size_t)n + q + 5) * sizeof(int));
    for (int i = 1; i <= n; ++i) { parent_[i] = i; size_[i] = 1; }

    solve_time(1, 1, q);
    return 0;
}
