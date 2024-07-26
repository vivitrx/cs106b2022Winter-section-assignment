#include "GUI/SimpleTest.h"
#include "Combine.h"
using namespace std;
// https://pastebin.com/MfPdfzrB 第一版代码，简洁，但是太慢了

Vector<DataPoint> helper(Vector<Vector<DataPoint>> sequences);

Vector<DataPoint> combine(const Vector<Vector<DataPoint>>& sequences) {
    if (sequences.size() == 0) return {};
    Vector<Vector<DataPoint>> sequencesssssss = sequences;
    return helper(sequencesssssss);
}

Vector<DataPoint> helper(Vector<Vector<DataPoint>> sequences) {
    if (sequences.size() == 1) // base case
    {
        return sequences[0];
    }else{ // recursive case: 只有2个向量的情况，左小向量，右大向量
        int half = sequences.size() / 2;
        Vector<DataPoint> leftSmall = helper( sequences.subList(0, half) );
        Vector<DataPoint> rightBig = helper( sequences.subList(half) );

        if (leftSmall.size() > rightBig.size())
        {
            Vector<DataPoint> temp = leftSmall;
            leftSmall = rightBig;
            rightBig = temp;
        }

        Vector<DataPoint> result; // 偷鸡，针对特殊情况做点优化
        if (leftSmall.size() != 0 && rightBig.size() != 0)
        {
            if (leftSmall[leftSmall.size() - 1].weight < rightBig[0].weight)// 如果leftSamll的最大值小于rightBig的最小值
            {
                result += leftSmall;
                result += rightBig;
                return result;
            }

            if (rightBig[rightBig.size() - 1].weight < leftSmall[0].weight)// 如果rightBig的最大值小于leftSamll的最小值
            {
                result += rightBig;
                result += leftSmall;
                return result;
            }
        }

        int left = 0;
        int right = 0;
        while ( left <= leftSmall.size() - 1 && right <= rightBig.size() - 1 ) // 当其中一个向量循环完毕后就停止循环
        {
            if (leftSmall[left].weight < rightBig[right].weight)
            {
                result.add(leftSmall[left]);
                left++;
            }else{
                result.add(rightBig[right]);
                right++;
            }
        }

        if (left == leftSmall.size())
        {
            result += rightBig.subList(right);
        }else
        {
            result += leftSmall.subList(left);
        }
        return result;
    }
}



/* * * * * * Test Cases Below This Point * * * * * */

/* TODO: Add your own custom tests here! */


STUDENT_TEST("Merges two single-item sequences.") {
    DataPoint suiseiseki = { "suiseiseki",       3 };
    DataPoint soseiseki  = { "soseiseki",        4 };

    DataPoint Geal        = { "Geal",            5 };
    DataPoint painter  = { "painter",            6 };
    DataPoint Friede  = { "Friede",            7 };

    DataPoint amy        = { "Amy Liu",          8 };
    DataPoint katherine  = { "Katherine Erdman", 9 };


    /* Try merging in both orders to make sure the result is correct. */
    auto merged = combine({{ amy }, { katherine }, { suiseiseki }, { soseiseki }, { Geal }, { painter }, { Friede }});
    EXPECT_EQUAL(merged.size(), 7);
    EXPECT_EQUAL(merged[0], suiseiseki);
    EXPECT_EQUAL(merged[1], soseiseki);
    EXPECT_EQUAL(merged[2], Geal);
    EXPECT_EQUAL(merged[3], painter);
}












/* * * * * Provided Tests Below This Point * * * * */


PROVIDED_TEST("Merges two single-item sequences.") {
    DataPoint amy        = { "Amy Liu",          103 };
    DataPoint katherine  = { "Katherine Erdman", 106 };

    /* Try merging in both orders to make sure the result is correct. */
    auto merged = combine({{ amy }, { katherine }});
    EXPECT_EQUAL(merged.size(), 2);
    EXPECT_EQUAL(merged[0], amy);
    EXPECT_EQUAL(merged[1], katherine);

    merged = combine({{ katherine }, { amy }});
    EXPECT_EQUAL(merged.size(), 2);
    EXPECT_EQUAL(merged[0], amy);
    EXPECT_EQUAL(merged[1], katherine);
}

PROVIDED_TEST("Merges four single-item sequences.") {
    DataPoint amy        = { "Amy Liu",          103 };
    DataPoint katherine  = { "Katherine Erdman", 106 };
    DataPoint isabel     = { "Isabel Bush",      107 };
    DataPoint anna       = { "Anna Saplistki",   161 };

    /* Try merging in several different orders. */
    auto merged = combine({{ amy }, { katherine }, { isabel }, { anna }});
    EXPECT_EQUAL(merged.size(), 4);
    EXPECT_EQUAL(merged[0], amy);
    EXPECT_EQUAL(merged[1], katherine);
    EXPECT_EQUAL(merged[2], isabel);
    EXPECT_EQUAL(merged[3], anna);

    merged = combine({{ katherine }, { isabel }, { anna }, { amy }});
    EXPECT_EQUAL(merged.size(), 4);
    EXPECT_EQUAL(merged[0], amy);
    EXPECT_EQUAL(merged[1], katherine);
    EXPECT_EQUAL(merged[2], isabel);
    EXPECT_EQUAL(merged[3], anna);
}

PROVIDED_TEST("Merges three single-item sequences.") {
    DataPoint amy        = { "Amy Liu",          103 };
    DataPoint katherine  = { "Katherine Erdman", 106 };
    DataPoint isabel     = { "Isabel Bush",      107 };

    /* Try merging in several different orders. */
    auto merged = combine({{ amy }, { katherine }, { isabel }});
    EXPECT_EQUAL(merged.size(), 3);
    EXPECT_EQUAL(merged[0], amy);
    EXPECT_EQUAL(merged[1], katherine);
    EXPECT_EQUAL(merged[2], isabel);

    merged = combine({{ katherine }, { isabel }, { amy }});
    EXPECT_EQUAL(merged.size(), 3);
    EXPECT_EQUAL(merged[0], amy);
    EXPECT_EQUAL(merged[1], katherine);
    EXPECT_EQUAL(merged[2], isabel);
}

PROVIDED_TEST("Merges two lists of different sizes") {
    Vector<DataPoint> one = { { "B" , 3 }};
    Vector<DataPoint> two = {
        { "A" , 2 },
        { "C" , 4 },
        { "D" , 5 },
    };

    auto merged = combine({ one, two });
    EXPECT_EQUAL(merged.size(), 4);
    EXPECT_EQUAL(merged[0], two[0]);
    EXPECT_EQUAL(merged[1], one[0]);
    EXPECT_EQUAL(merged[2], two[1]);
    EXPECT_EQUAL(merged[3], two[2]);
}

PROVIDED_TEST("Merges three lists of different sizes") {
    Vector<DataPoint> one = {
        { "G" , 7 }
    };
    Vector<DataPoint> two = {
        { "A" , 1 },
        { "D" , 4 },
        { "F" , 6 },
    };
    Vector<DataPoint> three = {
        { "B" , 2 },
        { "C" , 3 },
        { "E" , 5 },
        { "H" , 8 },
        { "I" , 9 },
    };

    auto merged = combine({ one, two, three });
    EXPECT_EQUAL(merged.size(), 9);

    Vector<DataPoint> expected;
    for (int i = 1; i <= 9; i++) {
        expected += DataPoint{ string(1, 'A' - 1 + i), double(i) };
    }

    EXPECT_EQUAL(merged, expected);
}

PROVIDED_TEST("Preserves duplicates in input sequences.") {
    Vector<DataPoint> one = {
        { "A" , 1 },
        { "B" , 3 },
    };
    Vector<DataPoint> two = {
        { "A", 1 },
        { "B", 2 },
        { "C", 3 },
        { "D", 4 },
    };
    Vector<Vector<DataPoint>> vec = { one, two };
    auto merged = combine(vec);
    EXPECT_EQUAL(merged.size(), 6);
    EXPECT_EQUAL(merged[0].weight, two[0].weight);
    EXPECT_EQUAL(merged[1].weight, one[0].weight);
    EXPECT_EQUAL(merged[2].weight, two[1].weight);
    EXPECT_EQUAL(merged[3].weight, two[2].weight);
    EXPECT_EQUAL(merged[4].weight, one[1].weight);
    EXPECT_EQUAL(merged[5].weight, two[3].weight);
}

PROVIDED_TEST("Works with negative elements.") {
    Vector<DataPoint> one = {
        { "A" , -5 },
        { "B" , -1 },
        { "C" ,  2 },
    };
    Vector<DataPoint> two = {
        { "A", -2 },
        { "C",  3 },
        { "D",  4 },
    };
    Vector<Vector<DataPoint>> vec = { one, two };
    auto merged = combine(vec);
    EXPECT_EQUAL(merged.size(), 6);
    EXPECT_EQUAL(merged[0], one[0]);
    EXPECT_EQUAL(merged[1], two[0]);
    EXPECT_EQUAL(merged[2], one[1]);
    EXPECT_EQUAL(merged[3], one[2]);
    EXPECT_EQUAL(merged[4], two[1]);
    EXPECT_EQUAL(merged[5], two[2]);
}

PROVIDED_TEST("Works in the example from the handout.") {
    Vector<Vector<double>> sequences = {
        { 3, 8, 10, 11, 13, 16 },
        { 0, 1, 12 },
        { 4, 9, 17, 19 },
        { 7 },
        { 5, 6, 14, 18 },
        { 2, 15 }
    };

    /* The example in the handout uses integers, but we need DataPoints. Tag each integer
     * with an empty string.
     */
    Vector<Vector<DataPoint>> dataPoints;
    for (auto sequence: sequences) {
        Vector<DataPoint> result;
        for (double elem: sequence) {
            result += { "", elem };
        }
        dataPoints += result;
    }

    /* Merge them! */
    auto merged = combine(dataPoints);

    EXPECT_EQUAL(merged.size(), 20);
    for (int i = 0; i < 20; i++) {
        EXPECT_EQUAL(merged[i].weight, i);
    }
}

PROVIDED_TEST("1,000 sequences with 0 total elements (should take at most a few seconds)") {
    Vector<Vector<DataPoint>> vec;
    for (int i = 0; i < 1000; i++) vec.add({});
    auto merged = combine(vec);
    EXPECT_EQUAL(merged.size(), 0);
}

PROVIDED_TEST("1,000 sequences with 1 total element") {
    DataPoint point = { "I'm the only point!", 1 };
    Vector<Vector<DataPoint>> vec = {{ point }};
    for (int i = 0; i < 1000 - 1; i++) vec.add({});
    auto merged = combine(vec);
    EXPECT_EQUAL(merged.size(), 1);
    EXPECT_EQUAL(merged[0], point);
}

PROVIDED_TEST("1,000 sequences with 1,000 total elements") {
    Vector<Vector<DataPoint>> vec;
    for (int i = 0; i < 1000; i++) vec.add({{ "", double(i) }});
    auto merged = combine(vec);
    EXPECT_EQUAL(merged.size(), 1000);
    EXPECT_EQUAL(merged[0].weight, 0);
    EXPECT_EQUAL(merged[999].weight, 999);
}

PROVIDED_TEST("100 sequences of random lengths") {
    Vector<Vector<DataPoint>> vec;
    int totalElems = 0;
    Vector<int> elems;
    for (int i = 0; i < 100; i++) {
        int length = randomInteger(0, 20);
        Vector<DataPoint> seq;
        for (int j = 0; j < length; j++) {
            seq.add({ "", double(j) });
            totalElems++;
            elems.add(j);
        }
        vec.add(seq);
    }
    auto merged = combine(vec);
    sort(elems.begin(), elems.end());
    EXPECT_EQUAL(merged.size(), totalElems);
    EXPECT_EQUAL(merged[0].weight, elems[0]);
    EXPECT_EQUAL(merged[totalElems - 1].weight, elems[totalElems - 1]);
}

PROVIDED_TEST("No elements and no sequences.") {
    Vector<Vector<DataPoint>> numbers;
    EXPECT_EQUAL(combine(numbers).size(), 0);
}

PROVIDED_TEST("Stress test: 25 sequences of 20,000 elements each (should take at most a few seconds).") {
    const int kNumSequences = 25;
    const int kNumElements  = 20000;
    Vector<Vector<DataPoint>> numbers;

    /* Build the sequences. */
    for (int i = 0; i < kNumSequences; i++) {
        Vector<DataPoint> values;
        for (int j = 0; j < kNumElements; j++) {
            values.add({ "", double(j) });
        }
        numbers.add(values);
    }

    /* Combine them. */
    auto result = combine(numbers);
    EXPECT_EQUAL(result.size(), kNumSequences * kNumElements);

    for (int i = 0; i < result.size(); i++) {
        EXPECT_EQUAL(result[i].name, "");
        EXPECT_EQUAL(result[i].weight, i / kNumSequences);
    }
}
