/* Innovation Works - Anquanbao
 *                  Dec 13, 2013
 */
#include <stdio.h>

int func(int x) {
    int cnt = 0;
    while(x) {
        cnt ++;
        x = x&(x-1);
    }
    return cnt;
}
int main(int argc, char *argv[]) {
    printf("%d\n", func(9999));
    return 0;
}
