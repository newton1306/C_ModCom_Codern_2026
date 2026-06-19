#include <stdio.h>

int main()
{
    int ticket, fans, discount;
    double shirt;

    scanf("%d", &ticket);
    scanf("%lf", &shirt);
    scanf("%d", &fans);
    scanf("%d", &discount);

    double subtotal = (ticket + shirt) * fans;
    double discountValue = subtotal * discount / 100.0;
    double total = subtotal - discountValue;

    printf("Subtotal: %.2f\n", subtotal);
    printf("Discount: %.2f\n", discountValue);
    printf("Total: %.2f", total);
    return 0;
}
