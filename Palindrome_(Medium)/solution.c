#include <stdio.h>

int main()
{
    long int a,x,y=0;
    scanf("%ld",&x);
    a=x;
    if(x<0){
        printf("Not a palindrome.");
        return 0;
    }
    while(x!=0)
    {
        y=y+(x%10);
        y*=10;
        x/=10;
    }
    y/=10;
    if(a==y){
        printf("%ld is a palindrome.",a);
    }else if(a!=y){
        printf("%ld is not a palindrome.",a);
    }
    return 0;
}