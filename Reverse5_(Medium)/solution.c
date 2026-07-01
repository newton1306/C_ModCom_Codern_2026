#include <stdio.h>
#include <string.h>

int main()
{
    char s[101];

    scanf("%100s", s);
    for (int i = 0; s[i] != '\0'; i++) {
        char ch = s[i] + 1;
        if (s[i] == 'z') {
            ch = 'a';
        }
        printf("%c", ch);
        if (s[i + 1] != '\0') {
            printf(" ");
        }
    }

    return 0;
}
