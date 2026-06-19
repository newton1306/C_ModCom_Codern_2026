#include <stdio.h>

void reverse_string(char str[], int length) {
    int left = 0;
    int right = length - 1;

    while (left < right) {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}

int main() {
    long long n;
    int base;
    scanf("%lld %d", &n, &base);

    char digits[] = "0123456789abcdefghijklmnopqrstuvwxyz";
    char answer[70];
    int index = 0;
    int is_negative = 0;

    if (n == 0) {
        printf("0");
        return 0;
    }

    if (n < 0) {
        is_negative = 1;
        n = -n;
    }

    while (n > 0) {
        answer[index++] = digits[n % base];
        n /= base;
    }

    if (is_negative) {
        answer[index++] = '-';
    }

    answer[index] = '\0';
    reverse_string(answer, index);

    printf("%s", answer);
    return 0;
}
