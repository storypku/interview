/*
 * Problem Description:
 *
 *  给定数字n，请给出方法，打印出所有的位数是n的数字，并且每一个数字，每一位
 *  从左到右依次变大。例如：n=3时(123,124,125...789).
 *
 */
#include <stdio.h>
#include <stdlib.h>
static void print_num(const int arr[], size_t n) {
    int i;
    for(i = 0; i < n; i++)
        printf("%d", arr[i]);
    printf("\n");
}
void process_digits(int arr[], size_t n) {
    int idx = 0, val;
    int backFlg = 0;
    while(1) {
        if(idx == n) {          /* A new n-digits number found */
            print_num(arr, n);  /* print the number */
            idx--;              /* move back */
            backFlg = 1;        /* set the "moving back" flag */
        }
        if(idx == 0 || backFlg == 1) /* If it's the top digit, */
            val = arr[idx] + 1;        /* or backflg was set */ 
        else
            val = arr[idx-1] + 1; /* When moving forward, the digit at pos- */
                                  /* ition idx should be larger by one than */
                                  /* the digit at position idx-1 */

        if(val < 10) {    /* If val for postion idx is valid, we should */
            arr[idx] = val;    /* set the value, and then move forward. */
            idx++;         
            backFlg = 0;
        } else {          /* Or else, moving back */
            idx--; 
            backFlg = 1;
            if(idx < 0)   /* the only exit, when all numbers have been found */
                break;
        }
    }
}
int main(int argc, char *argv[]) {
    int i, curr, n = 5;
    int *arr = calloc(n, sizeof(int)); /* Memory allocated and */
                                       /* initialized to 0. */
    if(!arr) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    process_digits(arr, n);
    free(arr);
    exit(EXIT_SUCCESS);
}
