/*
 * Alibaba 2014 Campus Hiring
 *      Sep 22, 2013
 *
 * Problem Description:
 *
 *  设计一个最优算法来查找一n个元素数组中的最大值和最小值。已知一种需要比
 * 较2n次的方法，请给一个更优的算法。情特别注意优化时间复杂度的常数。
 * 
 * Analysis:
 *  
 *  把数组中的数字两两组对，依次对每一对中的两个数做比较，把其中较大者与
 *  Max比较， 较小者与Min比较，并由此更新Max和Min。这样，遍历一次就能找
 *  到数组的最大值和最小值。
 *  这样，每一对数字比较3次，故其复杂度为n/2 * 3, 即 T(n) = O(3n/2)
 *
 */
#include <stdio.h>
int maxmin(int array[], int n, int *maxVal, int *minVal) {
    int mymin, mymax, i;
    int p, q;
    if(array == NULL || n == 0 || maxVal == NULL || minVal == NULL)
        return -1;
    mymin = mymax = array[0];

    for(i = 0; i < n - 1; i += 2) {
        p = array[i];
        q = array[i+1];
        if(p > q) {
            if (p > mymax)
                mymax = p;
            if (q < mymin)
                mymin = q;
        } else {
            if(q > mymax)
                mymax = q;
            if(p < mymin)
                mymin = p;
        }
    }

    if(n % 2) {
        p = array[n-1];
        if(p > mymax)
            mymax = p;
        else if (p < mymin)
            mymin = p;
    }
    *maxVal = mymax;
    *minVal = mymin;
    return 0;
}

static void printArray(int array[], int n) {
    int i;
    if(array == NULL || n == 0)
        return;
    printf("The array: ");
    for(i = 0; i < n; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main(int argc, char *argv[]){
    int array[] = {13, 5, 16, 21, 31, 19, 97, 2, 26};
    int sz = sizeof(array)/sizeof(int);
    int maxVal, minVal;
    printArray(array, sz);
    maxmin(array, sz, &maxVal, &minVal);
    printf("Max: %d, Min: %d\n", maxVal, minVal);
    return 0;
}
