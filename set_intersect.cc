/* Tencent 2014 Campus Hiring
 *      Sep 21, 2013
 *
 * Problem Description:
 *
 *  A、B两个整数集合，设计一个算法求它们的交集，尽可能地高效。
 *
 * Analysis:
 *
 *  设A和B的元素个数分别为N和M(N <= M)，对A采用堆排序，复杂度
 *  为NlogN, 对B中的每个元素, 在排好序的A中二分查找，复杂度为
 *  MlogN. 因此，该算法的总的复杂度为(M+N)logN.
 */
#include <iostream>
using std::cout; using std::endl;

#include <algorithm>
using std::make_heap;
using std::sort_heap;
using std::binary_search;

#include <vector>
using std::vector;

#include <set>
using std::set;

set<int> intersect(const set<int> &setA, const set<int> &setB) {
    set<int> res;
    vector<int> vtgt(setA.begin(), setA.end());
    make_heap(vtgt.begin(), vtgt.end());
    sort_heap(vtgt.begin(), vtgt.end());
    for(auto &i: setB)
        if(binary_search(vtgt.begin(), vtgt.end(), i))
            res.insert(i);
    return res;
}
int main() {
    set<int> setA = {1, 3, 5, 39, 45, 9, 30, 6, 2};
    set<int> setB = {51, 26, 30, 7, 2, 45, 4, 9};
    set<int> setC = intersect(setA, setB);
    for(auto &i: setC)
        cout << i << " ";
    cout << endl;
    return 0;
}
