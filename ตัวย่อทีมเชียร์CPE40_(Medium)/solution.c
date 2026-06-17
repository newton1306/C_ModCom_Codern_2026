#include <ctype.h>
#include <stdio.h>

int main()
{
    char first[50], second[50], third[50];

    scanf("%49s %49s %49s", first, second, third);

    printf("Code: %c%c%c",
           toupper((unsigned char)first[0]),
           toupper((unsigned char)second[0]),
           toupper((unsigned char)third[0]));
    return 0;
}
