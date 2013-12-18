/* MicroStrategy Campus
 *      Oct 21, 2013
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif
typedef enum { FALSE, TRUE } Boolean;

static Boolean palindrome(const char *str) {
    assert (str != NULL && *str != '\0');
    size_t i = 0, len = strlen(str);
    while(i < len/2) {
        if (str[i] != str[len-1-i])
            return FALSE;
        i++;
    }
    return TRUE;
}
int main(int argc, char *argv[]) {
    size_t len, i;
    char *p;
    if(argc != 2) {
        printf("%s <string>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    printf("Palindrome test for %s: ", argv[1]);
    if (palindrome(argv[1]))
        printf("Pass\n");
    else
        printf("Fail\n");
    exit(EXIT_SUCCESS);
}
