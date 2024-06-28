#include "HumanPyramids.h"
#include "error.h"
#include "strlib.h"
#include "HashMap.h"
#include "gridlocation.h"
using namespace std;

/* TODO: Refer to HumanPyramids.h for more information about what this function should do.
 * Then, delete this comment.
 */


double weightOnBackOf(int row, int col, int pyramidHeight) {
    static HashMap<GridLocation, double> cache;
    GridLocation gL;
    gL.row = row;
    gL.col = col;
    // 错误检测
    if (row < 0 || col < 0 || row > pyramidHeight - 1 || col > pyramidHeight - 1)
    {
        error("非法参数！越界！");
    }
    // base case
    if (row == 0) // 针对(0,0)
    {
        return 0;
    }
    else if (row == 1) // 针对(1,0)和(1,1)两种情况
    {
        return 80;
    }
    // memoization ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓
    if (cache.containsKey(gL))
    {
        return cache.get(gL);
    }
    // memoization ↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑
    else // recursive case
    {
        if (col == 0)// 左边缘情况
        {
            double result = (160 + weightOnBackOf(row - 1, col, pyramidHeight)) / 2;
            gL.row = row;
            gL.col = col;
            cache.put(gL, result); // memoization
            return result;
        }
        if (col == row)// 右边缘情况
        {
            double result = (160 + weightOnBackOf(row - 1, col - 1, pyramidHeight)) / 2;
            gL.row = row;
            gL.col = col;
            cache.put(gL, result); // memoization
            return result;
        }
        // 中间情况
        double result = (160 + weightOnBackOf(row - 1, col - 1, pyramidHeight)) / 2 + (160 + weightOnBackOf(row - 1, col, pyramidHeight)) / 2;
        gL.row = row;
        gL.col = col;
        cache.put(gL, result); // memoization
        return result;
    }
}

/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */

STUDENT_TEST("高度为5的金字塔，让我看看D，也就是(2,0)的情况.") {
    EXPECT_EQUAL(weightOnBackOf(2, 0, 5), 120);
}

STUDENT_TEST("高度为5的金字塔，让我看看B，也就是(1,0)的情况.") {
    EXPECT_EQUAL(weightOnBackOf(1, 0, 5), 80);
}

STUDENT_TEST("高度为5的金字塔，让我看看E，也就是(2,1)的情况.") {
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

STUDENT_TEST("高度为5的金字塔，让我看看G，也就是(3,0)的情况.") {
    EXPECT_EQUAL(weightOnBackOf(3, 0, 5), 140);
}

STUDENT_TEST("高度为5的金字塔，让我看看H，也就是(3,1)的情况.") {
    EXPECT_EQUAL(weightOnBackOf(3, 1, 5), 340);
}

STUDENT_TEST("高度为5的金字塔，让我看看L，也就是(4,1)的情况.") {
    EXPECT_EQUAL(weightOnBackOf(4, 1, 5), 400);
}



/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Check Person E from the handout.") {
    /* Person E is located at row 2, column 1. */
    EXPECT_EQUAL(weightOnBackOf(2, 1, 5), 240);
}

PROVIDED_TEST("Function reports errors in invalid cases.") {
    EXPECT_ERROR(weightOnBackOf(-1, 0, 10));
    EXPECT_ERROR(weightOnBackOf(10, 10, 5));
    EXPECT_ERROR(weightOnBackOf(-1, 10, 20));
}

PROVIDED_TEST("Stress test: Memoization is implemented (should take under a second)") {
    /* TODO: Yes, we are asking you to make a change to this test case! Delete the
     * line immediately after this one - the one that starts with SHOW_ERROR - once
     * you have implemented memoization to test whether it works correctly.
     */

    /* Do not delete anything below this point. :-) */

    /* This will take a LONG time to complete if memoization isn't implemented.
     * We're talking "heat death of the universe" amounts of time. :-)
     *
     * If you did implement memoization but this test case is still hanging, make
     * sure that in your recursive function (not the wrapper) that your recursive
     * calls are to your new recursive function and not back to the wrapper. If you
     * call the wrapper again, you'll get a fresh new memoization table rather than
     * preserving the one you're building up in your recursive exploration, and the
     * effect will be as if you hadn't implemented memoization at all.
     */
    EXPECT(weightOnBackOf(100, 50, 200) >= 10000);
}

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */



/* TODO: 是的，我们希望你对这个测试用例进行修改！一旦你实现了记忆化，请删除紧接在这行之后的那行代码——那行以 SHOW_ERROR 开头的代码，以测试其是否正确工作。
 去查看你的SuperMemo，标题是：P5 Lecture 8 Recursion 02-04  https://www.simtoco.com/#/albums/video?id=1000791
里面教你如何memoization

*/

/* 请不要删除这行之后的任何内容。:-) */

/* 如果没有实现记忆化，这将需要很长时间才能完成。
 * 我们说的是“宇宙热寂”级别的时间。:-)
 *
 * 如果你已经实现了记忆化，但这个测试用例仍然挂起，请确保在你的递归函数（而不是包装器）中，你的递归调用是调用你的新递归函数，而不是回到包装器。
 * 如果你再次调用包装器，你将得到一个全新的记忆化表，而不是在递归探索中构建的那个，效果就像你根本没有实现记忆化一样。
 */
