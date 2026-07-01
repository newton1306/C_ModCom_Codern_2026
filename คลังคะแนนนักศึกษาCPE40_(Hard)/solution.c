#include <stdio.h>
#include <stdlib.h>

typedef struct { int left, right, sum; } Node;
static Node *tree;
static int nodes = 0;

static int cmp_int(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);
}

static int lower_bound_int(const int *a, int n, int x) {
    int l = 0, r = n;
    while (l < r) {
        int m = (l + r) / 2;
        if (a[m] < x) l = m + 1; else r = m;
    }
    return l;
}

static int update(int old, int l, int r, int pos) {
    int cur = ++nodes;
    tree[cur] = tree[old];
    tree[cur].sum++;
    if (l != r) {
        int m = (l + r) / 2;
        if (pos <= m) tree[cur].left = update(tree[old].left, l, m, pos);
        else tree[cur].right = update(tree[old].right, m + 1, r, pos);
    }
    return cur;
}

static int kth(int leftRoot, int rightRoot, int l, int r, int k) {
    if (l == r) return l;
    int countLeft = tree[tree[rightRoot].left].sum - tree[tree[leftRoot].left].sum;
    int m = (l + r) / 2;
    if (k <= countLeft)
        return kth(tree[leftRoot].left, tree[rightRoot].left, l, m, k);
    return kth(tree[leftRoot].right, tree[rightRoot].right, m + 1, r, k - countLeft);
}

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    int *a = (int *)malloc((size_t)n * sizeof(int));
    int *sorted = (int *)malloc((size_t)n * sizeof(int));
    for (int i = 0; i < n; ++i) { scanf("%d", &a[i]); sorted[i] = a[i]; }
    qsort(sorted, n, sizeof(int), cmp_int);
    int distinct = 0;
    for (int i = 0; i < n; ++i)
        if (i == 0 || sorted[i] != sorted[i - 1]) sorted[distinct++] = sorted[i];

    tree = (Node *)calloc((size_t)n * 22 + 5, sizeof(Node));
    int *root = (int *)calloc((size_t)n + 1, sizeof(int));
    for (int i = 1; i <= n; ++i) {
        int pos = lower_bound_int(sorted, distinct, a[i - 1]);
        root[i] = update(root[i - 1], 0, distinct - 1, pos);
    }

    while (q--) {
        int l, r, k;
        scanf("%d %d %d", &l, &r, &k);
        int pos = kth(root[l - 1], root[r], 0, distinct - 1, k);
        printf("%d\n", sorted[pos]);
    }
    return 0;
}
