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
#include "lexicon.h"
#include <string>
#include "set.h"
using namespace std;

#include "testing/SimpleTest.h"

int find_subword_in_Lexicon(string current_word, const Lexicon& Lexicon);
string mostXzibitWord(const Lexicon& words) {
    string winner = "";
    int current_word_count = 0;
    int winner_word_count = 0;
    for (string current_word : words)
    {
        current_word_count = find_subword_in_Lexicon(current_word, words);
        if (current_word_count > winner_word_count)
        {
            winner = current_word;
            winner_word_count = current_word_count;
        }

    }
    return winner;
}

int find_subword_in_Lexicon(string current_word, const Lexicon& Lexicon)
{
    Set<string> subword_set;

    // 先想办法获取current_word的所有substr
    for (int i = 0; i <= current_word.length() - 1; i++) {
        for (int j = 1; j <= current_word.length() - i; j++) {
            string subword = current_word.substr(i,j); // 找出current_word的一个子串subword
            if (Lexicon.contains(subword) == true)
            {
                subword_set.add(subword);
            }
        }
    }
    return subword_set.size();
}
/* * * * * Provided Tests Below This Point * * * * */

static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

PROVIDED_TEST("Example from handout") {
    Lexicon& lex = sharedLexicon();
    EXPECT_EQUAL(mostXzibitWord(lex), "foreshadowers");
}
