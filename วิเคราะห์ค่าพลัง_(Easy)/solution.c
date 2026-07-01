#include <stdio.h>

int main() {
    char fname[50], lname[50];
    int reading, teamwork, physical, total;

    scanf("%s %s", fname, lname);


    scanf("%d", &reading);
    scanf("%d", &teamwork);
    scanf("%d", &physical);


    total = reading + teamwork + physical;


    if (reading < 0 || reading > 30 || teamwork < 0 || teamwork > 30 || physical < 0 || physical > 40 || total > 100) {
        printf("Something went wrong\n");
    } 
    else if (total <= 60) {
         printf("%s %s is Normal Player\n", fname, lname);
    } 
    else if (total <= 80) {
        printf("%s %s is Good Player\n", fname, lname);
    }
    else if(total <= 100){
        printf("%s %s is Talented Player\n", fname, lname);
    }

    return 0;
}
