#include <stdio.h>

int main() {
    int n;
    scanf("%d", &n);

    char pw1[35];
    char pw2[35];

    scanf("%s", pw1);
    scanf("%s", pw2);

    int answer = 1;

    for (int i = 0; i < n; i++) {
        if (pw1[i] != pw2[i]) {
            answer *= 2;
        }
    }

    printf("%d", answer);

    return 0;
}
