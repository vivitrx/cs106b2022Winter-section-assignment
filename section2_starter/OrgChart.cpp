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
#include "map.h"
#include <string>
using namespace std;

string CEO_finder(string person, const Map<string, string>& bosses);

bool areAtSameCompany(const string& p1,
                      const string& p2,
                      const Map<string, string>& bosses)
{
    string CEO1 = CEO_finder(p1, bosses);
    string CEO2 = CEO_finder(p2, bosses);

    if (CEO1 == CEO2)
    {
        return true;
    }else{
        return false;
    }
}

string CEO_finder(string person, const Map<string, string>& bosses)
{
    // base case
    if (bosses.containsKey(person) == false)
    {
        return person; // 说明他就是CEO
    }else{ // recursive case
        string superior = bosses.get(person); // 找到key对应的value
        return CEO_finder(superior, bosses);
    }
}



// Tests from OrgChart.cpp

// Correct (PROVIDED_TEST, line 53) Basic tests for areAtSameCompany

// Passed 1 of 1 tests. Perfecto!

// 2024-6-15 20:22:32 完成！

/* * * * * Provided Tests Below This Point * * * * */

PROVIDED_TEST("Basic tests for areAtSameCompany") {
    Map<string, string> company1 = {
        { "Neel", "Keith" },
        { "Keith", "Mehran" },
        { "Mehran", "John" }, 
        { "John", "Jennifer" }, 
        { "Jennifer", "Persis" }
    };

    Map<string, string> company2 = {
        { "CJ", "Pierre" },
        { "Jack", "Stanley" },
        { "Stanley", "Lisa" },
        { "Lisa", "Janet" },
        { "Janet", "Poonam" }

    };

    EXPECT(areAtSameCompany("Neel", "Jennifer", company1));
    EXPECT(!areAtSameCompany("Neel", "Lisa", company1));
    EXPECT(!areAtSameCompany("CJ", "Keith", company2));
    EXPECT(!areAtSameCompany("Poonam", "Lisa", company1));

}
