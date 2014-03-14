#include <stdio.h>
int search_last_pos_less_than_or_equal(int A[], int n, int target)
{
    if (n == 0) return -1;
    int low = 0, high = n - 1;
    int middle, value;

    while (low <= high) {
        if (high - low <= 1) {
            if (target < A[low])
                return low - 1;
            else if (target >= A[high])
                return high;
            else
                return low;
        } else {
            middle = (low + high) / 2;
            value = A[middle];
            if (value == target) {
                return middle;
            } else if (value > target) {
                high--;
                continue;
            } else {
                low = middle;
                continue;
            }

        }
    }
}
int main(int argc, char *argv[]) {
    int array[] = {1, 13, 21, 22, 40, 51};
    int i = 0;
    printf("The array: \n   ");
    for (i = 0; i< sizeof(array)/sizeof(int); i++) {
        printf(" %d ", array[i]);
    }
    printf("\n");
    if (argc != 2)
        return 0;
    int q = atoi(argv[1]);
    int ret = search_last_pos_less_than_or_equal(array, sizeof(array)/sizeof(int), q);
    printf("Your search: %d, last pos: %d\n", q, ret);
    return 0;
}
