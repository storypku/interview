/*
 * 剑指Offer: 名企面试官精讲典型编程题
 *
 *              Jan 26, 2014 By 斯德瑞
 * Problem Description:
 *
 *  求链表中的倒数第K个结点
 *
 * Analysis:
 *
 *  两个指针，第一个指针先走k步，然后两个指针一起走。
 *  当第一个走到Off-the-end悬崖边的时候, 第二个指针
 *  指向的正是倒数第K个结点。
 *
 */
#include <iostream>
#include <iomanip>

using std::cout; using std::endl;
template <typename T>
struct ListNode {
     T data;
     ListNode *next;
};

template <typename T>
ListNode<T> * FindKthToTail(ListNode<T> *pListHead, unsigned k) {
    if(!pListHead) return NULL;
    ListNode<T> *pAhead = pListHead;
    for(unsigned i = 0; i < k; i++) {
        pAhead = pAhead->next;
        if(!pAhead && i != k-1)
            return NULL;
    }
    ListNode<T> *pBehind = pListHead;
    while(pAhead) {
        pAhead = pAhead->next;
        pBehind = pBehind->next;
    }
    return pBehind;
}

template <typename T>
void FreeList(ListNode<T> *pHead) {
    while(pHead) {
        ListNode<T> *pNext = pHead->next;
        delete pNext;
        pHead = pNext;
    }
}

int main() {
    ListNode<int> *pHead = NULL, *pPrev = NULL;
    const unsigned N = 10;
    for(unsigned i = 0; i < N; i++) {
        ListNode<int> * pNode = new ListNode<int>;
        if(!pNode) {            // in case memory allocation fails
            FreeList(pHead);    // avoid potential memory leak
            return -1;
        }
        pNode->data = i + 1;
        if(i == 0) {
            pHead = pNode;
        } else {
            pPrev->next = pNode;
        }
        pPrev = pNode;
    }
    for(unsigned k = 1; k < N + 3; k++) {
        ListNode<int> *pNode = FindKthToTail(pHead, k);
        if (pNode)
            cout << "Got " << std::right << std::setw(2) << pNode->data
                 << ", expecting " << std::setw(2) << N+1-k << endl;
        else
            cout << "Too large K: " << k << endl;
    }
    FreeList(pHead);
    return 0;
}
