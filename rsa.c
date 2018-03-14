#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef unsigned char bool;
#define true 1
#define false 0

#define PRIME_LIST_CNT 100
#define PRIME_CHOSE_RANGE PRIME_LIST_CNT / 2

unsigned int random_seed = 0;
unsigned int prime_list[PRIME_LIST_CNT];

void _initialize_prime_list()
{
    unsigned int nature = 0, lindex = 0;
    prime_list[lindex++] = 2;
    prime_list[lindex++] = 3;
    prime_list[lindex++] = 5;
    for (nature = 6; lindex < PRIME_LIST_CNT; nature++)
    {
        int pindex = 0;
        int max = sqrt(nature);
        bool is_prime = true;
        for (pindex = 0; pindex < lindex && prime_list[pindex] < max; pindex++)
        {
            if (nature % prime_list[pindex] == 0)
            {
                is_prime = false;
                break;
            }
        }
        if (is_prime)
        {
            prime_list[lindex++] = nature;
        }
    }
}

bool _initialize()
{
    _initialize_prime_list();
    return true;
}

bool _prime_check(unsigned int number)
{
    int i = 2;
    int max = sqrt(number);
    if (number < 2)
    {
        return false;
    }
    if (2 == number)
    {
        return true;
    }
    if (number % 2 == 0 || number % 3 == 0)
    {
        return false;
    }
    for (i = 5; i < max; i++)
    {
        if (number % i)
        {
            printf("%d is not prime, can div by %d\n", number, i);
            return false;
        }
    }
    return true;
}

unsigned int _random(unsigned int max)
{
    unsigned int number = 0;
    srand(random_seed);
    number = random() % max;
    random_seed = number;
    printf("get random number: %d\n", number);
    return number;
}
//first get random number, then if it's prime return; shit!
// unsigned int _get_random_prime_number()
// {
//     int number = 0;
//     while (!_prime_check(number))
//     {
//         number = _random();
//     }
//     return number;
// }
unsigned int _get_big_random_prime_number() {
    return prime_list[PRIME_LIST_CNT - _random(PRIME_CHOSE_RANGE) - 1];
}

unsigned int _get_small_random_prime_number() {
    return prime_list[_random(PRIME_CHOSE_RANGE)];
}

void _show_prime_list();
int main(void)
{
    unsigned int p, q, n, l, e, d;
    if (!_initialize()) {
        return 0;
    } 
    _show_prime_list();
    //1.get one prime number, p
    p = _get_big_random_prime_number();
    printf("p = %d\n", p);
    //2.get another prime number, q , similar to the first one
    q = p;
    while (q == p ) {
        q = _get_big_random_prime_number();
    }
    printf("q = %d\n", q);
    //3.get n
    n = p * q;
    printf("n = %d\n", n);
    //4.get Sigma(n), l
    l = (p - 1) * (q - 1);
    printf("l = %d\n", l);
    //5.get e
    e = 1;
    while( l % e == 0) {
        e = _get_big_random_prime_number();
    }
    printf("e = %d\n", e);
    //6.get d (now: the small one )
    for (d = 1; d < l; d++) {
        if (d * e % l == 1) {
            break;
        }
    }
    printf("d = %d\n", d);
    //7.encryption
    //8.decryption
    return 0;
}

void _show_prime_list() {
    unsigned int lindex = 0;
    printf("prime_list=[");
    for (lindex; lindex < PRIME_LIST_CNT; lindex++) {
        char *str = lindex == 0 ? " %d" : ", %d";
        printf(str, prime_list[lindex]);
    }
    printf("]\n");
}
