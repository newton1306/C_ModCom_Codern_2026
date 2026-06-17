#include <stdio.h>

int main()
{
    char code;

    scanf(" %c", &code);

    switch (code) {
    case 'H':
        printf("Home Kit");
        break;
    case 'A':
        printf("Away Kit");
        break;
    case 'N':
        printf("Neutral Kit");
        break;
    default:
        printf("Invalid Kit");
        break;
    }

    return 0;
}
