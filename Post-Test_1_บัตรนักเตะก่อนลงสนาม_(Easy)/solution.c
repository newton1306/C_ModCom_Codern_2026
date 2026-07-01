#include <stdio.h>

int main() {
    char name[35];
    int number;

    scanf("%s", name);
    scanf("%d", &number);

    printf("Player: %s\n", name);
    printf("Number: %d\n", number);
    printf("Ready to play!");

    return 0;
}

