#include <stdio.h>

int main()
{
    int n;
    char s[101];
    scanf("%d", &n);
    scanf("%100s", s);

    int count = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == 'G') {
            count++;
        }
    }

    printf("%d", count);
    return 0;
}
