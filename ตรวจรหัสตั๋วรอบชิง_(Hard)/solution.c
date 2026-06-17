#include <stdio.h>

int is_digit(char ch)
{
    return ch >= '0' && ch <= '9';
}

int valid_code(char code[], int *seat)
{
    if (code[0] != 'F') {
        return 0;
    }
    if (code[1] < 'A' || code[1] > 'Z') {
        return 0;
    }

    int sum = 0;
    int value = 0;
    for (int i = 2; i < 6; i++) {
        if (!is_digit(code[i])) {
            return 0;
        }
        int digit = code[i] - '0';
        sum += digit;
        value = value * 10 + digit;
    }

    *seat = value;
    return value >= 1 && sum % 3 == 0;
}

int main()
{
    int n;
    int valid = 0;
    int invalid = 0;
    int zone_count[26] = {0};
    int max_seat = 0;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        char code[7];
        int seat = 0;
        scanf("%6s", code);

        if (valid_code(code, &seat)) {
            valid++;
            zone_count[code[1] - 'A']++;
            if (seat > max_seat) {
                max_seat = seat;
            }
        } else {
            invalid++;
        }
    }

    char top_zone = '-';
    int best_count = 0;
    for (int i = 0; i < 26; i++) {
        if (zone_count[i] > best_count) {
            best_count = zone_count[i];
            top_zone = (char)('A' + i);
        }
    }

    printf("Valid: %d\n", valid);
    printf("Invalid: %d\n", invalid);
    printf("Top zone: %c\n", top_zone);
    printf("Max seat: %d", max_seat);

    return 0;
}
