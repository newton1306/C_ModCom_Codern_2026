#include <stdio.h>

int main()
{
    int n, x;
    int mn, mx;

    scanf("%d", &n);
    scanf("%d", &x);
    mn = x;
    mx = x;

    for (int i = 2; i <= n; i++) {
        scanf("%d", &x);
        if (x < mn) {
            mn = x;
        }
        if (x > mx) {
            mx = x;
        }
    }

    printf("%d", mx - mn);

    return 0;
}
