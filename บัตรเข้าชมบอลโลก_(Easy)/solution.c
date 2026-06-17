#include <stdio.h>

int main()
{
    int price, quantity;
    char zone;

    scanf("%d", &price);
    scanf("%d", &quantity);
    scanf(" %c", &zone);

    printf("Zone: %c\n", zone);
    printf("Total: %d", price * quantity);
    return 0;
}
