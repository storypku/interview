/* Baidu 2014 Campus Hiring
 *      Oct 13, 2013
 */
#include <stdio.h>
#include <stdlib.h>
char * reverse_str(char *src) {
    if(!src) return NULL;
    char *start = src, *end = src;
    char ch;
    while (*end++ != '\0')
        ;
    end -= 2;
    while(start < end) {
        ch = *start;
        *start++ = *end;
        *end-- = ch;
    }
    return src;
}
int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s <string-to-reverse>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    char *src = argv[1];
    printf("Before: %s\n", src);
    char *dst = reverse_str(src);
    printf("After:  %s\n", dst);
    return 0;
}
