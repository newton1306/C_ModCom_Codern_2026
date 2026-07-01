#include <stdio.h>

int main() {

    int score;

    scanf("%d",&score);

    if(score>=80)
        printf("Excellent");
    else if(score>=50)
        printf("Pass");
    else
        printf("Fail");

    return 0;
}