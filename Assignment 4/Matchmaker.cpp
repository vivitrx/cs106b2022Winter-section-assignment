#include "Matchmaker.h"
using namespace std;

//Milestone One: Find Perfect Matchings 里程碑一：找到完美匹配

bool helper(Map<string, Set<string>> possibleLinks, Set<Pair>& matching, int size);
bool hasPerfectMatching(const Map<string, Set<string>>& possibleLinks,
                        Set<Pair>& matching)
{
    if (possibleLinks.size() % 2 != 0) // 如果是奇数
    {
        return false;
    }

    for (string i : possibleLinks) // 寻找孤儿
    {
        if (possibleLinks[i].size() == 0)
        {
            return false;
        }
    }

    // 如果这些都不是，那么欢迎你进入漫长的剪枝优化过程
    int size = possibleLinks.size();
    Map<string, Set<string>> posboLink = possibleLinks;
    return helper(posboLink, matching, size);
}


bool helper(Map<string, Set<string>> possibleLinks, Set<Pair>& matching, int size)
{

    if (matching.size() * 2 == size)
    {
        return true;
    }else
    {
        string man = possibleLinks.firstKey();

        Map<string, Set<string>> new_possibleLinks = possibleLinks;
        new_possibleLinks.remove(man);

        for (string pair_man : new_possibleLinks)
        {
            if (possibleLinks[man].contains(pair_man)) // 如果pair_man和man配对成功
            {
                // 寻找在该子树下的其他可能性
                Pair greek1(man, pair_man);
                matching.add(greek1); // matching.建立联系(man, pairman);

                Map<string, Set<string>> new_new_possibleLinks = new_possibleLinks;
                new_new_possibleLinks.remove(pair_man);
                if (helper(new_new_possibleLinks, matching, size) == true) // 这里的意思是，如果我们找到最后，成功找到了perfect match，
                {                                                       // 那么我们应该大开绿灯，确保最后一个call stack的结果成功返回到main()中
                    return true;
                }

                // 失败了，该回溯了
                matching.remove(greek1);
            }
        }
    }
    return false;
}

// Milestone One ↑↑↑↑↑↑↑↑







// 伪代码存档：https://pastebin.com/f2c0GVYM
Set<Pair> maxi_helper(
    Map<string, Map<string, int>> possibleLinks,
    Set<Pair> current_match,
    int current_weight,
    Set<Pair>& winner_match,
    int& winner_weight);

Set<Pair> maximumWeightMatching(const Map<string, Map<string, int>>& possibleLinks)
{
    Map<string, Map<string, int>> possibleLinkssssssssss = possibleLinks;
    Set<Pair> winner_match = {};
    int winner_weight = 0;
    return maxi_helper(possibleLinkssssssssss, {}, 0, winner_match, winner_weight);
}

Set<Pair> maxi_helper(
    Map<string, Map<string, int>> possibleLinks,
    Set<Pair> current_match,
    int current_weight,
    Set<Pair>& winner_match,
    int& winner_weight)
{
    if (possibleLinks.isEmpty()) // base case
    {
        return winner_match;
    }else{ // recurisve case
        string man = possibleLinks.firstKey(); // 获取possibleLinks中的first()元素man;

        Map<string, Map<string, int>> new_possibleLinks = possibleLinks;
        new_possibleLinks.remove(man);

        for (string pair_man : new_possibleLinks)
        {
            if (possibleLinks[man].containsKey(pair_man)) // if (man 和 pair_man可以配对)
            {
                Pair greek1(man, pair_man);
                current_match.add(greek1); // current_match是一个Set<Pair>

                auto temp = possibleLinks[man];
                int weight_OF_man_AND_pairman = temp.get(pair_man); /*找出man和pair_man的权重*/;

                current_weight += weight_OF_man_AND_pairman; // 关键语句，我们将man配对pairman的权重加入到了current_weight中
                if (current_weight > winner_weight)
                {
                    winner_weight = current_weight;
                    winner_match = current_match;
                }

                Map<string, Map<string, int>> new_new_possibleLinks = new_possibleLinks;
                new_new_possibleLinks.remove(pair_man);

                // 该深入探索了，另外，只有配队成功才应该深入探索
                maxi_helper(new_new_possibleLinks,
                            current_match,
                            current_weight,
                            winner_match,
                            winner_weight); // 递归点
                // 开始回溯
                current_match.remove(greek1);
                current_weight -= weight_OF_man_AND_pairman;
            }
        }
        maxi_helper(new_possibleLinks,
                    current_match,
                    current_weight,
                    winner_match,
                    winner_weight); // 递归点
    }
    return winner_match; // 程序的结束点
}

/* * * * * Test Cases Below This Point * * * * */

namespace {
/* Utility to go from a list of triples to a world. */
struct WeightedLink {
    string from;
    string to;
    int cost;
};
Map<string, Map<string, int>> fromWeightedLinks(const Vector<WeightedLink>& links) {
    Map<string, Map<string, int>> result;
    for (const auto& link: links) {
        result[link.from][link.to] = link.cost;
        result[link.to][link.from] = link.cost;
    }
    return result;
}

/* Pairs to world. */
Map<string, Set<string>> fromLinks(const Vector<Pair>& pairs) {
    Map<string, Set<string>> result;
    for (const auto& link: pairs) {
        result[link.first()].add(link.second());
        result[link.second()].add(link.first());
    }
    return result;
}

/* Checks if a set of pairs forms a perfect matching. */
bool isPerfectMatching(const Map<string, Set<string>>& possibleLinks,
                       const Set<Pair>& matching) {
    /* Need to check that
         *
         * 1. each pair is indeed a possible link,
         * 2. each person appears in exactly one pair.
         */
    Set<string> used;
    for (Pair p: matching) {
        /* Are these folks even in the group of people? */
        if (!possibleLinks.containsKey(p.first())) return false;
        if (!possibleLinks.containsKey(p.second())) return false;

        /* If these people are in the group, are they linked? */
        if (!possibleLinks[p.first()].contains(p.second()) ||
            !possibleLinks[p.second()].contains(p.first())) {
            return false;
        }

        /* Have we seen them before? */
        if (used.contains(p.first()) || used.contains(p.second())) {
            return false;
        }

        /* Add them both. */
        used += p.first();
        used += p.second();
    }

    /* Confirm that's everyone. */
    return used.size() == possibleLinks.size();
}
}

#include "GUI/SimpleTest.h"




PROVIDED_TEST("hasPerfectMatching works on a world with just one person.") {
    /* The world is just a single person A, with no others. How sad. :-(
     *
     *                 A
     *
     * There is no perfect matching.
     */

    Set<Pair> unused;
    EXPECT(!hasPerfectMatching({ { "A", {} } }, unused));
}

PROVIDED_TEST("hasPerfectMatching works on an empty set of people.") {
    /* There actually is a perfect matching - the set of no links meets the
     * requirements.
     */
    Set<Pair> unused;
    EXPECT(hasPerfectMatching({}, unused));
}



PROVIDED_TEST("hasPerfectMatching works on a world with two linked people.") {
    /* This world is a pair of people A and B. There should be a perfect matching.
     *
     *               A -- B
     *
     * The matching is {A, B}
     */
    auto links = fromLinks({
        { "A", "B" }
    });

    Set<Pair> unused;
    EXPECT(hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a world with two linked people, and produces output.") {
    /* This world is a pair of people A and B. There should be a perfect matching.
     *
     *               A -- B
     *
     * The matching is {A, B}
     */
    auto links = fromLinks({
        { "A", "B" }
    });

    Set<Pair> expected = {
        { "A", "B" }
    };

    Set<Pair> matching;
    EXPECT(hasPerfectMatching(links, matching));
    EXPECT_EQUAL(matching, expected);
}



PROVIDED_TEST("hasPerfectMatching works on a triangle of people.") {
    /* Here's the world:
     *
     *               A --- B
     *                \   /
     *                 \ /
     *                  C
     *
     * There is no perfect matching here, unfortunately.
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "A" }
    });

    Set<Pair> unused;
    EXPECT(!hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a square of people.") {
    /* Here's the world:
     *
     *               A --- B
     *               |     |
     *               |     |
     *               D --- C
     *
     * There are two different perfect matching here: AB / CD, and AD/BD.
     * Either will work.
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "A" }
    });

    Set<Pair> unused;
    EXPECT(hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a square of people, and produces output.") {
    /* Here's the world:
     *
     *               A --- B
     *               |     |
     *               |     |
     *               C --- D
     *
     * There are two different perfect matching here: AB / CD, and AC/BC.
     * Either will work.
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "A" }
    });

    Set<Pair> matching;
    EXPECT(hasPerfectMatching(links, matching));
    EXPECT(isPerfectMatching(links, matching));
}

PROVIDED_TEST("hasPerfectMatching works on a pentagon of people.") {
    /* Here's the world:
     *
     *               A --- B
     *             /       |
     *            E        |
     *             \       |
     *               D --- C
     *
     * There is no perfect matching here, since the cycle has odd
     * length.
     */
    auto links = fromLinks({
        { "A", "B" },
        { "B", "C" },
        { "C", "D" },
        { "D", "E" },
        { "E", "A" }
    });

    Set<Pair> unused;
    EXPECT(!hasPerfectMatching(links, unused));
}

PROVIDED_TEST("hasPerfectMatching works on a line of six people.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *
     *
     *        * -- * -- * -- * -- * -- *
     *
     *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
            { people[0], people[1] },
            { people[1], people[2] },
            { people[2], people[3] },
            { people[3], people[4] },
            { people[4], people[5] }
        });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a more complex negative example.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *
     *         *        *
     *          \      /
     *           * -- *
     *          /      \
     *         *        *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
                                                    { people[0], people[2] },
                                                    { people[1], people[2] },
                                                    { people[2], people[3] },
                                                    { people[3], people[4] },
                                                    { people[3], people[5] },
                                                    });

        Set<Pair> matching;
        EXPECT(!hasPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a more complex positive example.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *               *
     *               |
     *               *
     *              / \
     *             *---*
     *            /     \
     *           *       *
     *
     * There are 6! = 720 possible permutations of the ordering of these
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
                                                    { people[0], people[1] },
                                                    { people[1], people[2] },
                                                    { people[2], people[3] },
                                                    { people[3], people[1] },
                                                    { people[2], people[4] },
                                                    { people[3], people[5] },
                                                    });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching works on a caterpillar.") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *         *---*---*
     *         |   |   |
     *         *   *   *
     *
     * There are 6! = 720 possible permutations of the ordering of these six
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        Map<string, Set<string>> links = fromLinks({
                                                    { people[0], people[1] },
                                                    { people[1], people[2] },
                                                    { people[0], people[3] },
                                                    { people[1], people[4] },
                                                    { people[2], people[5] },
                                                    });

        Set<Pair> matching;
        EXPECT(hasPerfectMatching(links, matching));
        EXPECT(isPerfectMatching(links, matching));
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("hasPerfectMatching stress test: negative example (should take under a second).") {
    /* Here, we're giving a "caterpillar" of people, like this:
     *
     *    *   *   *   *     *   *
     *    |   |   |   |     |   |
     *    *---*---*---* ... *---*
     *    |   |   |   |     |   |
     *    *   *   *   *     *   *
     *
     * This doesn't have a perfect matching, However, it may take some searching
     * to confirm this is the case. At this size, however, it should be
     * almost instanteous to find the solution, since the search space is fairly
     * small and most "wrong" decisions can be detected quickly.
     *
     * On the other hand, if your implementation repeatedly constructs the same
     * matchings over and over again, or keeps exploring even when a person who
     * couldn't be paired with the current setup is found, then the number of
     * options you need to consider will be too large for your computer to handle
     * in any reasonable time.
     *
     * If you're passing the other tests and this test hangs, double-check your
     * code to make sure you aren't repeatedly constructing the same matchings
     * multiple times.
     */

    /* Number of "body segments". */
    const int kRowSize = 10;

    Vector<Pair> links;
    for (int i = 0; i < kRowSize - 1; i++) {
        links.add({ to_string(i), to_string(i + 1) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + kRowSize) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + 2 * kRowSize) });
    }

    Set<Pair> matching;
    EXPECT(!hasPerfectMatching(fromLinks(links), matching));
}

PROVIDED_TEST("hasPerfectMatching stress test: positive example (should take under a second).") {
    /* Here, we're giving a "millipede" of people, like this:
     *
     *    *---*---*---* ... *---*
     *    |   |   |   |     |   |
     *    *   *   *   *     *   *
     *
     * This always has a perfect matching, which is found by pairing each person
     * with the person directly below them. However, it may take some searching
     * to find this particular configuration. At this size, however, it should be
     * almost instanteous to find the solution, since the search space is fairly
     * small and most "wrong" decisions can be detected quickly.
     *
     * On the other hand, if your implementation repeatedly constructs the same
     * matchings over and over again, or keeps exploring even when a person who
     * couldn't be paired with the current setup is found, then the number of
     * options you need to consider will be too large for your computer to handle
     * in any reasonable time.
     *
     * If you're passing the other tests and this test hangs, double-check your
     * code to make sure you aren't repeatedly constructing the same matchings
     * multiple times.
     */

    /* Number of "body segments". */
    const int kRowSize = 10;

    Vector<Pair> links;
    for (int i = 0; i < kRowSize - 1; i++) {
        links.add({ to_string(i), to_string(i + 1) });
    }
    for (int i = 0; i < kRowSize; i++) {
        links.add({ to_string(i), to_string(i + kRowSize) });
    }

    Set<Pair> matching;
    EXPECT(hasPerfectMatching(fromLinks(links), matching));
    EXPECT(isPerfectMatching(fromLinks(links), matching));
}



//////////////////////////////////////maximumWeightMatching test
//////////////////////////////////////maximumWeightMatching test
//////////////////////////////////////maximumWeightMatching test

PROVIDED_TEST("maximumWeightMatching: Works on a line of three people.") {
    /* This world:
     *
     *  A --- B --- C
     *     1     2
     *
     * Best option is to pick B -- C.
     */
    auto links = fromWeightedLinks({
                                    { "A", "B", 1 },
                                    { "B", "C", 2 },
                                    });

    /* Should pick B--C. */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works for empty group.") {
    EXPECT_EQUAL(maximumWeightMatching({}), {});
}

PROVIDED_TEST("maximumWeightMatching: Works for group of one person.") {
    Map<string, Map<string, int>> links = {
        { "A", {} }
    };

    EXPECT_EQUAL(maximumWeightMatching(links), {});
}

PROVIDED_TEST("maximumWeightMatching: Works for a single pair of people.") {
    /* This world:
     *
     *  A --- B
     *     1
     *
     * Best option is to pick A -- B.
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 }
    });

    /* Should pick A--B. */
    EXPECT_EQUAL(maximumWeightMatching(links), {{"A", "B"}});
}

PROVIDED_TEST("maximumWeightMatching: Won't pick a negative edge.") {
    /* This world:
     *
     *  A --- B
     *     -1
     *
     * Best option is to not match anyone!
     */
    auto links = fromWeightedLinks({
        { "A", "B", -1 }
    });

    /* Should pick A--B. */
    EXPECT_EQUAL(maximumWeightMatching(links), {});
}



PROVIDED_TEST("maximumWeightMatching: Works on a triangle.") {
    /* This world:
     *
     *         A
     *      1 / \ 2
     *       B---C
     *         3
     *
     * Best option is to pick B -- C.
     */
    auto links = fromWeightedLinks({
        { "A", "B", 1 },
        { "B", "C", 3 },
        { "A", "C", 2 }
    });

    /* Should pick B--C. */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works on a square.") {
    /* This world:
     *
     *         1
     *      A --- B
     *      |     |
     *    8 |     | 2
     *      |     |
     *      D --- C
     *         4
     *
     * Best option is to pick BC/AD.
     */
    auto links = fromWeightedLinks({
                                    { "A", "B", 1 },
                                    { "B", "C", 2 },
                                    { "C", "D", 4 },
                                    { "D", "A", 8 },
                                    });

    EXPECT_EQUAL(maximumWeightMatching(links), { {"A", "D"}, {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Works on a line of four people.") {
    /* This world:
     *
     *  A --- B --- C --- D
     *     1     3     1
     *
     * Best option is to pick B -- C, even though this is not a perfect
     * matching.
     */
    auto links = fromWeightedLinks({
                                    { "A", "B", 1 },
                                    { "B", "C", 3 },
                                    { "C", "D", 1 },
                                    });

    /* Should pick B--C. */
    EXPECT_EQUAL(maximumWeightMatching(links), { {"B", "C"} });
}

PROVIDED_TEST("maximumWeightMatching: Small stress test (should take at most a second or two).") {
    /* Because Map and Set internally store items in sorted order, the order
     * in which you iterate over people when making decisions is sensitive
     * to the order of those peoples' names. This test looks at a group like
     * this one, trying out all possible orderings of peoples' names:
     *
     *               *
     *               | 1
     *               *
     *            1 / \ 5
     *             *---*
     *          1 /  1  \ 1
     *           *       *
     *
     * (Best option is to pick the 5-cost edge and the opposite-side 1-cost
     * edge.)
     *
     * There are 6! = 720 possible permutations of the ordering of these
     * people. If your code is able to solve the problem correctly for all of
     * those orderings, there's a good chance that you're correctly tracking
     * who is matched at each step. On the other hand, if your code runs into
     * issues here, it may indicate that there's a bug in how you mark who's
     * paired and who isn't.
     */
    Vector<string> people = { "A", "B", "C", "D", "E", "F" };
    do {
        auto links = fromWeightedLinks({
                                        { people[0], people[1], 5 },
                                        { people[1], people[2], 1 },
                                        { people[2], people[0], 1 },
                                        { people[3], people[0], 1 },
                                        { people[4], people[1], 1 },
                                        { people[5], people[2], 1 },
                                        });

        Set<Pair> expected = {
            { people[0], people[1] },
            { people[2], people[5] }
        };

        EXPECT_EQUAL(maximumWeightMatching(links), expected);
    } while (next_permutation(people.begin(), people.end()));
}

PROVIDED_TEST("maximumWeightMatching: Large stress test (should take at most a second or two).") {
    /* Here, we're giving a chain of people, like this:
     *
     *    *---*---*---*---*---*---*---* ... *---*
     *      1   1   1   1   1   1   1         1
     *
     * The number of different matchings in a chain of n people is given by the
     * nth Fibonacci number. (Great exercise - can you explain why?) This means
     * that if we have a chain of 21 people, there are F(21) = 10,946 possible
     * matchings to check. If your program tests every single one of them exactly
     * once, then it should be pretty quick to determine what the best matching
     * here is. (It's any matching that uses exactly floor(21 / 2) = 10 edges.
     *
     * On the other hand, if your implementation repeatedly constructs the same
     * matchings over and over again, then the number of options you need to consider
     * will be too large for your computer to handle in any reasonable time.
     *
     * If you're passing the other tests and this test hangs, double-check your
     * code to make sure you aren't repeatedly constructing the same matchings
     * multiple times.
     */
    const int kNumPeople = 21;
    Vector<WeightedLink> links;
    for (int i = 0; i < kNumPeople - 1; i++) {
        links.add({ to_string(i), to_string(i + 1), 1 });
    }

    auto matching = maximumWeightMatching(fromWeightedLinks(links));
    EXPECT_EQUAL(matching.size(), kNumPeople / 2);

    /* Confirm it's a matching. */
    Set<string> used;
    for (Pair p: matching) {
        /* No people paired more than once. */
        EXPECT(!used.contains(p.first()));
        EXPECT(!used.contains(p.second()));
        used += p.first();
        used += p.second();

        /* Must be a possible links. */
        EXPECT_EQUAL(abs(stringToInteger(p.first()) - stringToInteger(p.second())), 1);
    }
}
