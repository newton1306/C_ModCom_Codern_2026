#include <stdio.h>

int main()
{
    int n;
    int menu, amount;
    float total = 0.0f;

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        scanf("%d %d", &menu, &amount);

        int price_per_cup;
        if (menu == 1) {
            price_per_cup = 10;
        } else if (menu == 2) {
            price_per_cup = 25;
        } else {
            price_per_cup = 30;
        }

        float price = price_per_cup * amount;
        if (amount >= 5) {
            price *= 0.90f;
        }

        total += price;
        printf("%d %d %.2f\n", menu, amount, price);
    }

    printf("Total: %.2f", total);
    return 0;
}

