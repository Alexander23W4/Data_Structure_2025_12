#include <iostream>
#include <stdlib.h>
#include <string>
#include <assert.h>
using namespace std;

// Interation程序结构就是一种Stack
// Interation的妙处就是 把反向套娃思维 变成 正向顺序因果思维, Stack让这变得Explicit
// 突出Stack能够化反为正的特性

/**
  递归有 
 多项递归
 int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);
}
 单项递归
 int fact(int n) {
    if (n == 0) return 1;
    return n * fact(n - 1);
}
执行逻辑是：
先算 fact(n-1)
再乘以 n
? 调用栈必须保留 n
? 不是尾递归

单项递归有特例 尾递归:
int fact_tail(int n, int acc) {
    if (n == 0) return acc;
    return fact_tail(n - 1, n * acc);
}

这里：
fact_tail(...) 是 return 的最后一步
递归返回后 没有任何额外计算
? 这是 尾递归

由于尾递归可以不用栈, 所以可以用 迭代(其实就是while循环) 写出非递归形式

 */


// Tower Of Hanio

int Hanio(n){   // 最后求解出来其实是 2^n-1, 64个盘, 584.6亿年
    if(n > 1){
        return 2 * Hanio(n - 1) + 1;
    }
    else return 1;
}