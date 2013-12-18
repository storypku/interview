/*
 * Baidu 2014 Campus
 *      Aug 15, 2013
 *
 * Problem Description:
 *      给定一个自然数N，求[6, N]之内的所有素数中，两两之和为偶数的那些偶数。
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#define handle_error(msg) \
    do { perror(msg); exit(EXIT_FAILURE); } while (0)

unsigned char * bitmap_init(unsigned maxVal, unsigned *pLen) {
    assert(pLen != NULL);
    unsigned len = maxVal / 8 + 1;
    unsigned char *bitmap = calloc(len, sizeof(unsigned char));
    if (bitmap == NULL)
        handle_error("bitmap_init: calloc");
    *pLen = len;
    return bitmap;
}

int bitmap_set(unsigned char *bitmap, unsigned len, unsigned val) {
    unsigned quo = val / 8, remainder = val % 8;
    if(quo > len) {
        fprintf(stderr, "bitmap_set: too big value ignored: %u\n", val);
        return 0;
    }
    bitmap[quo] |= (0x1 << remainder);
    return 1;
}

int bitmap_isset(unsigned char *bitmap, unsigned len, unsigned val) {
    unsigned quo = val / 8, remainder = val % 8;
    if(quo > len) {
        fprintf(stderr, "bitmap_isset: too big value ignored: %u\n", val);
        return 0;
    }
    return bitmap[quo] & (0x1<<remainder) ? 1:0;
}

void bitmap_destroy(unsigned char *bitmap) {
    free(bitmap);
}

static unsigned * prime_array_construct(unsigned N, unsigned *pCnt) {
    assert (N > 6);

    /*
     * Next we define two  pointers: primes points to the start of the
     * primes array, while pNext points to the to-be-filled location of next
     * prime number
     */
    unsigned *primes, *pNext;

    /* At most every 2/6 numbers will be prime, and we take into account
     * that when N = 7, at least 1 additional unsigned int will be needed
     * to hold 0. */
    unsigned len = N/3 + 3;

    primes = calloc(len, sizeof(unsigned));
    if(primes == NULL)
        handle_error("prime_array_construct: calloc");

    /* initialization */
    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    pNext = primes + 3;

    /* Calc and populate all the primes up to N in the primes array */
    unsigned num = 6+1, count = 0, *ptr;
    int primeFlg, firstFlg = 1;
    /* num: the current number in question
     * primeFlg: the flag to indicate whether or not the current num is prime
     * firstFlg: only those numbers that satisfied num = 6X+1, 6X+5, 6(X+1)+1,
     *          6(X+1)+5, ... could be prime, so we set this flag to reflect
     *          this fact.
     * count:   total number of primes in the range [6, N]
     */
    while(num <= N) {
        primeFlg = 1;
        for(ptr = primes; ptr != pNext; ptr++) {
            /* traverse all existing primes */
            if(num % *ptr == 0) {
                primeFlg = 0; /* Even number found, set the primeFlg to false */
                break;
            }
        }
        if (primeFlg) {
            *pNext++ = num;
            count++;
        }
        if (firstFlg)
            num += 4;
        else
            num += 2;
        firstFlg = (firstFlg+1)%2;
    }
    if(pCnt != NULL) /* pCnt is optional */
        *pCnt = count;
    return primes;
}
static void prime_array_destroy(unsigned * primes) {
    free(primes);
}
static void printSumPrimes(unsigned N) {
    unsigned i, *primes, *piter, *pCur, *pStart;

    primes = prime_array_construct(N, NULL);

    pStart = primes + 3;
    unsigned len;

    unsigned char *pSum = bitmap_init(2*N, &len);
    for(pCur = pStart; *pCur != 0; pCur++) {
        for(piter = pCur; *piter != 0; piter++)
            bitmap_set(pSum, len, *pCur + *piter);
    }

    for(i = 6; i <= 2*N; i += 2)
        if(bitmap_isset(pSum, len, i))
            printf("%u ", i);

    printf("\n");

    bitmap_destroy(pSum);
    prime_array_destroy(primes);
}
static void usageErr(const  char *progName) {
        fprintf(stderr, "%s N (where N should be > 6)\n", progName);
        exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {
    if(argc != 2)
        usageErr(argv[0]);
    const unsigned N = (unsigned)atoi(argv[1]);
    if (N <= 6)
        usageErr(argv[0]);
    printSumPrimes(N);
    return 0;
}
