/* Renren 2014 Campus Hiring
 *      Sep 22, 2013
 *
 * Problem Description:
 *  给定一个有序数组a，长度为len，和一个数x, 判断a数组
 *  里面是否存在两个数， 他们的和为x。
 *  bool judge(int a[], int len, int x), 存在返回true，
 *  不存在返回false.
 *
 */
#include <iostream>
using std::cout; using std::endl;

bool judge(int a[], int len, int x) {
    int beg = 0, end = len -1;
    while(beg < end) {
        int curr_sum = a[beg] + a[end];
        if(curr_sum == x)
            return true;
        else if (curr_sum > x)
            end--;
        else
            beg++;
    }
    return false;
}
