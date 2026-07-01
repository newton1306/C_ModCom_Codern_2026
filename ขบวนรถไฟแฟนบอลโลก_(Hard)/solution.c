#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int left, right, size;
    unsigned priority;
    long long value, sum, add;
    int reverse;
} Node;

static Node *tr;
static unsigned rngState = 2463534242u;

static unsigned rng(void) {
    rngState ^= rngState << 13;
    rngState ^= rngState >> 17;
    rngState ^= rngState << 5;
    return rngState;
}

static int size_of(int x) { return x ? tr[x].size : 0; }
static long long sum_of(int x) { return x ? tr[x].sum : 0; }

static void pull(int x) {
    tr[x].size = 1 + size_of(tr[x].left) + size_of(tr[x].right);
    tr[x].sum = tr[x].value + sum_of(tr[x].left) + sum_of(tr[x].right);
}

static void apply_add(int x, long long v) {
    if (!x) return;
    tr[x].value += v;
    tr[x].sum += v * tr[x].size;
    tr[x].add += v;
}

static void apply_reverse(int x) {
    if (!x) return;
    int t = tr[x].left; tr[x].left = tr[x].right; tr[x].right = t;
    tr[x].reverse ^= 1;
}

static void push(int x) {
    if (!x) return;
    if (tr[x].reverse) {
        apply_reverse(tr[x].left); apply_reverse(tr[x].right);
        tr[x].reverse = 0;
    }
    if (tr[x].add) {
        apply_add(tr[x].left, tr[x].add); apply_add(tr[x].right, tr[x].add);
        tr[x].add = 0;
    }
}

static int merge(int a, int b) {
    if (!a) return b;
    if (!b) return a;
    if (tr[a].priority > tr[b].priority) {
        push(a); tr[a].right = merge(tr[a].right, b); pull(a); return a;
    }
    push(b); tr[b].left = merge(a, tr[b].left); pull(b); return b;
}

static void split(int root, int count, int *a, int *b) {
    if (!root) { *a = *b = 0; return; }
    push(root);
    if (size_of(tr[root].left) >= count) {
        split(tr[root].left, count, a, &tr[root].left);
        pull(root); *b = root;
    } else {
        split(tr[root].right, count - size_of(tr[root].left) - 1, &tr[root].right, b);
        pull(root); *a = root;
    }
}

int main(void) {
    int n, q;
    if (scanf("%d %d", &n, &q) != 2) return 0;
    tr = (Node *)calloc((size_t)n + 1, sizeof(Node));
    int root = 0;
    for (int i = 1; i <= n; ++i) {
        scanf("%lld", &tr[i].value);
        tr[i].sum = tr[i].value; tr[i].size = 1; tr[i].priority = rng();
        root = merge(root, i);
    }
    while (q--) {
        char command[8]; int l, r, a, b, c;
        scanf("%s %d %d", command, &l, &r);
        split(root, l - 1, &a, &b);
        split(b, r - l + 1, &b, &c);
        if (command[0] == 'A') {
            long long x; scanf("%lld", &x); apply_add(b, x);
        } else if (command[0] == 'R') {
            apply_reverse(b);
        } else {
            printf("%lld\n", sum_of(b));
        }
        root = merge(a, merge(b, c));
    }
    return 0;
}
