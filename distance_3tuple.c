/* Alibaba 2014 Campus Hiring
 *      Sep 22, 2013
 *
 * Problem Description:
 *
 *  已知三个升序整数数组a[l], b[m]和c[n]。请在三个数组中各找一个元素，使得
 *  组成的三元组距离最小。三元组的距离定义是：假设a[i]、b[j]和c[k]是一个三
 *  元组，那么距离为:
 *  Distance = max(|a[i] – b[j]|, |a[i] – c[k]|, |b[j] – c[k]|)
 *
 *  请设计一个求最小三元组距离的最优算法，并分析时间复杂度。
 *
 * Analysis:
 *
 *  由max(|a|, |b|) = 1/2 * (|a-b| + |a+b|), 
 *  设x1 = a[i], x2 = b[j], x3 = c[k], 则
 *  Distance = max(|x1-x2|, |x2-x3|, |x3 - x1|)
 *           = 1/2 * (|x1-x2|+|x2-x3|+|x3-x1|)
 *
 * 为每一个数组设定一结构体，分别存放其数组起始位置，数组长度，和当前
 * 的位置索引。初始时，取三个数组的第一个数组成三元组，计算其距离。然后前
 * 移三个数中最小者所在的数组的索引，再计算距离，再前移三数之最小者所在数
 * 组的索引，计算距离...如此循环，直到最小值所在数组的索引被穷尽。由此，
 * 最多移动(l + m + n)次，复杂度为 T(l,m,n) = O(l+m+n).
 *
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *array;
    int len;
    int i;
} Arc;

static Arc * arcForMin(Arc *a, Arc *b, Arc *c) {
    Arc * pArcMin;
    pArcMin = (a->array[a->i] < b->array[b->i])? a: b;
    pArcMin = (pArcMin->array[pArcMin->i] < c->array[c->i]) ? pArcMin: c;
    return pArcMin;
}

static int distance(Arc *a, Arc *b, Arc *c) {
    int x1 = a->array[a->i],
        x2 = b->array[b->i],
        x3 = c->array[c->i];
    return (abs(x1-x2) + abs(x2-x3) + abs(x3-x1))/2;
}

int min_dist(int arr1[], int n1, int arr2[], int n2, int arr3[], int n3) {
    if(!arr1||!arr2||!arr3|| !n1 || !n2 || !n3)
        return -1;
    Arc a = {.array = arr1, .len = n1, .i = 0}, 
           b = {.array = arr2, .len = n2, .i = 0},
           c = {.array = arr3, .len = n3, .i = 0};
    Arc *pArcMin = NULL;
    int minDist, currDist;
    minDist = distance(&a, &b, &c);
    pArcMin = arcForMin(&a, &b, &c);
    while(++pArcMin->i != pArcMin->len) {
        currDist = distance(&a, &b, &c);
        if(currDist < minDist)
            minDist = currDist;
        pArcMin = arcForMin(&a, &b, &c);
    }
    return minDist;
}

int main(int argc, char *argv[]) {
    int arr1[] = {2, 3, 5, 7, 9};
    int arr2[] = {3, 6, 9, 11, 17, 19, 23};
    int arr3[] = {1, 5, 8, 11, 13, 17};
    int n1 = sizeof(arr1)/sizeof(int),
        n2 = sizeof(arr2)/sizeof(int),
        n3 = sizeof(arr3)/sizeof(int);
    int ret = min_dist(arr1, n1, arr2, n2, arr3, n3);
    printf("Minimum Distance: %d\n", ret);
    return 0;
}
