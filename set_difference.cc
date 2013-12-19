/*
 * Xunlei 2014 Campus
 *      Sep 09, 2013
 *
 * 已知集合A和B的元素分别用不含头结点的单链表存储，函数difference()用于求解
 * 集合A与B的差集，并将结果保存在集合A的单链表中。例如，若集合A={5, 10, 20,
 * 15, 25, 30}，集合B={5, 15, 35, 25}，完成计算后A={10, 20, 30}。
 * 链表结点的结构类型定义如下：
 * struct node {
 *  int elem;
 *  node *next;
 * };
 *
 */
#include <iostream>
struct node {
    int elem;
    node *next;
};

void difference(node **LA, node *LB) {
    node *pa, *pb, *pre, *q;
    pre = NULL;
    pa = *LA;
    while(pa) {
        pb = LB;
        while(pb && pa->elem != pb->elem)
            pb = pb->next;
        if(pb) {
            if(!pre)
                *LA = pa->next;
            else
                pre->next = pa->next;
            q = pa;
            pa = pa->next;
            free(q);
        } else {
            pre = pa;
            pa = pa->next;
        }
    }
}

