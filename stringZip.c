/* Huawei 2014 Campus Hiring
 *      Sep 05, 2013
 *
 * Problem Description:
 *   通过键盘输入一串小写字母(a~z)组成的字符串。请编写一个字符串压缩程序，将字符串中
 *   连续出席的重复字母进行压缩，并输出压缩后的字符串。压缩规则：
 *  1、仅压缩连续重复出现的字符。比如字符串"abcbc"由于无连续重复字符，压缩后的字符串
 *     还是"abcbc"。
 *  2、压缩字段的格式为"字符重复的次数+字符"。例如：字符串"xxxyyyyyyz"压缩后就成为"3x6yz"。
 *  要求实现函数:
 *  void stringZip(const char *pInputStr, long lInputLen, char *pOutputStr);
 *  输入 pInputStr：  输入字符串
 *       lInputLen：  输入字符串长度
 *  输出 pOutputStr： 输出字符串，空间已经开辟好，与输入字符串等长；
 *  注意：只需要完成该函数功能算法，中间不需要有任何IO的输入输出
 *  示例:
 *  输入："cccddecc"   输出："3c2de2c"
 *  输入："adef"     输出："adef"
 *  输入："pppppppp" 输出："8p"
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static void helper(char c, size_t count, char **p){
    char tmp[1024];
    size_t len;
    if(count == 1) {
        *(*p) = c;
        (*p)++;
    }
    else {
        snprintf(tmp, sizeof(tmp), "%zu%c", count, c);
        len = strlen(tmp);
        memcpy(*p, tmp, len);
        *p = (*p) + len;
    }
    return;
}
void stringZip(const char *srcStr, size_t length, char *dstStr) {
    assert(length != 0 && srcStr != NULL && *srcStr != 0 && dstStr != NULL);
    char cur, prev = *srcStr;
    char *pdst = dstStr;
    size_t count = 1, idx;
    for(idx = 1; idx < length; idx++) {
        cur = srcStr[idx];
        if(cur == prev)
            count++;
        else {
            helper(prev, count, &pdst);
            count = 1;
            prev = cur;
        }
    }
    helper(cur, count, &pdst);
    return;
}

int main(int argc, char *argv[]) {
    char dst[1024];
    if(argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    const char *src = argv[1];
    stringZip(src, strlen(src), dst);
    printf("%s  ==>  %s\n", src, dst);
    exit(EXIT_SUCCESS);
}
