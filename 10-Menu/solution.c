#include <stdio.h>

int main() {

    int menu;

    scanf("%d",&menu);

    switch(menu){

        case 1:
            printf("Coffee");
            break;

        case 2:
            printf("Tea");
            break;

        case 3:
            printf("Milk");
            break;

        default:
            printf("Invalid");

    }

    return 0;
}