#include <stdio.h>

int gcd_euclid(int m, int n) {
    int r;
    while (n != 0) {
        r = m % n;
        m = n;
        n = r;
    }
    return m;
}

int gcd_modified(int m, int n) {
    int min = (m < n) ? m : n;

    while (min >= 1) {
        if (m % min == 0 && n % min == 0) {
            return min;
        }
        min--;
    }

    return 1; // If no common divisor is found, the GCD is 1
}

int gcd_consecutive(int m, int n) {
    int min, temp;
    min = (m < n) ? m : n;

    while (min >= 1) {
        if (m % min == 0 && n % min == 0) {
            return min;
        }
        min--;
    }

    return 1; // If no common divisor is found, the GCD is 1
}

int main() {
    int ch, m, n, result;

    while (1) {
        printf("GCD\n");
        printf("1. Euclid\n2. Modified Euclid\n3. Consecutive integer method\n0 to exit\n");
        scanf("%d", &ch);

        if (ch == 0) {
            break;
        }

        printf("Enter the values M and N:\n");
        scanf("%d %d", &m, &n);

        switch (ch) {
            case 1:
                result = gcd_euclid(m, n);
                printf("The GCD is %d\n", result);
                break;
            case 2:
                result = gcd_modified(m, n);
                printf("The GCD is %d\n", result);
                break;
            case 3:
                result = gcd_consecutive(m, n);
                printf("The GCD is %d\n", result);
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
