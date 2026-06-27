#include <stdio.h>

int main()
{
    char s[101];
    int ans = 0;

    scanf("%100s", s);
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') {
            ans++;
        }
    }

    printf("%d", ans);

    return 0;
}
