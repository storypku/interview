/* 网新恒天2014校园招聘
 *      Sep 06, 2013
 *
 * Problem Description:
 *  已知memcpy的函数为： void* memcpy(void *dst , const void* src , size_t n)
 *  其中dst是目的指针，src是源指针。不调用c++/c的memcpy库函数，请编写memcpy。
 *
 */

#include <assert.h>
void *memcpy(void *dst, const void *src, size_t n) {
    /* special cases */
    if(n == 0 || dst == src)
        return dst;

    unsigned char * pdst = (unsigned char *)dst;
    const unsigned char * psrc = (const unsigned char *)src;

    /* sanity check */
    assert(pdst != NULL && psrc != NULL);

    /* to avoid memory overlap */
    assert(!(psrc <= pdst && pdst < psrc + n));
    assert(!(pdst <= psrc && psrc < pdst + n));

    while(n--)
        *pdst++ = *psrc++;
    return dst;
}

