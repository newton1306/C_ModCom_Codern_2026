#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int firstChild, nextSibling, pass, ending;
    unsigned char letter;
} Node;

static Node *trie;
static int nodes = 1, capacity = 0;

static void ensure_capacity(void) {
    if (nodes + 1 < capacity) return;
    int old = capacity;
    capacity = capacity ? capacity * 2 : 1024;
    trie = (Node *)realloc(trie, (size_t)capacity * sizeof(Node));
    memset(trie + old, 0, (size_t)(capacity - old) * sizeof(Node));
}

static int child_of(int parent, unsigned char letter, int create) {
    int previous = 0, current = trie[parent].firstChild;
    while (current && trie[current].letter < letter) {
        previous = current; current = trie[current].nextSibling;
    }
    if (current && trie[current].letter == letter) return current;
    if (!create) return 0;
    ensure_capacity();
    int made = nodes++;
    trie[made].letter = letter;
    trie[made].nextSibling = current;
    if (previous) trie[previous].nextSibling = made;
    else trie[parent].firstChild = made;
    return made;
}

static void add_word(const char *s, int delta) {
    int v = 0;
    trie[v].pass += delta;
    for (int i = 0; s[i]; ++i) {
        v = child_of(v, (unsigned char)(s[i] - 'a'), delta > 0);
        trie[v].pass += delta;
    }
    trie[v].ending += delta;
}

static int prefix_count(const char *s) {
    int v = 0;
    for (int i = 0; s[i]; ++i) {
        v = child_of(v, (unsigned char)(s[i] - 'a'), 0);
        if (!v) return 0;
    }
    return trie[v].pass;
}

static int kth_word(int k, char *answer) {
    if (k > trie[0].pass) return 0;
    int v = 0, len = 0;
    for (;;) {
        if (k <= trie[v].ending) { answer[len] = '\0'; return 1; }
        k -= trie[v].ending;
        int child = trie[v].firstChild;
        while (child && k > trie[child].pass) {
            k -= trie[child].pass;
            child = trie[child].nextSibling;
        }
        if (!child) return 0;
        answer[len++] = (char)('a' + trie[child].letter);
        v = child;
    }
}

int main(void) {
    int q;
    if (scanf("%d", &q) != 1) return 0;
    ensure_capacity();
    char command[8], word[64], answer[64];
    while (q--) {
        scanf("%s", command);
        if (command[0] == 'A') {
            scanf("%s", word); add_word(word, 1);
        } else if (command[0] == 'D') {
            scanf("%s", word); add_word(word, -1);
        } else if (command[0] == 'C') {
            scanf("%s", word); printf("%d\n", prefix_count(word));
        } else {
            int k; scanf("%d", &k);
            if (kth_word(k, answer)) puts(answer); else puts("NONE");
        }
    }
    return 0;
}
