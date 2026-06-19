#include <stdio.h>

int main() {
    int n;
    scanf("%d" ,&n);
    int map[n];
    for(int i=0; i < n; i++){
        scanf("%d" , &map[i]);
    }
    for(int i=0; i < n ; i++){ 
        for(int j=i; j<n; j++){
            if((map[i]+map[j]) % n != map[(i+j) % n]){
                printf("false");
                return 0;
            }
        }
    }
    printf("true");
    return 0;
}
