/* 美团网2014 Campus Hiring
 *  Sep 10, 2013
 *
 * Problem Description:
 *  一个m*n的矩阵，从左到右从上到下都是递增的，给一个数elem，求是否在矩阵
 *  中，给出思路和代码。
 *
 * Analysis:
 *  杨氏矩阵查找, 时间复杂度为O(m+n)
 *
 */
#include <iostream>
#define N 4

using namespace std;

bool young_search(const int arr[][N], const int M, int elem) {
    int r = 0, c = N-1;
    int val;
    while( c != -1 && r != M ) {
        val = arr[r][c];
        if(val == elem)
            return true;
        else if(val < elem)
            r++;
        else
            c--;
    }
    return false;
}
int main(int argc, char *argv[]) {
    int elem;
    const int M = 4;
    int arr[][N] = {{1, 2, 8, 9},
                     {2, 4, 9, 12},
                     {4, 7, 10, 13},
                     {6, 8, 11, 15}
                    };
    cout << "Your search: ";
    while(cin >> elem) {
        if(young_search(arr, M, elem))
            cout << elem << " exists." << endl;
        else
            cout << elem << " doesn't exist." << endl;
        cout << "Your search: ";
    }
    return 0;
}
