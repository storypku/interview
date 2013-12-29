/* 2014 Meituan Social Hiring
 *          Dec 23, 2013
 * 給定兩個有序數組，將至合併成一個有序無重複的數組
 */
#include <stdio.h>
int main(int argc, char *argv[]) {
    int arrA[] = {1, 2, 2, 3, 7, 9, 13};
    int arrB[] = {1, 3, 5, 7, 9, 11, 15, 17, 17, 21};
    int lenA = sizeof(arrA)/sizeof(int);
    int lenB = sizeof(arrB)/sizeof(int);
    int lenC = lenA+lenB;
    int arrC[lenC];
    int i = 0, j = 0, k = 0;
    while(i != lenA && j != lenB) {
        if(arrA[i] < arrB[j]) {
            if(k == 0 || arrC[k-1] != arrA[i])
                arrC[k++] = arrA[i];
            i++;
        }
        else if(arrA[i] == arrB[j]) {
            if(k == 0 || arrC[k-1] != arrA[i])
                arrC[k++] = arrA[i];
            i++, j++;
        }
        else {
            if(k == 0 || arrC[k-1] != arrB[j])
                arrC[k++] = arrB[j];
            j++;
        }
    }
    while(i < lenA) {
        if(k==0 || arrC[k-1] != arrA[i])
            arrC[k++] = arrA[i];
        i++;
    }
    while(j < lenB) {
        if(k == 0 || arrC[k-1] != arrB[j])
            arrC[k++] = arrB[j];
        j++;
    }
    lenC = k;
    for(k = 0; k < lenC; k++)
        printf("%d ", arrC[k]);
    printf("\n");
    return 0;
}
