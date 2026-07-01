#include <stdio.h>

int main() {

    int a,b;

    scanf("%d %d",&a,&b);

    double avg = (double)(a+b)/2;

    printf("%.2lf",avg);

    return 0;
}