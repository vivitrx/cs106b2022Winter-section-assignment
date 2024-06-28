#include "WhatAreYouDoing.h"
using namespace std;

/* TODO: Read the comments in WhatAreYouDoing.h to see what this function needs to do, then
 * delete this comment.
 *
 * Don't forget about the tokenize function defined in WhatAreYouDoing.h; you'll almost
 * certainly want to use it.
 */
#include <cctype>
#include "stack.h"
#include "strlib.h"
#include "set.h"
Set<string> allEmphasesOf_helper(Set<string>& output, Vector<string> token, Stack<int> code);
Set<string> allEmphasesOf(const string& sentence)
{
    // 预处理
    Vector<string> token = tokenize(toLowerCase(sentence));
    Stack <int> CODE;
    Set<string> OUTPUT = {};
    Set<string>& output = OUTPUT;

    int size = token.size();
    for (int i = 0; i < size; i++)
    {
        if (isalpha(token[i][0]))
        {
            // 说明token[i]是个单词，我应该记录他的编号i，写入stack里，这样可以最大化效率
            CODE.push(i);
        }
    }

    if (CODE.isEmpty())
    {
        OUTPUT.add(sentence);
        return OUTPUT;
    }
    // 预处理完成
    return allEmphasesOf_helper(output, token, CODE);
}

Set<string> allEmphasesOf_helper(Set<string>& output, Vector<string> token, Stack<int> CODE)
{
    // base case 从code里pop()出编号i然后搞大写
    if (CODE.size() == 1)
    {
        Vector<string> upper = token;
        int r = CODE.pop();
        upper[r] = toUpperCase(token[r]);

        string UPper;
        int size = upper.size();
        for (int i = 0; i < size; i++)
        {
            UPper += upper[i];
        }
        string TOken;
        size = token.size();
        for (int i = 0; i < size; i++)
        {
            TOken += token[i];
        }
        // 现在，你有了全部小写的temp
        // 和最后一个单词大写的token
        // 不用多想，全部装进Set就行，重复的内容Set是不会接受的
        output.add(TOken);
        output.add(UPper);
        return output;
    }
    // recursive case
    else
    {
        Vector<string> upper = token;
        int r = CODE.pop();
        upper[r] = toUpperCase(token[r]);

        // string UPper;
        // int size = upper.size();
        // for (int i = 0; i < size; i++)
        // {
        //     UPper += upper[i];
        // }
        // string TOken;
        // size = token.size();
        // for (int i = 0; i < size; i++)
        // {
        //     TOken += token[i];
        // }
        // 现在，你有了全部小写的temp
        // 和最后一个单词大写的token
        // // 不用多想，全部装进Set就行，重复的内容Set是不会接受的
        // output.add(TOken);
        // output.add(UPper);
        allEmphasesOf_helper(output, upper, CODE);
        allEmphasesOf_helper(output, token, CODE);
    }
    return output;
}


/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
STUDENT_TEST("Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello. a",
        "hello. A",
        "HELLO. a",
        "HELLO. A",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello. a"), expected);
}












/* * * * * * Test cases from the starter files below this point. * * * * * */

PROVIDED_TEST("Stress Test: Recursion only branches on words (should take under a second)") {
    /* We're producing a string consisting of fifty copies of the * character. This tokenizes
     * into fifty separate stars. A star is the same whether or not you capitalize it - there
     * is no such thing as an "upper-case" or "lower-case" star. Therefore, your code should
     * not try to form two versions of the sentence, one with the star capitalized and one
     * without, because the two versions will end up being the same and the work to compute
     * both options will dramatically increase the runtime.
     *
     * For reference, if you do try branching the recursion and checking what happens both if
     * you capitalize the star and if you don't, you'll try exploring 2^50 different possible
     * capitalizations. That's 1,125,899,906,842,624 options, and even doing a billion of
     * these a second is going to take over two years to generate them all! And of course,
     * that's all wasted work, since there's only one way to capitalize this sentence, and
     * that's just to leave it as-is.
     *
     * If your code is hanging when this test is running, it likely means that your code is
     * trying to enumerate all of these options. See if you can edit your code so that, if
     * you're given a non-word token, you just leave it as-is and don't change anything.
     */
    string punctuation(50, '*'); // 50 copies of *

    /* The only emphasis is itself. */
    Set<string> expected = {
        punctuation
    };

    EXPECT_EQUAL(allEmphasesOf(punctuation), expected);
}

PROVIDED_TEST("Enumerates all options in a simple case.") {
    Set<string> expected = {
        "hello",
        "HELLO",
    };

    EXPECT_EQUAL(allEmphasesOf("Hello"), expected);
}

PROVIDED_TEST("Each option has the right length.") {
    string sentence = "Hello, world!";
    for (string option: allEmphasesOf(sentence)) {
        EXPECT_EQUAL(option.length(), sentence.length());
    }
}

PROVIDED_TEST("Enumerates all options in a more typical case.") {
    Set<string> expected = {
        "you are?",
        "you ARE?",
        "YOU are?",
        "YOU ARE?"
    };

    EXPECT_EQUAL(allEmphasesOf("You Are?"), expected);
}



// PROVIDED_TEST("Stress test: Generates each option once (should take at most a few seconds)") {  // 该测试已经通过，现在注释掉方便其他题目测试
//     /* This sentence has 13 words in it. There are therefore 2^13 = 8192 possible emphases for
//      * the words there, which is a big number but not so large that the computer can't handle
//      * it if generates each emphasis exactly once.
//      *
//      * On the other hand, if your code tries to generate the same emphases multiple times,
//      * this test may take a very, very long time to complete, and might even appear to freeze
//      * up.
//      *
//      * If your code gets stuck in this test, trace through your code and confirm that you can't
//      * produce the same emphasis multiple times. Check to make sure you aren't, for example,
//      * looping over every token in the input sentence and deciding which one to capitalize
//      * next. The recursion here follows more of an include/exclude type pattern (more like
//      * subsets and combinations) than it does a "which is next?" type pattern (more like
//      * permutations).
//      */
//     string yeats = "Turing and turning in a widening gyre / the falcon cannot hear the falconer.";
//     EXPECT_EQUAL(allEmphasesOf(yeats).size(), 8192);
// }
