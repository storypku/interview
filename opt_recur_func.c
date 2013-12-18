/* Papaya Mobile
 *      Dec 16, 2013
 * Problem Description:
 *  int func(int n) {
 *      if(n <= 4)
 *          return n*n;
 *      else
 *          return func(n-1)*f(n-4) - f(n-2)*f(n-2);
 *  }
 * Question: How to optimize the function above ?
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define NTIMES 10000000

static long func(int n) {
    if (n <= 4) return n*n;
    int i, j;
    long tmp, theQueue[4] = {1, 4, 9, 16};
    const int numCalc = n - 4;
    for(i = 0; i < numCalc; i ++) {

        tmp = theQueue[3]*theQueue[0] - theQueue[2]*theQueue[2];
        /* Shift the elements in theQueue by one */
        theQueue[0] = theQueue[1];
        theQueue[1] = theQueue[2];
        theQueue[2] = theQueue[3];
        theQueue[3] = tmp;

    }
    return theQueue[3];
}

int main(int argc, char *argv[]) {
    int argu, i;
    long ret;
    if(argc != 2 || strcmp(argv[1], "--help") == 0) {
        printf("Usage: %s <integer>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    argu = atoi(argv[1]);
    for(i=0; i< NTIMES; i++) {  /* Call func() NTIMES to measure its performance */
        ret = func(argu);
    }
    printf("Func(%d) = %ld\n", argu, ret);
    exit(EXIT_SUCCESS);
}
