/* Renren 2014 Campus Hiring
 *      Sep 22, 2013
 *
 * Problem Description:
 * 
 *  给定有n个数的数组a, 其中超过一半的数为一定值，在不进行排序，
 *  不开设额外数组的情况下，以最高效的算法找出这个数。
 *      int find(int a[], int n);
 */
#include <stdio.h>
int find(int a[], int n) {
    int nTimes = 0;
    int i, candidate;
    for(i = 0; i < n; i++)  {
        if(nTimes == 0) {
            candidate = a[i];
            nTimes = 1;
        }
        else {
            if (a[i] == candidate)
                nTimes++;
            else
                nTimes--;
        }
    }
    return candidate;
}
int main(int argc, char *argv[]) {
    int a[] = {2, 10, 10, 3, 10, 3, 3, 10, 10};
    int i, sz = sizeof(a)/sizeof(int);
    printf("The  array: ");
    for(i = 0; i < sz; i++)
        printf("%d ", a[i]);
    printf("\nThe number: %d\n", find(a, sz));
    return 0;
}
