#include "DisasterPlanning.h"
using namespace std;

/* TODO: Refer to DisasterPlanning.h for more information about this function.
 * Then, delete this comment.
 */


// 伪代码存档：https://pastebin.com/cBT8fMXc
bool is_allCity_included(Map<string, Set<string>> roadNetwork,
                         Set<string> supplyLocations);

bool helper(Map<string, Set<string>> roadNetwork,
            Map<string, Set<string>> original_roadNetwork,
            int numCities,
            Set<string>& supplyLocations);

bool is_thisCity_s_neighbor_covered(string city,
                                    Map<string, Set<string>> roadNetwork,
                                    Set<string>& supplyLocations);

bool canBeMadeDisasterReady(const Map<string, Set<string>>& roadNetwork,
                            int numCities,
                            Set<string>& supplyLocations) {
    if (numCities < 0) error("");
    if (roadNetwork.size() == 0)
    {
        return true;
    }
    if (numCities == 0 && roadNetwork.size() != 0) return false;

    Map<string, Set<string>> roadNetworkkkkkkkk = roadNetwork;
    Map<string, Set<string>> original_roadNetwork = roadNetwork;
    bool i = helper(roadNetworkkkkkkkk,
                    original_roadNetwork,
                    numCities,
                    supplyLocations);
    return i;
}

bool is_thisCity_covered(
    string city,
    Map<string, Set<string>> original_roadNetwork,
    Set<string>& supplyLocations)
{
    if (supplyLocations.contains(city) == false
        &&
        is_thisCity_s_neighbor_covered(city, original_roadNetwork, supplyLocations) == false)
    {
        return false; // 该city没有被覆盖
    }else{
        return true; // 该city被覆盖了
    }
}

bool helper(Map<string, Set<string>> roadNetwork,
            Map<string, Set<string>> original_roadNetwork,
            int numCities,
            Set<string>& supplyLocations)
{
    // static Map<string, Set<string>> original_roadNetwork = roadNetwork;
    // 孩子们，不要乱用static变量
    // static 变量存储的值会从第一个测试保留到第二个（以及第三四五六个）测试, 这会导致测试错误
    if (numCities >= 0) // base case
    {
        bool i = is_allCity_included(original_roadNetwork, supplyLocations);
        if (i) // 检测所有的城市是否都被覆盖到了,若该检测表达式为TRUE
        {
            return true;
        }
    }

    if (numCities >= 0)
    {
        // for (string city : roadNetwork)
        //     {
                // if (is_thisCity_covered(city, original_roadNetwork, supplyLocations) == true) // recursive case
                // {
                //     continue; // 如果该城市已经被补给站覆盖到，那么就别管这个城市了
                // }
            string city = roadNetwork.firstKey();
                if (is_thisCity_covered(city, original_roadNetwork, supplyLocations) == false){
                    // ***选择给城市本身储存物资***
                    supplyLocations.add(city);
                    Map<string, Set<string>> new_roadNetwork = roadNetwork;
                    for (string neighbor : new_roadNetwork[city]) // 如果city刚刚成为了光荣的补给站，那么他的邻居也都受益，他的邻居自然不用成为补给站
                    {
                        new_roadNetwork.remove(neighbor);
                    }
                    new_roadNetwork.remove(city);

                    if (helper(new_roadNetwork,
                               original_roadNetwork,
                               numCities - 1,
                               supplyLocations) == true) // 如果已经得到TRUE，就大开绿灯
                    {return true;}

                    supplyLocations.remove(city); // 为回溯所做的准备

                    // ***选择给城市的其中一个邻居储存物资，需要for循环***
                    for (string neighbor : roadNetwork[city])
                    {
                        supplyLocations.add(neighbor);

                        Map<string, Set<string>> new_roadNetwork = roadNetwork;
                        for (string neighbor111 : new_roadNetwork[neighbor]) // 如果city刚刚成为了补给站，那么他的邻居也都受益，他的邻居自然不用成为补给站
                        {
                            new_roadNetwork.remove(neighbor111);
                        }
                        new_roadNetwork.remove(neighbor);

                        if (helper(new_roadNetwork,
                                   original_roadNetwork,
                                   numCities - 1,
                                   supplyLocations) == true) // 如果已经得到TRUE，就大开绿灯
                        {return true;}
                        // 为回溯所做的准备
                        supplyLocations.remove(neighbor);
                    }
                }
            // }
    }
    return false; // 如果你检测了roadNetwork里所有的组合，却发现没有一个满足要求的，那说明当前城市规划就是一坨屎
}

bool is_thisCity_s_neighbor_covered(
    string city,
    Map<string, Set<string>> roadNetwork,
    Set<string>& supplyLocations)
{
    int i = 0;
    for (string neighbor : roadNetwork[city])
    {
        if (supplyLocations.contains(neighbor))
        {
            i = 1;
            return true;
        }else{
            i = 0;
        }
    }
    if (i == 1)
    {
        return true;
    }else{
        return false;
    }
}


bool is_allCity_included(Map<string, Set<string>> roadNetwork,
                         Set<string> supplyLocations)
{
    int flag = 1;
    for (string cityy : roadNetwork)
    {
        if (supplyLocations.contains(cityy))
        {
            flag = 1;
            continue;
        }else
        {
            flag = 0; // 城市cityy本身没有补给不代表就没有希望了

            // 检测cityy的邻居城市在不在supplyLocations中
            if (roadNetwork[cityy].isEmpty())
            {
                flag = 0;
                break;
            }else
            {
                for (string neighbor : roadNetwork[cityy])
                {
                    if(supplyLocations.contains(neighbor))
                    {
                        flag = 1; // 只要cityy的至少一个邻居城市有补给站，那么城市cityy就能被支援到
                        break;
                    }else{
                        flag = 0;
                    }
                }
            }


            if (flag == 0) // 只要roadNetwork中有一个城市无法被补给到，那么就全部完蛋
            {
                return false;
            }
        }
    }
    // 总检定
    if (flag == 1)
    {
        return true;
    }else
    {
        return false;
    }
}


/* * * * * * * Test Helper Functions Below This Point * * * * * */
#include "GUI/SimpleTest.h"

/* This is a helper function that's useful for designing test cases. You give it a Map
 * of cities and what they're adjacent to, and it then produces a new Map where if city
 * A links to city B, then city B links back to city A. We recommend using this helper
 * function when writing tests, though you won't need it in your implementation of the main
 * canBeMadeDisasterReady function.
 */
Map<string, Set<string>> makeSymmetric(const Map<string, Set<string>>& source) {
    Map<string, Set<string>> result = source;

    for (const string& from: source) {
        for (const string& to: source[from]) {
            result[from] += to;
            result[to] += from;
        }
    }

    return result;
}

/* This helper function tests whether a city has been covered by a set of supply locations
 * and is used by our testing code. You're welcome to use it in your tests as well!
 */
bool isCovered(const string& city,
               const Map<string, Set<string>>& roadNetwork,
               const Set<string>& supplyLocations) {
    if (supplyLocations.contains(city)) return true;

    for (string neighbor: roadNetwork[city]) {
        if (supplyLocations.contains(neighbor)) return true;
    }

    return false;
}

/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Add your own custom tests here! */
STUDENT_TEST("Stress test: 6 x 6 grid. (This should take at most a few seconds.)") {
    Map<string, Set<string>> grid;

    /* Build the grid. */
    char maxRow = 'F';
    int  maxCol = 6;
    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            if (row != maxRow) {
                grid[row + to_string(col)] += (char(row + 1) + to_string(col));
            }
            if (col != maxCol) {
                grid[row + to_string(col)] += (char(row) + to_string(col + 1));
            }
        }
    }
    grid = makeSymmetric(grid);

    Set<string> locations;
    EXPECT(canBeMadeDisasterReady(grid, 10, locations));
}




STUDENT_TEST("串联甲烷城市(含补给点精准测试).") {
    /*
  1     2
  |     |
3-4-5-6-7-8
  |     |
  9    10
*/
    Map<string, Set<string>> map = makeSymmetric({
        { "1", { "4" } },
        { "2", { "7"} },
        { "3", { "4"} },
        { "4", { "1", "3", "5", "9"} },
        { "5", { "4", "6"} },
        { "6", { "5", "7"} },
        { "7", { "2", "6", "8", "10"} },
        { "8", { "7"} },
        { "9", { "4"} },
        { "10", { "7"} }
    });

    Set<string> locations0;
    Set<string> expected = { "4", "7" };

    EXPECT(canBeMadeDisasterReady(map, 2, locations0));
    EXPECT_EQUAL(locations0, expected);
}









/* * * * * Provided Tests Below This Point * * * * */
PROVIDED_TEST("Works for four disconnected cities.") {
    Map<string, Set<string>> map = makeSymmetric({
        { "A", { } },
        { "B", { } },
        { "C", { } },
        { "D", { } }
    });

    Set<string> locations0, locations1, locations2, locations3, locations4;
    EXPECT(canBeMadeDisasterReady(map, 4, locations4));
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(!canBeMadeDisasterReady(map, 2, locations2));
    EXPECT(!canBeMadeDisasterReady(map, 3, locations3));
}

PROVIDED_TEST("Works for map with two linked cities.") {
    Map<string, Set<string>> map = makeSymmetric({
        { "A", { "B" } },
        { "B", {     } }
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));
}

PROVIDED_TEST("Works for map with one city.") {
    Map<string, Set<string>> map = makeSymmetric({
        { "Solipsist", {} }
    });

    /* Shouldn't matter how many cities we use, as long as it isn't zero! */
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT( canBeMadeDisasterReady(map, 1, locations1));
    EXPECT( canBeMadeDisasterReady(map, 2, locations2));
}




PROVIDED_TEST("Reports an error if numCities < 0") {
    Set<string> supply;
    EXPECT_ERROR(canBeMadeDisasterReady({}, -137, supply));
}

PROVIDED_TEST("Works for map with no cities.") {
    Set<string> locations;

    /* The number of cities we use really doesn't matter here. */
    EXPECT(canBeMadeDisasterReady({}, 0, locations));
    EXPECT_EQUAL(locations.size(), 0);

    EXPECT(canBeMadeDisasterReady({}, 137, locations));
    EXPECT_EQUAL(locations.size(), 0);
}


PROVIDED_TEST("Works for map with one city, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "Solipsist", {} }
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));

    /* Don't check locations0; since the function returned false, the values there
     * can be anything.
     */
    Set<string> expected = { "Solipsist" };
    EXPECT_EQUAL(locations1, expected);
    EXPECT_EQUAL(locations2, expected);
}



PROVIDED_TEST("Works for map with two linked cities, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
         { "A", { "B" } },
    });

    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(canBeMadeDisasterReady(map, 2, locations2));

    EXPECT_EQUAL(locations1.size(), 1);
    EXPECT(locations1.isSubsetOf({"A", "B"}));

    EXPECT(locations2.size() <= 2);
    EXPECT(locations2.isSubsetOf({"A", "B"}));
}


PROVIDED_TEST("Works for four disconnected cities, and produces output.") {
    Map<string, Set<string>> map = makeSymmetric({
        { "A", { } },
        { "B", { } },
        { "C", { } },
        { "D", { } }
    });

    Set<string> locations0, locations1, locations2, locations3, locations4;
    EXPECT(!canBeMadeDisasterReady(map, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(map, 1, locations1));
    EXPECT(!canBeMadeDisasterReady(map, 2, locations2));
    EXPECT(!canBeMadeDisasterReady(map, 3, locations3));
    EXPECT(canBeMadeDisasterReady(map, 4, locations4));

    Set<string> expected = { "A", "B", "C", "D" };
    EXPECT_EQUAL(locations4, expected);
}

PROVIDED_TEST("Can solve ethene example, regardless of ordering.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *             *
     *             |
     *        * -- * -- * -- *
     *                  |
     *                  *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * cities. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* Ethene arrangement:
         *
         *        0
         *       1234
         *         5
         */
        Map<string, Set<string>> map = makeSymmetric({
            { cities[2], { cities[0], cities[1], cities[3] } },
            { cities[3], { cities[4], cities[5] } }
        });

        /* We should be able to cover everything with two cities:
         * city 2 and city 3.
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Can solve ethene example, regardless of ordering, and produces output.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *             *
     *             |
     *        * -- * -- * -- *
     *                  |
     *                  *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * cities. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* Ethene arrangement:
         *
         *        0
         *       1234
         *         5
         */
        Map<string, Set<string>> map = makeSymmetric({
            { cities[2], { cities[0], cities[1], cities[3] } },
            { cities[3], { cities[4], cities[5] } }
        });

        /* We should be able to cover everything with two cities:
         * city 2 and city 3.
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        EXPECT_EQUAL(chosen.size(), 2);
        EXPECT(chosen.contains(cities[2]));
        EXPECT(chosen.contains(cities[3]));

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Works for six cities in a line, regardless of order.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *        * -- * -- * -- * -- * -- *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * cities in a line. If your code is able to solve the problem correctly
     * for all of those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* Linear arrangement. */
        Map<string, Set<string>> map;
        for (int i = 1; i + 1 < cities.size(); i++) {
            map[cities[i]] = { cities[i - 1], cities[i + 1] };
        }

        map = makeSymmetric(map);

        /* We should be able to cover everything with two cities, specifically,
         * the cities one spot in from the two sides.
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Works for six cities in a line, regardless of order, and produces output.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *        * -- * -- * -- * -- * -- *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * cities in a line. If your code is able to solve the problem correctly
     * for all of those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F" };
    do {
        /* Linear arrangement. */
        Map<string, Set<string>> map;
        for (int i = 1; i + 1 < cities.size(); i++) {
            map[cities[i]] = { cities[i - 1], cities[i + 1] };
        }

        map = makeSymmetric(map);

        /* We should be able to cover everything with two cities, specifically,
         * the cities one spot in from the two sides.
         */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        EXPECT_EQUAL(chosen.size(), 2);
        EXPECT(chosen.contains(cities[1]));
        EXPECT(chosen.contains(cities[4]));

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

/* The "Don't Be Greedy" sample world. */
const Map<string, Set<string>> kDontBeGreedy = makeSymmetric({
    { "A", { "B" } },
    { "B", { "C", "D" } },
    { "C", { "D" } },
    { "D", { "F", "G" } },
    { "E", { "F" } },
    { "F", { "G" } },
});

PROVIDED_TEST("Solves \"Don't be Greedy\" from the handout.") {
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 1, locations1));
    EXPECT( canBeMadeDisasterReady(kDontBeGreedy, 2, locations2));
}

PROVIDED_TEST("Solves \"Don't be Greedy\" from the handout, and produces output.") {
    Set<string> locations0, locations1, locations2;
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 0, locations0));
    EXPECT(!canBeMadeDisasterReady(kDontBeGreedy, 1, locations1));
    EXPECT( canBeMadeDisasterReady(kDontBeGreedy, 2, locations2));

    Set<string> expected = {"B", "F"};
    EXPECT_EQUAL(locations2, expected);
}

PROVIDED_TEST("Solves \"Don't be Greedy,\" regardless of ordering, and produces output.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over the cities when making decisions is sensitive
     * to the order of those cities' names. This test looks at a map like
     * this one, trying out all possible orderings of the city names:
     *
     *     0       4
     *     |       |
     *     1 - 2 - 3
     *      \ / \ /
     *       5   6
     *
     * There are 7! = 5,040 possible permutations of the ordering of these seven
     * cities. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly
     * covering and uncovering cities at each step. On the other hand, if
     * your code runs into issues here, it may indicate that the way in which
     * you're covering and uncovering cities accidentally uncovers a city that
     * you have previously covered.
     */
    Vector<string> cities = { "A", "B", "C", "D", "E", "F", "G" };
    do {
        Map<string, Set<string>> map = makeSymmetric({
            { cities[1], { cities[0], cities[2], cities[5] } },
            { cities[2], { cities[3], cities[5], cities[6] } },
            { cities[3], { cities[4], cities[6] } },
        });

        /* We should be able to cover everything with two cities. */
        Set<string> chosen;
        EXPECT(canBeMadeDisasterReady(map, 2, chosen));

        /* Those cities should be 1 and 3. */
        EXPECT_EQUAL(chosen, { cities[1], cities[3] });

        /* We should not be able to cover everything with one city. */
        chosen.clear();
        EXPECT(!canBeMadeDisasterReady(map, 1, chosen));
    } while (next_permutation(cities.begin(), cities.end()));
}

PROVIDED_TEST("Stress test: 6 x 6 grid. (This should take at most a few seconds.)") {
    Map<string, Set<string>> grid;

    /* Build the grid. */
    char maxRow = 'F';
    int  maxCol = 6;
    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            if (row != maxRow) {
                grid[row + to_string(col)] += (char(row + 1) + to_string(col));
            }
            if (col != maxCol) {
                grid[row + to_string(col)] += (char(row) + to_string(col + 1));
            }
        }
    }
    grid = makeSymmetric(grid);

    Set<string> locations;
    EXPECT(canBeMadeDisasterReady(grid, 10, locations));
}

PROVIDED_TEST("Stress test: 6 x 6 grid, with output. (This should take at most a few seconds.)") {
    Map<string, Set<string>> grid;

    /* Build the grid. */
    char maxRow = 'F';
    int  maxCol = 6;
    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            if (row != maxRow) {
                grid[row + to_string(col)] += (char(row + 1) + to_string(col));
            }
            if (col != maxCol) {
                grid[row + to_string(col)] += (char(row) + to_string(col + 1));
            }
        }
    }
    grid = makeSymmetric(grid);

    Set<string> locations;
    EXPECT(canBeMadeDisasterReady(grid, 10, locations));

    for (char row = 'A'; row <= maxRow; row++) {
        for (int col = 1; col <= maxCol; col++) {
            EXPECT(isCovered(row + to_string(col), grid, locations));
        }
    }
}

