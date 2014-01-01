#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#define PRECISION 1e-3
#define ABS(expr) (((expr) > 0)? (expr):(-(expr)))
static void usageErr(char *progName) {
    fprintf(stderr, "Usage: %s <num>\n"
                    "               where num >= 0\n", progName);
    exit(EXIT_FAILURE);
}

double sqrt_(double x) {
    assert(x >= 0);
    double prev, curr;
    prev = x/2;
    curr = (prev + x/prev) / 2;
    while(ABS(curr-prev) > PRECISION) {
        prev = curr;
        curr = (prev + x/prev) / 2;
    }
    return curr;
}

int main(int argc, char *argv[]) {
    if(argc != 2 || strcmp(argv[1], "--help") == 0)
        usageErr(argv[0]);
    int num; double root;
    if( (num = atoi(argv[1])) < 0)
        usageErr(argv[0]);
    root = sqrt_(num);
    printf("Square root of %d is: %6.3f\n", num, root);
    return 0;
}
