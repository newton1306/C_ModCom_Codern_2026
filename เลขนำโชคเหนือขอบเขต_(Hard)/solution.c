#include <stdio.h>
#include <string.h>

#define MAX_BYTES 4005
#define MAX_DIGITS 1005

const char OFFSET[] = "18446744073709551609";

void strip_leading_zero(char *s) {
    int i = 0;
    while (s[i] == '0' && s[i + 1] != '\0') {
        i++;
    }
    if (i > 0) {
        memmove(s, s + i, strlen(s + i) + 1);
    }
}

int thai_to_ascii(const char *src, char *dst) {
    int i = 0;
    int j = 0;

    while (src[i] != '\0') {
        unsigned char a = (unsigned char)src[i];

        if (a >= '0' && a <= '9') {
            dst[j++] = (char)a;
            i++;
        } else if (a == 0xE0 &&
                   (unsigned char)src[i + 1] == 0xB9 &&
                   (unsigned char)src[i + 2] >= 0x90 &&
                   (unsigned char)src[i + 2] <= 0x99) {
            dst[j++] = (char)('0' + ((unsigned char)src[i + 2] - 0x90));
            i += 3;
        } else {
            return 0;
        }

        if (j >= MAX_DIGITS) {
            return 0;
        }
    }

    dst[j] = '\0';
    strip_leading_zero(dst);
    return j > 0;
}

int compare_number(const char *a, const char *b) {
    int la = (int)strlen(a);
    int lb = (int)strlen(b);

    if (la != lb) {
        return la > lb ? 1 : -1;
    }

    int cmp = strcmp(a, b);
    if (cmp > 0) {
        return 1;
    }
    if (cmp < 0) {
        return -1;
    }
    return 0;
}

void add_one(const char *a, char *out) {
    int len = (int)strlen(a);
    char temp[MAX_DIGITS + 2];
    int carry = 1;

    temp[len + 1] = '\0';

    for (int i = len - 1; i >= 0; i--) {
        int value = (a[i] - '0') + carry;
        temp[i + 1] = (char)('0' + (value % 10));
        carry = value / 10;
    }

    if (carry) {
        temp[0] = '1';
        strcpy(out, temp);
    } else {
        strcpy(out, temp + 1);
    }
}

void subtract_offset(const char *a, char *out) {
    int la = (int)strlen(a);
    int lb = (int)strlen(OFFSET);
    int borrow = 0;

    out[la] = '\0';

    for (int i = la - 1, j = lb - 1; i >= 0; i--, j--) {
        int top = a[i] - '0' - borrow;
        int bottom = j >= 0 ? OFFSET[j] - '0' : 0;

        if (top < bottom) {
            top += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        out[i] = (char)('0' + (top - bottom));
    }

    strip_leading_zero(out);
}

int main() {
    char raw_b[MAX_BYTES];
    char raw_c[MAX_BYTES];
    char b[MAX_DIGITS];
    char c[MAX_DIGITS];
    char expected_c[MAX_DIGITS + 2];
    char answer[MAX_DIGITS];

    if (scanf("%4000s %4000s", raw_b, raw_c) != 2) {
        printf("INVALID");
        return 0;
    }

    if (!thai_to_ascii(raw_b, b) || !thai_to_ascii(raw_c, c)) {
        printf("INVALID");
        return 0;
    }

    add_one(b, expected_c);
    if (strcmp(c, expected_c) != 0) {
        printf("INVALID");
        return 0;
    }

    if (compare_number(b, OFFSET) < 0) {
        printf("INVALID");
        return 0;
    }

    subtract_offset(b, answer);
    printf("%s", answer);

    return 0;
}

