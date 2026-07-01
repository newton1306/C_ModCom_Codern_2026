#include <stdio.h>
#include <string.h>

#define MAX 1005

void multiply_by_2(char number[]) {
    int carry = 0;
    int len = (int)strlen(number);

    for (int i = len - 1; i >= 0; i--) {
        int value = (number[i] - '0') * 2 + carry;
        number[i] = (char)((value % 10) + '0');
        carry = value / 10;
    }

    if (carry > 0) {
        memmove(number + 1, number, len + 1);
        number[0] = (char)(carry + '0');
    }
}

int main() {
    int n;
    char answer[MAX] = "1";

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        multiply_by_2(answer);
    }

    printf("%s", answer);

    return 0;
}

