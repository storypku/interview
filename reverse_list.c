/* Meituan 2014 Campus Hiring
 *  Sep 2013
 *
 * Problem Description:
 *  k链表翻转。给出一个链表和一个数k, 比如链表1->2->3->4->5->6, k=2,
 *  则翻转后2->1->4->3->6->5, 若k=3, 翻转后3->2->1->6->5->4, 若k=4,
 *  翻转后4->3->2->1->5->6, 用程序实现。
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 12

struct Node {
    int data;
    struct Node *next;
};

void llist_destroy(struct Node *header) {
    struct Node *tmp, *curr = header;
    while(curr != NULL) {
        tmp = curr->next;
        free(curr);
        curr = tmp;
    }
}

struct Node *llist_init(void) {
    int i = 1;
    struct Node *curr, *header = NULL, *prev=NULL;
    while(i <= N) {
        curr = malloc(sizeof(struct Node));
        if(!curr) {
            llist_destroy(header);  /* clean up */
            return NULL;
        }
        curr->data = i++;
        curr->next = NULL;
        if(!header)
            header = curr;
        else
            prev->next = curr;
        prev = curr;
    }
    return header;
}

/* Reverse the region between first and last */
static void inner_reverse(struct Node *first, struct Node *last) {
    struct Node *next_, *curr = first, *prev = NULL, *stop = last->next;
    while (curr != stop) {
        next_ = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_;
    }
}

struct Node * llist_reverse_by_k(struct Node *header, int k) {
    if(!header || k < 2) return header; /* Nothing to do */
    struct Node *curr = header, *prev = NULL;
    struct Node *first, *last;
    do {
        first = curr;
        for(int i=1; i < k; i++) { /* to find the last node of every k nodes */
            curr = curr->next;
            if(!curr) { /* not enough nodes, return early */
                if(prev)
                    prev->next = first;
                return header;
            }
        }
        last = curr;
        curr = curr->next;  /* to preserve the first node for next iteration */
        inner_reverse(first, last);
        if(!prev) {
            header = last;
        } else {
            prev->next = last;
        }
        prev = first;
    } while (curr);
    return header;
}

int main(int argc, char *argv[]) {
    struct Node *curr, *header;
    int k;

    if(argc != 2 || strcmp(argv[1], "--help") == 0) {
        fprintf(stderr, "%s k\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    k = atoi(argv[1]);

    header = llist_init();  /* Initialize the single linked list */

    for(curr = header; curr != NULL; curr = curr->next)
        printf("%d ", curr->data);
    printf("\n");

    header = llist_reverse_by_k(header, k);

    for(curr = header; curr != NULL; curr = curr->next)
        printf("%d ", curr->data);
    printf("\n");

    llist_destroy(header);
    return 0;
}
