/* MicroStrategy 2014 Campus Hiring
 *      Oct 21, 2013
 *
 * Problem Description:
 *   Find the element in the rigorously increasing array A (i.e., no dup-
 *   licates) that satisfies A[i] = i.
 *
 */
#include <stdio.h>

int search(const int *arr, int n) {
    int low, high, mid;
    low = 0;
    high = n - 1;
    while(low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == mid)
            return mid;
        else if (arr[mid] < mid) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

int main() {
    int A[10] = {-3, -1, 2, 4, 6, 7, 8, 9, 10, 11};
    int dst = search(A, 10);
    if (dst >= 0)
        printf("A[%d] = %d\n", dst, A[dst]);
    else
        printf("No such element.\n");
    return 0;
}
