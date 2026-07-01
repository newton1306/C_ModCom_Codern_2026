#include <stdio.h>

int main() {

    int a[5];

    for(int i=0;i<5;i++)
        scanf("%d",&a[i]);

    int mx=a[0];

    for(int i=1;i<5;i++)
        if(a[i]>mx)
            mx=a[i];

    printf("%d",mx);

    return 0;
}