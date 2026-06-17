#include <stdio.h>

int main()
{
    int goals[5];
    int topIndex = 0;

    for (int i = 0; i < 5; i++) {
        scanf("%d", &goals[i]);
        if (goals[i] > goals[topIndex]) {
            topIndex = i;
        }
    }

    printf("Top Player: %d\n", topIndex + 1);
    printf("Goals: %d", goals[topIndex]);
    return 0;
}
