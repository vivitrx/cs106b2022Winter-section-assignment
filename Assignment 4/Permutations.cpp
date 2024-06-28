#include "Permutations.h"
using namespace std;

/* Returns all permutations of the given input string.
 *
 * NOTE: THE INITIAL IMPLEMENTATION PROVIDED HERE IS INCORRECT. You will need
 * to isolate the bug by using the debugger, then answer some questions about
 * why this code is incorrect. Remember that the error consists purely of the
 * addition of a single extra character; you shouldn't need to do any major
 * surgery to repair this function.
 *
 * Should we have used pass-by-const-reference here? Probably. That itself
 * isn't the error, but it is related to what went wrong here.
 */
/* 返回给定输入字符串的所有排列。
 *
 * 注意：这里提供的初始实现是错误的。你需要使用调试器找出错误，
 * 然后回答一些关于此代码为何错误的问题。请记住，错误仅仅是由于添加了一个多余的字符；
 * 你不需要对这个函数进行大手术来修复它。
 *
 * 我们是否应该在这里使用按常量引用传递？可能是的。这本身不是错误，
 * 但它与出错的原因有关。
 */
Set<string> permutationsRec(string str, string chosen) {
    /* Base Case: If there are no remaining characters left to consider, then
     * the only permutation possible is the single permutation consisting of
     * what we already committed to.
     */
    /* 基本情况：如果没有剩余的字符需要考虑，那么唯一可能的排列
     * 就是我们已经承诺的单一排列。
     */
    if (str == "") {
        return { chosen };
    }
    /* Recursive Case: Some character has to be the next one in the permutation.
     * Which one should it be? Let's try all possible options and see what we
     * find.
     */
    /* 递归情况：某个字符必须是排列中的下一个字符。
     * 应该是哪个字符？让我们尝试所有可能的选项，看看会发现什么。
     */
    else {
        /* Hold all permutations we find. */
        /* 保存我们找到的所有排列。 */
        Set<string> result;
        for (int i = 0; i < str.size(); i++) {
            /* Form a new string of all the remaining letters by grabbing everything
             * up to but not including the current character, then everything after
             * the current character.
             */
            /* 通过抓取当前字符之前的所有字符和当前字符之后的所有字符，
             * 形成一个新的剩余字母字符串。
             */
            char ch = str[i];
            string remaining = str.substr(0, i) + str.substr(i + 1);

            /* Find all permutations we can make with this choice and add them into
             * the result.
             */
            /* 找到我们可以用这个选择做出的所有排列并将它们添加到结果中。 */
            Set<string> thisOption = permutationsRec(remaining, chosen += ch); // 错误在这里！他先赋值再传递了！所以在当前的call stack，chosen就已经改变了。
            result += thisOption;
        }

        /* We've now tried all options, so let's return what we came up with. */
        /* 我们现在已经尝试了所有选项，所以返回我们的结果。 */
        return result;
    }
}

Set<string> permutationsOf(const string& str) {
    return permutationsRec(str, "");
}






/* * * * * * Test Cases * * * * * */

#include "GUI/SimpleTest.h"

PROVIDED_TEST("最简单的测试.") {
    Set<string> result = {"ab", "ba"};
    EXPECT_EQUAL(permutationsOf("ab"), result);
}
