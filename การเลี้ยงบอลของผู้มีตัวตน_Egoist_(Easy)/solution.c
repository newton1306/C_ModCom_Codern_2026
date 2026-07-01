#include <stdio.h>

int main() {
    int X, K;
    if (scanf("%d %d", &X, &K) != 2) {
        return 0;
    }
    
    // Check if X is a prime number (2, 3, 5, 7)
    int is_prime = (X == 2 || X == 3 || X == 5 || X == 7);
    
    // Check if X and K share a common factor (2, 3, 5, or 7)
    int share_factor = ((X % 2 == 0 && K % 2 == 0) || 
                        (X % 3 == 0 && K % 3 == 0) || 
                        (X % 5 == 0 && K % 5 == 0) || 
                        (X % 7 == 0 && K % 7 == 0));
                        
    if (is_prime || share_factor) {
        printf("BLOCKED\n");
    } else {
        printf("Ore ni kateru no wa ore dake da (The Only who can beat me is me)\n");
    }
    
    return 0;
}
