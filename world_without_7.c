/*
 * Google 2014
 *      微信号: 待字闺中 转载的 谷歌面经(MITBBS)
 *
 * Problem Description:
 *  一个特殊的国家忌讳7这个数字，所有包含7的数字他们都不用，改用
 * 下一个数字， 比如7他们用8代替，17用19代替。给定这个国家的数字，
 * 翻译成我们用的数字。
 *
 * Analysis:
 *
 *  一个没有7的数字世界是9进制的，即：
 *      0 1 2 3 4 5 6 7 8  一般的9进制表示
 *      0 1 2 3 4 5 6 8 9  这个特殊国度的9进制表示
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
static int power(int x, int y) {
    int i = 0, ret = 1;
    while(i < y) {
        ret *= x;
        i++;
    }
    return ret;
}

/*
 * @parm
 *  src      指向特殊国家的数字串的指针
 *  orig     指向我们用的数字
 * @return
 *  成功返回0, 失败返回-1.
 */
int revert_num(const unsigned char *src, int *orig) {
    if(src == NULL || orig == NULL)     return -1;
    int i, ret = 0, sz = strlen(src);
    unsigned char c;
    for(i = 0; i < sz; i++) {
        c = src[i];
        if(!isdigit(c)) {
            *orig = 0;
            return -1;
        }
        if(c > '7')
            ret += (c - '1') * power(9, sz - 1 - i);
        else
            ret += (c - '0') * power(9, sz - 1 - i);
    }
    *orig = ret;
    return 0;
}

int main(int argc, char *argv[]) {
    int orig = 0;
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <num>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if (revert_num(argv[1], &orig) != 0) {
        fprintf(stderr, "revert_num on %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }
    printf("%d:%s\n", orig, argv[1]);
    exit(EXIT_SUCCESS);
}

/* 我们所用数字与特殊国家的数字对应表 */
#include <stdio.h>
#include <string.h>
#define NUM 1000
#define LEN 256
int main() {
    int i, r, arr[NUM];
    char strr[LEN];
    char *ptr;
    for(r = i = 0; i < NUM; i++, r++) {
        snprintf(strr, sizeof(strr), "%d", r);
        if( (ptr=strchr(strr, '7')) != NULL) {
            *ptr = '8';
            r = atoi(strr);
        }
        arr[i] = r;
    }
    for(i = 0; i < NUM; i++) {
        if(i % 10 == 0)
            printf("\n");
        printf("%4d:%4d ", i, arr[i]);
    }
    printf("\n");
    return 0;
}
