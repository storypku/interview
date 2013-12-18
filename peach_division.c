/* Problem Description:
 * 五猴分桃
 *
 * 五只猴子采得一堆桃，它们约定次日早起来分。半夜里，一只猴子偷偷起来,
 * 把桃均分成五堆后，发现还多一个，它吃了这桃子，拿走了其中一堆。第二
 * 只猴子醒来，又把桃子均分成五堆后，还是多了一个，它也吃了这个桃子，拿
 * 走了其中一堆。第三只，第四只，第五只猴子都依次如此做了。
 *
 * Question: 桃子数最少有多少个？
 */
#include <stdio.h>
#define NUM_MAX 10000

static int solution(int *numPeach, int orderNo) {
/* numPeach left for the orderNo-th monkey */
    if(orderNo == 6)
        return 1;   /* Solution found when we arrive here*/
    if( (*numPeach - 1) % 5 != 0)
        return 0;   /* indicate fail */
    *numPeach = (*numPeach - 1) * 4 / 5;
    return solution(numPeach, orderNo + 1);
}

int main(int argc, char *argv[]) {
    int i, numPeach;
    int Found = 0;
    for(i = 6; i < NUM_MAX ; i+=5) {
        numPeach = i;
        if(solution(&numPeach, 1)) {
            Found = 1;
            printf("The minimum # of Peaches: %d\n", i);
            break;
        }
    }
    if (!Found)
        printf("No solution found.\n");
    return 0;
}
