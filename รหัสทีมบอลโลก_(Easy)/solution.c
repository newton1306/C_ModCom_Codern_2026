#include <stdio.h>
#include <string.h>

int main()
{
    char code[50];

    scanf("%49s", code);

    printf("Code: %s\n", code);
    printf("Length: %d", (int)strlen(code));
    return 0;
}
