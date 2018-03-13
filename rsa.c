#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef unsigned char bool;
#define true 1
#define false 0

unsigned int random_seed = 0;

bool _prime_check(unsigned int number) {
    int i = 2;
    int max = sqrt(number);
    if (number < 2) {
        return false;
    }
    if (2 == number) {
        return true;
    }
    if (number % 2 == 0 || number % 3 == 0) {
        return false;
    }
    for (i = 5; i < max; i++) {
        if (number % i) {
            printf("%d is not prime, can div by %d\n", number, i);
            return false;
        }
    }
    return true;
}

unsigned int _random() {
    unsigned int number = 0;
    srand(random_seed);
    number = random();
    random_seed = number;
    printf("get random number: %d\n", number);
    return number;
}

unsigned int _get_random_prime_number() {
    int number = 0;
    while(!_prime_check(number)) {
        number = _random();
    }
    return number;
}

int main(void) {
    printf("random: %d, MAX: %d\n", _random(), RAND_MAX);
    printf("get random prime number: %d\n", _get_random_prime_number());
}
