/* 创新工场 2014 Campus Hiring
 *  Sep 16, 2013
 * 输入一个整形无序数组，用堆排序的方法使之有序。
 */
#include <iostream>
using namespace std;
static void swap(int &a, int &b) {
    int c = a; a = b; b = c;
}
static void siftup(int array[], int idx) {
    if(idx > 0) {
        int parent = (idx-1)/2;
        if(array[idx] > array[parent]) {
            swap(array[idx], array[parent]);
            siftup(array, parent);
        }
    }
}
static void siftdown(int array[], const int n, int idx) {
    int left = 2*idx+1, right = left+1, largest = idx;
    if(left < n && array[left] > array[largest])
        largest = left;
    if(right < n && array[right] > array[largest])
        largest = right;
    if(largest != idx) {
        swap(array[largest], array[idx]);
        siftdown(array, n, largest);
    }
}
void heapsort(int array[], const int n) {
    for(int i=0; i < n; i++)
        siftup(array, i);
    for(int i = n-1; i > 0; i--) {
        swap(array[i], array[0]);
        siftdown(array, i, 0);
    }
}
int main() {
    int array[] = {10, 51, 2, 18, 4, 31, 13, 5, 23, 64, 29};
    cout << "Original array: ";
    for(auto i: array)
        cout << i << " ";
    cout << endl;
    heapsort(array, sizeof(array)/sizeof(int));
    cout << "After heapsort: ";
    for(auto i: array)
        cout << i << " ";
    cout << endl;
    return 0;
}
