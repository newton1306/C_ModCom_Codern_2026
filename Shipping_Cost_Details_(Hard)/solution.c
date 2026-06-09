#include <stdio.h>

int main() {
    int n;
    int option;
    float w;
    float s;
    int shipping_cost;
    float total_cost = 0;
    scanf("%d",&option);
    scanf("%d", &n);
    float result[n][3];

    for (int i = 0; i < n; i++) {
        scanf("%f %f", &w,&s);
        if (option == 1){
            if (w <= 1.0) {
                shipping_cost = 5;
            } else if (w <= 5.0) {
                shipping_cost = 15;
            } else {
                shipping_cost = 25;
            }
            result[i][0] = w;
            result[i][1] = s;
            result[i][2] = shipping_cost + s*3;
            total_cost = total_cost + shipping_cost + s*3;
        }else{
            if (w <= 1.0) {
                shipping_cost = 5;
            } else if (w <= 5.0) {
                shipping_cost = 15;
            } else {
                shipping_cost = 25;
            }
            total_cost += shipping_cost + s*7;
            result[i][0] = w;
            result[i][1] = s;
            result[i][2] = shipping_cost + s*7;
        }
    }
    for (int i = 0; i < n; i++) {
        printf("%.2f %.2f %.2f\n",result[i][0],result[i][1],result[i][2]); 
    }
    printf("%.2f",total_cost);    

    return 0;
}
