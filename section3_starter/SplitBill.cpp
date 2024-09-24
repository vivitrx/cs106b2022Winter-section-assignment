/*
 * CS106B Section Handout Test Harness: Section 3
 * ----------------------------------------------
 * These problems have been galvanized from years of
 * section handouts that have been worked on by numerous
 * instructors and TA's. Codified for Qt and Ed by Neel
 * Kishnani for Winter 2022.
 *
 * A huge thank you to Keith Schwarz and Julie Zelenski
 * for creating an amazing testing harness!
 */

#include <iostream>
#include "testing/SimpleTest.h"
#include "testing/TextUtils.h"
#include "set.h"
#include "error.h"
#include "hashmap.h"
using namespace std;

/*
 * Function: listPossiblePayments
 * -------------------------------
 * Write a function that takes as input a total amount of money
 * to pay (in dollars) and a set of all the people who ordered
 * something, then lists off every possible way you could split
 * the bill, assuming everyone pays a whole number of dollars.
 */
void listPossiblePayments_helper(int total,
                                 Set<string> people,
                                 Map <string, int> result);

void listPossiblePayments(int total, const Set<string>& people) {
    listPossiblePayments_helper(total, people, {});
}

void listPossiblePayments_helper(int total,
                                Set<string> people,
                                Map <string, int> result)
{
    static int real_total = total;
    if (result.size() == 3)
    {
        int sum = 0;
        for (string i : result) {
            sum += result[i];
        }
        if (sum == real_total)
        {
            cout << result << endl;
        }
        return;
    }else{
        for (int i = total; i >= 0; i--)
        {
            string man = people.first();
            result.put(man, i);

            // Set<string> new_people = people;
            // new_people.remove(man);

            listPossiblePayments_helper(total - i, people - man, result);
        }
    }
}


/* * * * * Provided Tests Below This Point * * * * */

/*
 * Since this is a void function, we don't have a return value to verify with.
 * We will instead just run your code to make sure there is no obvious error.
 */
PROVIDED_TEST("Provided Test: Run the provided example. There should be 15 entries.") {
    Set<string> s = {"A", "B", "C"};
    listPossiblePayments(4, s);
}
