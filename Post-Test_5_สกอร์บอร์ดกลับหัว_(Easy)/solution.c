#include <stdio.h>
#include <string.h>

char rotate_digit(char c) {
    if (c == '0') return '0';
    if (c == '1') return '1';
    if (c == '6') return '9';
    if (c == '8') return '8';
    if (c == '9') return '6';
    return '?';
}

int main() {
    char s[105];
    char answer[105];
    int index = 0;

    scanf("%s", s);

    int len = (int)strlen(s);

    for (int i = len - 1; i >= 0; i--) {
        char rotated = rotate_digit(s[i]);

        if (rotated == '?') {
            printf("INVALID");
            return 0;
        }

        answer[index++] = rotated;
    }

    answer[index] = '\0';
    printf("%s", answer);

    return 0;
}
