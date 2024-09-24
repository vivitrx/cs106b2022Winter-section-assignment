/*
 * CS106B Section Handout Test Harness: Section 2
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include "testing/SimpleTest.h"
#include "set.h"
#include "strlib.h"
using namespace std;

/*
 * See Stanford library's promptUserForFile function to get
 * a file into a stream format:
 * https://web.stanford.edu/dept/cs_edu/resources/cslib_docs/filelib.html#Function:promptUserForFile
 */
Set<string> wordsIn(istream& input) {
    string inputstring;
    Set<string> result;
    getline(input, inputstring);
    string word = "";

    for (int i = 0; i < inputstring.length(); i++) {
        if (inputstring[i] == ' ')
        {
            result.add(word);
            continue;
        }else{
            word += inputstring[i];
        }
    }
    return result;
}

好吧，我想起我在assignment2写过这个题目了，所以我不写了

