#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
    char code[50];
    int valid = 1;

    scanf("%49s", code);

    if (strncmp(code, "CPE40-", 6) != 0 || strlen(code) <= 6) {
        valid = 0;
    } else {
        for (int i = 6; code[i] != '\0'; i++) {
            unsigned char ch = (unsigned char)code[i];
            if (!isupper(ch) && !isdigit(ch)) {
                valid = 0;
                break;
            }
        }
    }

    if (valid) {
        printf("Valid CPE 40 Code");
    } else {
        printf("Invalid CPE 40 Code");
    }

    return 0;
}
