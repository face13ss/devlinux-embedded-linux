#include "mmath.h"

int isPrime(int number) {
    int flag = 0;
    if (number == 0 || number == 1)
        flag = 1;

    for(int i = 0; i < number/2; ++i) {
        if (number % i == 0) {
            flag = 1;
            break;
        }
    }
    // 0 is prime
    // 1 are not prime
    return flag;
}