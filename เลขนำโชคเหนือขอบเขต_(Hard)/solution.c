#include <stdio.h>
#include <string.h>

#define MAX 5005

char offset[] = "18446744073709551609";

void thai_to_number(char raw[], char num[]) {
    char thai[] = "๐๑๒๓๔๕๖๗๘๙";
    int i = 0, j = 0;

    while (raw[i] != '\0') {
        for (int d = 0; d < 10; d++) {
            if (raw[i] == thai[d * 3] &&
                raw[i + 1] == thai[d * 3 + 1] &&
                raw[i + 2] == thai[d * 3 + 2]) {
                num[j++] = '0' + d;
                break;
            }
        }

        i += 3;
    }

    num[j] = '\0';
}

int less_than(char a[], char b[]) {
    int la = (int)strlen(a);
    int lb = (int)strlen(b);

    if (la != lb) {
        return la < lb;
    }
    return strcmp(a, b) < 0;
}

void plus_one(char s[]) {
    int i = (int)strlen(s) - 1;

    while (i >= 0 && s[i] == '9') {
        s[i] = '0';
        i--;
    }

    if (i >= 0) {
        s[i]++;
    } else {
        memmove(s + 1, s, strlen(s) + 1);
        s[0] = '1';
    }
}

void subtract_offset(char s[]) {
    int i = (int)strlen(s) - 1;
    int j = (int)strlen(offset) - 1;
    int borrow = 0;

    while (i >= 0) {
        int top = s[i] - '0' - borrow;
        int bottom = j >= 0 ? offset[j] - '0' : 0;

        if (top < bottom) {
            top += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        s[i] = (char)('0' + top - bottom);
        i--;
        j--;
    }
}

void print_number(char s[]) {
    int i = 0;

    while (s[i] == '0' && s[i + 1] != '\0') {
        i++;
    }

    printf("%s", s + i);
}

int main() {
    char raw_b[MAX], raw_c[MAX];
    char b[MAX], c[MAX], check[MAX];

    scanf("%s %s", raw_b, raw_c);

    thai_to_number(raw_b, b);
    thai_to_number(raw_c, c);

    strcpy(check, b);
    plus_one(check);

    if (strcmp(check, c) != 0 || less_than(b, offset)) {
        printf("INVALID");
        return 0;
    }

    subtract_offset(b);
    print_number(b);

    return 0;
}
