/*
 * 选自 程序员面试宝典（第四版）
 *
 * Description:
 *
 *  利用位运算实现整数的加法：int Add(int x, int y);
 *
 */
int Add(int x, int y) {
    if(x == 0) return y;
    int common_sum =  (x & y) << 1;
    int diff_sum = x ^ y;
    return Add(common_sum, diff_sum);
}
