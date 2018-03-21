#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef unsigned long long  ullong;
typedef unsigned char bool;
#define true 1
#define false 0

#define PRIME_MAX      10000
#define PRIME_TEST_SCURITY 10
#define PRIME_LIST_CNT 1000
#define PRIME_CHOSE_RANGE PRIME_LIST_CNT / 4
#define _MIN(x, y) (x < y ? x : y)
#define _MAX(x, y) (y < x ? x : y)

ullong prime_list[PRIME_LIST_CNT];

ullong _mod_pow(ullong x, ullong y, ullong m) {
    ullong result = 1;
    while(0 < y) {
        if (y & 1) result = (result * x) % m;
        y = y >> 1;
        x = (x * x) % m;
    }
    return result;
}

ullong _lcm(ullong x, ullong y) {
    ullong larger = _MAX(x, y), lesser = _MIN(x, y), i = 2;
    while (larger * i % lesser != 0) {
        i++;
    }
    return larger * i;
}

ullong _rand(ullong max)
{
    ullong number = 0;
    number = rand() % max;
    return number;
}

bool _prime_check(ullong number)
{
    ullong i = 2;
    ullong max = sqrt(number);
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
            return false;
        }
    }
    return true;
}


/* get random prime number from prime list */
// ullong _get_random_prime_number()
// {
//     ullong number = 0;
//     while (!_prime_check(number))
//     {
//         number = _rand(PRIME_LIST_CNT);
//         number = number + (1 - number % 2);
//     }
//     return number;
// }

/* solovay strassen test*/
ullong _gcd(ullong a, ullong b) {
    ullong result = b;
    while(result != 0) {
        result  = a % b;
        a = b;
        b = result;
    }
    return a;
}

int _jacobi(ullong a, ullong n) {
    int result = 0, tmp = 0;
    //TODO: calculate jacobi
    if (_gcd(a, n) != 1) return 0;
    switch(a) {
        case 1: {
            return 1;
        }
        case 2: {
            return ((n * n - 1) / 8) % 2 ? -1 : 1;
        }
        default: {
            tmp = n;
            n = a;
            a = tmp % a;
            return _jacobi(a, n) * ((a - 1) / 2 * (n - 1) / 2 % 2 ? -1 : 1);
        }
    }
    return result;
}

bool _solovay_strassen_test(ullong n) {
    ullong a = 0, tcnt = PRIME_TEST_SCURITY;
    int modex = 0, jac = 0;
    if (n % 2 == 0 && n != 2) return false;
    while (0 < tcnt--) {
        a = _rand(n); 
        modex = _mod_pow(a, (n - 1) / 2, n);
        jac = _jacobi(a, n);
        if (jac != modex && jac != (modex - n)) 
            return false;
    }
    return true;
}
/* get random prime by prime test */
ullong _get_random_prime_number() {
    ullong number = 0;
    while(1) {
        number = _rand(PRIME_MAX);
        number += (1 - number % 2);
        if (number < PRIME_MAX / 2) continue;
        if (_solovay_strassen_test(number)) {
            return number;
        }
        if (_prime_check(number)) {
            printf("random odd: %llu, prime_check: true, solovay-test: false\n", number);
        }
    }
}

ullong _get_big_random_prime_number() {
    return prime_list[PRIME_LIST_CNT - _rand(PRIME_CHOSE_RANGE) - 1];
}

ullong _get_small_random_prime_number() {
    return prime_list[_rand(PRIME_CHOSE_RANGE)];
}

void _initialize_prime_list()
{
    ullong nature = 0, lindex = 0;
    prime_list[lindex++] = 2;
    prime_list[lindex++] = 3;
    prime_list[lindex++] = 5;
    for (nature = 6; lindex < PRIME_LIST_CNT; nature++)
    {
        int pindex = 0;
        int max = sqrt(nature) + 1;
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
    //_initialize_prime_list();
    srand(time(0));
    return true;
}

void _show_prime_list();

int main(void)
{
    ullong p, q, n, l, e, d;
    ullong msg = 123, msg_e = 0, msg_d = 0;  
    if (!_initialize()) {
        return 0;
    } 
    _show_prime_list();
    printf("msg: %llu\n", msg);

    /*1.get one prime number, p*/
    p = _get_random_prime_number();
    printf("p = %llu\n", p);

    /*2.get another prime number, q , similar to the first one*/
    q = p;
    while (q == p ) {
        q = _get_random_prime_number();
    }
    printf("q = %llu\n", q);

    /*3.get n*/
    n = p * q;
    printf("n = %llu\n", n);

    /*4.get Sigma(n), l*/
    l = (p - 1) * (q - 1);
    printf("l = %llu\n", l);

    /*5.get e*/
    e = 1;
    while( l % e == 0 || l < e) {
        e = _get_random_prime_number();
    }
    printf("e = %llu\n", e);

    /*6.get d (now: the small one )*/
    for (d = 1; d < l; d++) {
        if (d * e % l == 1) {
            break;
        }
    }
    printf("d = %llu\n", d);

    /*7.encryption*/
    msg_e = _mod_pow(msg, e, n);
    printf("msg_e = %llu\n", msg_e);

    /*8.decryption*/
    msg_d = _mod_pow(msg_e, d, n);
    printf("msg_d = %llu\n", msg_d);
    return 0;
}

void _show_prime_list() {
    ullong lindex = 0;
    printf("prime_list=[");
    for (lindex; lindex < PRIME_LIST_CNT; lindex++) {
        char *str = lindex == 0 ? " %llu" : ", %llu";
        printf(str, prime_list[lindex]);
    }
    printf("]\n");
}
