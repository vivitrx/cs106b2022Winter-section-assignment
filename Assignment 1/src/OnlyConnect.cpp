/* File: OnlyConnect.cpp
 *
 * TODO: Edit these comments to describe anything interesting or noteworthy in your implementation.
 *
 * TODO: Edit these comments to leave a puzzle for your section leader to solve!
 */
#include "OnlyConnect.h"
#include "GUI/SimpleTest.h"


/*
2024年5月10日15:42:21，这次你挑战递归失败了，你应该去学完CS106X的递归再来挑战，也就是说，你要学完lecture9再来

简单说一下这次思路：

string onlyConnectize(string phrase)传入一个phrase。
用数据结构vector存储大写辅音字母
Vector vector<>
string onlyConnectize(string phrase)
{
    if (phrase[0] == 辅音)
    {
        vector.add[phrase[0]]  // 这个逻辑是有问题的，当你新进行一次递归调用的时候，就会创造一个新的vector，这样你永远都无法把2个及以上的大写辅音传递给最开始的vector
        再调用一次onlyConnectize(phrase)
    }

    if (phrase[0] != 辅音)
    {
        从phrase中删除phrase[0]
        再调用一次onlyConnectize(phrase)
    }

    return (强制转换成string)vector
}


你这个写法错误在你用了数据结构vector

*/
using namespace std;


int isConsonant(string);

string onlyConnectize(string phrase){
    string OC = "";
    //base case, return 是辅音就大写
    if (phrase.length() == 1 && isConsonant(phrase) == 1)
    {
        return toUpperCase(phrase);
    }
    // recursive case, 把phrase分解成phrase[0] + substr(1, phrase[phrase.length(0)] - 1)
    if (phrase.length() > 1)
    {
        OC += onlyConnectize(phrase.substr(0, 1)) + onlyConnectize(phrase.substr(1, phrase[phrase.length()] - 1));
    }
    return OC;
}

int isConsonant(string sub_word)
{
    // 检查是否是辅音
    string consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ";
    int index = stringIndexOf(consonants, sub_word);
    if (index != -1)
    {
        return 1; //成功，sub_word在consonants中出现了
    } else
    {
        return 0; //失败
    }
}




/* * * * * * Provided Test Cases * * * * * */

PROVIDED_TEST("Converts lower-case to upper-case.") {
    EXPECT_EQUAL(onlyConnectize("lowercase"), "LWRCS");
    EXPECT_EQUAL(onlyConnectize("uppercase"), "PPRCS");
}

PROVIDED_TEST("Handles non-letter characters properly.") {
    EXPECT_EQUAL(onlyConnectize("2.718281828459045"), "");
    EXPECT_EQUAL(onlyConnectize("'Hi, Mom!'"), "HMM");
}

PROVIDED_TEST("Handles single-character inputs.") {
    EXPECT_EQUAL(onlyConnectize("A"), "");
    EXPECT_EQUAL(onlyConnectize("+"), "");
    EXPECT_EQUAL(onlyConnectize("Q"), "Q");
}

/* TODO: You will need to add your own tests into this suite of test cases. Think about the sorts
 * of inputs we tested here, and, importantly, what sorts of inputs we *didn't* test here. Some
 * general rules of testing:
 *
 *    1. Try extreme cases. What are some very large cases to check? What are some very small cases?
 *
 *    2. Be diverse. There are a lot of possible inputs out there. Make sure you have tests that account
 *       for cases that aren't just variations of one another.
 *
 *    3. Be sneaky. Don't just try standard inputs. Try weird ones that you wouldn't expect anyone to
 *       actually enter, but which are still perfectly legal.
 *
 * Happy testing!
 */






