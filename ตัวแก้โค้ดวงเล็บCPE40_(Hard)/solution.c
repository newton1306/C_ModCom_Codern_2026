#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int sum, minPrefix, maxPrefix, length, lazy; } Node;
static Node *tree;
static char *s;

static int min2(int a, int b) { return a < b ? a : b; }
static int max2(int a, int b) { return a > b ? a : b; }

static Node combine(Node a, Node b) {
    if (!a.length) return b;
    if (!b.length) return a;
    Node c;
    c.sum = a.sum + b.sum;
    c.minPrefix = min2(a.minPrefix, a.sum + b.minPrefix);
    c.maxPrefix = max2(a.maxPrefix, a.sum + b.maxPrefix);
    c.length = a.length + b.length;
    c.lazy = 0;
    return c;
}

static void apply_flip(int p) {
    int oldMin = tree[p].minPrefix;
    tree[p].sum = -tree[p].sum;
    tree[p].minPrefix = -tree[p].maxPrefix;
    tree[p].maxPrefix = -oldMin;
    tree[p].lazy ^= 1;
}

static void push(int p) {
    if (tree[p].lazy) {
        apply_flip(p * 2); apply_flip(p * 2 + 1);
        tree[p].lazy = 0;
    }
}

static void build(int p, int l, int r) {
    if (l == r) {
        int v = s[l - 1] == '(' ? 1 : -1;
        tree[p] = (Node){v, v, v, 1, 0};
        return;
    }
    int m = (l + r) / 2;
    build(p * 2, l, m); build(p * 2 + 1, m + 1, r);
    tree[p] = combine(tree[p * 2], tree[p * 2 + 1]);
}

static void flip_range(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) { apply_flip(p); return; }
    push(p);
    int m = (l + r) / 2;
    if (ql <= m) flip_range(p * 2, l, m, ql, qr);
    if (qr > m) flip_range(p * 2 + 1, m + 1, r, ql, qr);
    tree[p] = combine(tree[p * 2], tree[p * 2 + 1]);
}

static Node query(int p, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return tree[p];
    push(p);
    int m = (l + r) / 2;
    if (qr <= m) return query(p * 2, l, m, ql, qr);
    if (ql > m) return query(p * 2 + 1, m + 1, r, ql, qr);
    return combine(query(p * 2, l, m, ql, qr),
                   query(p * 2 + 1, m + 1, r, ql, qr));
}

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    s = (char *)malloc((size_t)n + 1);
    scanf("%s", s);
    tree = (Node *)calloc((size_t)4 * n + 8, sizeof(Node));
    build(1, 1, n);
    while (q--) {
        char type; int l, r;
        scanf(" %c %d %d", &type, &l, &r);
        if (type == 'F') flip_range(1, 1, n, l, r);
        else {
            Node ans = query(1, 1, n, l, r);
            puts(ans.sum == 0 && ans.minPrefix >= 0 ? "YES" : "NO");
        }
    }
    return 0;
}
