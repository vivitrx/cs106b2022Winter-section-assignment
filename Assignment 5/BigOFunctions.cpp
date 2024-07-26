#include "BigOFunctions.h"
#include <iostream>
using namespace std;

/******************************************************************************
 ******************************************************************************
 *********                 Part One: Printing Chip                    *********
 ******************************************************************************
 ******************************************************************************/

/* Prints a letter H that's n characters wide and n characters
 * tall. For example, calling printH(5) prints
 *
 *       *   *
 *       *   *
 *       *****
 *       *   *
 *       *   *
 *
 * and calling printH(7) prints
 *
 *       *     *
 *       *     *
 *       *     *
 *       *******
 *       *     *
 *       *     *
 *       *     *
 */
void printH(int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++) {
            /* The character is a star if it's in the very first or very last
             * column, or if it's in the middle row.
             */
            if (row == n / 2 || col == 0 || col == n - 1) {
                cout << '*';
            }
            /* Otherwise, it's blank. */
            else {
                cout << ' ';
            }
        }
        cout << endl;
    }
}

/* Prints a letter C that is n characters wide and n characters tall.
 *
 * For example, printC(4) prints
 *
 *       ****
 *       *
 *       *
 *       ****
 *
 * and printC(10) prints
 *
 *       **********
 *       *
 *       *
 *       *
 *       *
 *       *
 *       *
 *       *
 *       *
 *       **********
 */
void printC(int n) {
    for (int row = 0; row < n; row++) {

        if (row == 0 || row == n - 1) { /* First/last row print a row of stars. */
            for (int col = 0; col < n; col++) {
                cout << '*';
            }
            cout << endl;
        }
        else { /* Every othe row prints just a single star. */
            cout << '*' << endl;
        }
    }
}

/* Prints a letter I that's n characters wide and n characters
 * tall. For example, calling printI(5) prints
 *
 *       *****
 *         *
 *         *
 *         *
 *       *****
 *
 * and calling printI(7) prints
 *
 *       *******
 *          *
 *          *
 *          *
 *          *
 *          *
 *       *******
 */
void printI(int n) {
    for (int row = 0; row < n; row++) {
        /* Top and bottom rows are full of stars. */
        if (row == 0 || row == n - 1) {
            for (int col = 0; col < n; col++) { // O(n) * 2
                cout << '*';
            }
        }
        /* Every other row needs a star at the halfway point. */
        else {
            for (int col = 0; col < (n / 2); col++) { // O(n) * (n - 2)
                cout << ' ';
            }
            cout << '*'; // 一共执行n - 2次，也就是O(n)
        }
        cout << endl;
    }
}

/* Prints a letter P that's n characters wide and n characters
 * tall. For example, calling printP(5) prints
 *
 *       *****
 *       *   *
 *       *****
 *       *
 *       *
 *
 * and calling printP(7) prints
 *
 *       *******
 *       *     *
 *       *     *
 *       *******
 *       *
 *       *
 *       *
 */
void printP(int n) {
    for (int row = 0; row < n; row++) {
        /* Top and middle rows are full of stars. */
        if (row == 0 || row == n / 2) { // 2 * O(n)
            for (int col = 0; col < n; col++) { // O(n)
                cout << '*';
            }
        }
        /* Every other row in the top half has a star at the front and back. */
        else if (row < n / 2) {
            for (int col = 0; col < n; col++) {
                if (col == 0 || col == n - 1) {
                    cout << '*';
                } else {
                    cout << ' ';
                }
            }
        }
        /* All remaining rows just have a star at the front. */
        else {
            cout << '*';
        }
        cout << endl;
    }
}

/* Prints the word "CHIP" using letters of the given size. */
void printChip(int n) {
    printC(n);
    cout << endl;
    printH(n);
    cout << endl;
    printI(n);
    cout << endl;
    printP(n);
}

/******************************************************************************
 ******************************************************************************
 *********                 Part Two: Counting Triples                 *********
 ******************************************************************************
 ******************************************************************************/

/* Given a vector of integers, counts the number of triples of elements in
 * the vector th    at sum up to exactly the target. For example, given the
 * input {0, 1, 2, 3, 4} and a target of 5, the function would return 2,
 * since there are two triples of numbers ({0, 1, 4} and {0, 2, 3})
 */

//   n = 1000:     1441.97ms
int countTriples(const Vector<int>& values, int target) {
    int result = 0;
    for (int i = 0; i < values.size(); i++) {
        for (int j = i + 1; j < values.size(); j++) {
            for (int k = j + i; k < values.size(); k++) {
                if (values[i] + values[j] + values[k] == target) {
                    result++;
                }
            }
        }
    }
    return result;
}

/******************************************************************************
 ******************************************************************************
 *********                Part Three: Printing Cycles                 *********
 ******************************************************************************
 ******************************************************************************/

/* Given a vector of integers, cycles through the vector by repeatedly
 * printing out the first element, then removing it and moving it to
 * the back of the vector. This is similar to the Looper example from
 * class, except that it only does one loop.
 *
 * This first version uses .remove(0) and += to do the cycling.
 */

//  n = 50000:    197.774ms
void printCycle_v1(Vector<int>& values) {
    for (int i = 0; i < values.size(); i++) {
        int first = values[0]; // O(1)
        values.remove(0); // Remove first element // O(N)
        values += first;  // Append that element to the back. 尾加法 // O(N)

        cout << first << endl; // O(1)
    }
}

/* Given a vector of integers, cycles through the vector by repeatedly
 * printing out the first element, then removing it and moving it to
 * the back of the vector. This is similar to the Looper example from
 * class, except that it only does one loop.
 *
 * This first version uses .subList and + to do the cycling.
 */

//   n = 5000:     917.537ms
void printCycle_v2(Vector<int>& values) {
    for (int i = 0; i < values.size(); i++) {
        int first = values[0]; // O(1)
        values = values.subList(1) + first; // Cycle the elements 这一行语句很慢，可能是因为他生成了新的Vector// O(N)

        cout << first << endl;
    }
}

/* Given a queue of integers, cycles through the queue using
 * an approach similar to the one we used for the looper.
 */

//  n = 5000000:  342.424ms 什么超高速我的天哪
void printCycle_v3(Queue<int>& values) {
    for (int i = 0; i < values.size(); i++) {
        int first = values.dequeue(); // O(1)
        values.enqueue(first); // O(1)的极速！

        cout << first << endl;
    }
}

/******************************************************************************
 ******************************************************************************
 *********                Part Four: Recursive Puzzles                *********
 ******************************************************************************
 ******************************************************************************/

/* A recursive function designed to give you practice assessing efficiency.
 * Trace out how the recursion works and use that to form a hypothesis about
 * the runtime.
 */
int recursivePuzzle(int n) {
    if (n == 0) {
        return 1;
    }
    return 1 + recursivePuzzle(n - 1);
}

/* A recursive function designed to give you practice assessing efficiency.
 * Trace out how the recursion works and use that to form a hypothesis about
 * the runtime.
 */
int recursiveEnigma(int n) { // 若是现实中的数学，那么无论n是多少他都会无限递归，但是这里是整数截断除法，那么确实通过截断得到0
    if (n == 0) {
        return 1;
    }
    return 1 + recursiveEnigma(n / 2);
}

/******************************************************************************
 ******************************************************************************
 *********            Part Five: Maximum Single-Sell Profit           *********
 ******************************************************************************
 ******************************************************************************/

/* The "Maximum Single-Sell Profit" problem. In this problem, you're given a list of
 * the historical values of a stock. You're allowed to buy the stock once and sell it
 * once. The goal is to make the maximum amount of profit possible. For example, suppose
 * you're given this price list:
 *
 *         5 6 7 1 2 3 4
 *
 * Here, the best option would be to buy the stock when it's retailing for $1, then
 * sell it when it's valued at $4. We can't buy it at $1 and sell it for $7 because
 * the prices reflect the historical value of the stock in order; the stock was at
 * $7 but then dropped to $1 immediately afterwards.
 *
 * Or suppose you have this list of numbers:
 *
 *        10 9 8 7 6 5 4 3 2 1
 *
 * In this case, your maximum profit would be $0: buy the stock and then sell it
 * immediately.
 *
 * There are many ways to solve this problem. This first version of the function works
 * by looking at all buy/sell pairs and taking the best.
 */
int maximumSingleSellProfit_v1(const Vector<int>& values) {
    int best = 0; // Could buy and sell on the same day for $0 profit.
    for (int i = 0; i < values.size(); i++) { // O(n)
        for (int j = i + 1; j < values.size(); j++) { // 循环n-1次 循环n-2次 循环n-3次 循环n-4次...循环1次 循环0次 加和时间复杂度为O(n^2)
            best = max(best, values[j] - values[i]); // O(1)
        }
    }
    return best;
}// 总时间复杂度为O(n^3)

/* There's a very clever recursive algorithm for solving this problem. There's some
 * time we buy the stock and some time we sell the stock. Those times are either
 *
 *   1. purely in the first half of the array,
 *   2. purely in the second half of the array, or
 *   3. the purchase time is in the first half and the sell time is in the second.
 *
 * We can find the best solution to (1) or (2) using recursion - finding the best
 * profit we can make on a smaller subarray. For (3), we take the minimum price
 * in the first half and the maximum price in the second half. The best option
 * must be one of those three.
 */
int maximumSingleSellProfit_v2(const Vector<int>& values) {
    /* Base case: If the list has fewer than two elements, then you either can't
     * buy or sell anything or you have to sell at the buy price. Either way you
     * make no profit.
     */
    if (values.size() < 2) {
        return 0;
    }

    int half = values.size() / 2;

    /* Find the max profit buying and selling purely in the first or
     * second half of the list.
     */
    int firstHalfProfit  = maximumSingleSellProfit_v2(values.subList(0, half)); // 不考虑递归，只考虑赋值的话，他的时间复杂度是O(1)
    int secondHalfProfit = maximumSingleSellProfit_v2(values.subList(half)); // 不考虑递归，只考虑赋值的话，他的时间复杂度是O(1)

    /* Find the best buy price in the first half and the best buy price in the
     * second half.
     */  
    int firstMin = values[0];
    for (int i = 1; i < half; i++) {
        firstMin = min(firstMin, values[i]);
    }// 在第1层call stack里，你先无条件假设355和356行执行完毕了，那么这个for循环的时间复杂度是O(n/2)

    // 在最深层的call stack里，这个for循环需要的时间是O(0) 【half为1时】
    // 上一个call stack里，这个操作花费O(1)【half为2时】， 而half最大为n/2

    int secondMax = values[half];

    for (int i = half + 1; i < values.size(); i++) {
        secondMax = max(secondMax, values[i]);
    }// 在第1层call stack里，你先无条件假设355和356行执行完毕了，那么这个for循环的时间复杂度是O(n/2)

    /* The best option is either the max profit purely buying and selling in the
     * first half, or the max profit buying and selling purely in the second half,
     * or by buying in the first half and selling in the second.
     */
    return max({ firstHalfProfit, secondHalfProfit, secondMax - firstMin }); // 无论何时，该代码只花费O(1)的时间
}
// 2024-6-29 00:22:19 他这个代码写的真是太聪明了，太深刻了，真酷

// 2024-6-29 00:39:29 哈哈，我懂了，每个call stack里最多消费O(n/2) + O(n/2)的时间，越往深处的call stack消费的时间就越少
// 大概是        O(n) + O(n/2) + O(n/4) + O(n/8) + O(n/16) + ... + O(n/log2(n)) 的关系
// 对应call stack ①     ②         ③       ④       ⑤       ...    log2(n)
// 第①层call stack总花费时间是O(n)，是因为算出firstMin消费O(n/2) 和 算出secondMax消费O(n/2)，而常数无关紧要，所以时间复杂度就是O(n)
// 然后你看，第①个call stack消费的时间最多，在n趋于无穷的时候，第②③④...log2(n)层call stack消费的时间都是无关紧要的，都不如①消费的时间多
// 所以总时间复杂度是O(n)
