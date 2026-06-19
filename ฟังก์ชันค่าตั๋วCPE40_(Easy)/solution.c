#include <stdio.h>

double packagePrice(int basePrice, char package)
{
    if (package == 'V') {
        return basePrice + 150.0;
    }
    return basePrice;
}

double calculateTotal(int basePrice, int fans, char package, int discount)
{
    double subtotal = packagePrice(basePrice, package) * fans;
    return subtotal - subtotal * discount / 100.0;
}

int main()
{
    int basePrice, fans, discount;
    char package;

    scanf("%d", &basePrice);
    scanf("%d", &fans);
    scanf(" %c", &package);
    scanf("%d", &discount);

    printf("Total: %.2f", calculateTotal(basePrice, fans, package, discount));
    return 0;
}
