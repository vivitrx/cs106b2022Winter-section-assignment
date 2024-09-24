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
#include "map.h"
#include "lexicon.h"
using namespace std;

/*
 * Function: listLegalOrderingsOf
 * -------------------------------
 * Write a function that takes as input a Map representing the
 * prerequisite structure, then lists all possible orders in which
 * you could complete those tasks without violating the
 * prerequisites. The prereqs map is structured so that each key
 * is a task and each value is the set of that task’s immediate prerequisites.
 * See section handout for more details
 */
void listLegalOrderingsOf_helper(Map<string, Set<string>> prereqs,
                                Vector<string> learning_order);

bool is_this_elem_included (string elem, Vector<string> learning_order);

void listLegalOrderingsOf(const Map<string, Set<string>>& prereqs)
{
    Vector<string> learning_order = {"CS106A"};
    Map<string, Set<string>> prereqssssss = prereqs;
    prereqssssss.remove("CS106A");
    listLegalOrderingsOf_helper(prereqssssss, learning_order);
}

void listLegalOrderingsOf_helper(Map<string, Set<string>> prereqs,
                                Vector<string> learning_order)
{
    static int size = prereqs.size();
    if (learning_order.size() == size + 1) // base case
    {
        cout << learning_order << endl;
    }else // recursive case
    {
        for (string present_class : prereqs)
        {
            int flag = 0;

            for (string prerequisite_class : prereqs[present_class])
            {
                if (is_this_elem_included(prerequisite_class, learning_order)) // 如果某课程的全部前置课程都存在于向量learning_order中的话，则该课程就是当下有资格学习的
                {
                    flag = 1;
                }else {
                    flag = 0;
                    break; // 如果集合prereqs[present_class]不是集合learning order的子集，那你就别试了，
                    // 用人话说，prereqs[present_class]（前置课程集合）中肯定有一个课程a，
                    // 这个课程a不存在于learning order（已经修完的课程集合）中，
                    // 前置课程没学完还想学新课程？
                }
            }

            if (flag == 1)
            {
                learning_order += present_class;

                Map<string, Set<string>> new_prereqs = prereqs;
                new_prereqs.remove(present_class);

                listLegalOrderingsOf_helper(new_prereqs, learning_order);
                learning_order.remove(learning_order.size() - 1);
            }
        }
    }
}

bool is_this_elem_included (string elem, Vector<string> learning_order)
{
    for (string i : learning_order)
    {
        if (i == elem)
        {
            return true;
        }
    }

    return false;
}



/* * * * * Provided Tests Below This Point * * * * */

/*
 * Since this is a void function, we don't have a return value to verify with.
 * We will instead just run your code to make sure there is no obvious error.
 */
PROVIDED_TEST("Provided Test: Run the provided example. There should be 16 entries.") {
    Map<string, Set<string>> prereqs = {
        {"CS103", { "CS106A" }},
        {"CS106A", { }},
        {"CS106B", { "CS106A" }},
        {"CS107", { "CS106B" }},
        {"CS109", { "CS103", "CS106B" }},
        {"CS110", { "CS107" }},
        {"CS161", { "CS109" }}
    };
    listLegalOrderingsOf(prereqs);
}
