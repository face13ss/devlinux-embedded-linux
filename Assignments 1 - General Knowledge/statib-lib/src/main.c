#include <stdio.h>
#include "mmath.h"

int main() {
    int number = 73;
    if (isPrime(number) == 0)
        printf("%d is a prime number.", number);
    else
        printf("%d is not a prime number.", number);

    return 0;
}