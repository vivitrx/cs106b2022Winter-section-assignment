#include "Apportionment.h"
#include "HeapPQueue.h"
#include "queue.h"
using namespace std;

double compute(double P,double S)
{
    return P/sqrt(S*(S+1));
}

Map<string, int> apportion(const Map<string, int>& populations, int numSeats) {
    if (populations.size() > numSeats){
        error("如果州数多于席位数，则应调用 error() 报告错误。");}

    Map<string, int> state_seats = {}; // 州---席位，这是你最终要返回的结果
    for(string state : populations){
        // 最初，给每个州一个众议院席位
        state_seats.put(state, 1);
        numSeats --;
    }

    // 然后，将所有州放入 HeapPQueue 中
    HeapPQueue state_weight; // 州---权重
    DataPoint i;
    for(string state : populations){
        i.name = state;
        i.weight = -1 * double(populations[state]) / sqrt(2) ; // 乘以负一是神来之笔，把小顶堆变成大顶堆
        state_weight.enqueue(i);
    }

    /////////////////////////////////////////

    DataPoint outer;
    while (true)
    {
        if (numSeats == 0) // 最好还是把检测放最前面，因为先执行下方代码中的numSeats --可能会导致负数死循环
        {
            return state_seats;
        }
        outer = state_weight.dequeue();
        state_seats[outer.name]++;
        numSeats --;
        outer.weight = -1 * compute(populations[outer.name], state_seats[outer.name]);
        state_weight.enqueue(outer);
    }
}

// 你得找到权重最高的条目，如何欺骗？
// // 哦牛逼，我知道了，不停的dequeue()，最后剩下的那个就是权重最大的条目，然后最后dequeue()一次就能获取权重最高的条目了
// Queue<DataPoint> relic;
// while (1){
//     if (state_weight.size() == 1)
//         break;
//     relic.enqueue( state_weight.dequeue() );
// }
// outer = state_weight.dequeue(); // 此时state_weight应该为空

// while (1){
//     if (relic.size() == 0)
//         break;
//     state_weight.enqueue( relic.dequeue() ); // 把relic中的所有元素都放进state_weight中
// }
// // /////////////////////////////////


/* * * * * Test Cases Below This Point * * * * */
#include "GUI/SimpleTest.h"
#include "Utilities/CSV.h"


PROVIDED_TEST("Each state gets at least one seat.") {
    /* Fall 2020 */
    Map<string, int> populations = {
        { "CS106A", 551 },
        { "CS106B", 428 },
        { "CS103",  206 },
        { "CS107",  267 },
        { "CS109",  214 },
        { "CS110",  196 },
        { "CS161",  187 }
    };

    /* Seven seats and seven classes means everyone gets one. */
    Map<string, int> seats = {
        { "CS106A", 1 },
        { "CS106B", 1 },
        { "CS103",  1 },
        { "CS107",  1 },
        { "CS109",  1 },
        { "CS110",  1 },
        { "CS161",  1 }
    };

    EXPECT_EQUAL(apportion(populations, 7), seats);
}

PROVIDED_TEST("Reports an error if there are more states than seats.") {
    Map<string, int> populations = {
        { "House",         435 },
        { "Senate",        100 },
        { "Supreme Court",   9 },
        { "President",       1 },
    };

    EXPECT_ERROR(apportion(populations, 3));
    EXPECT_ERROR(apportion(populations, -2));
    EXPECT_NO_ERROR(apportion(populations, 4));
}

PROVIDED_TEST("Works on the example from the handout.") {
    Map<string, int> populations = {
        { "Mind",    25419 },
        { "Denial",  13509 },
        { "Affairs", 7984  },
        { "Being",   14938 },
        { "Matter",  14617 }
    };

    Map<string, int> seats = {
        { "Mind",    5 },
        { "Denial",  2 },
        { "Affairs", 1 },
        { "Being",   3 },
        { "Matter",  3 }
    };

    EXPECT_EQUAL(apportion(populations, 14), seats);
}

namespace {
    Map<string, int> populationsFrom(const string& filename) {
        CSV csv = CSV::parseFile(filename);

        Map<string, int> populations;
        for (size_t i = 0; i < csv.numRows(); i++) {
            populations[csv[i]["State"]] = stringToInteger(csv[i]["Population"]);
        }

        return populations;
    }
}

PROVIDED_TEST("Works on the 2020 apportionment.") {
    auto populations = populationsFrom("res/apportionment/2020.csv");

    /* Apportioned results. */
    Map<string, int> seats = {
        { "Alabama", 7 },
        { "Alaska", 1 },
        { "Arizona", 9 },
        { "Arkansas", 4 },
        { "California", 52 },
        { "Colorado", 8 },
        { "Connecticut", 5 },
        { "Delaware", 1 },
        { "Florida", 28 },
        { "Georgia", 14 },
        { "Hawaii", 2 },
        { "Idaho", 2 },
        { "Illinois", 17 },
        { "Indiana", 9 },
        { "Iowa", 4 },
        { "Kansas", 4 },
        { "Kentucky", 6 },
        { "Louisiana", 6 },
        { "Maine", 2 },
        { "Maryland", 8 },
        { "Massachusetts", 9 },
        { "Michigan", 13 },
        { "Minnesota", 8 },
        { "Mississippi", 4 },
        { "Missouri", 8 },
        { "Montana", 2 },
        { "Nebraska", 3 },
        { "Nevada", 4 },
        { "New Hampshire", 2 },
        { "New Jersey", 12 },
        { "New Mexico", 3 },
        { "New York", 26 },
        { "North Carolina", 14 },
        { "North Dakota", 1 },
        { "Ohio", 15 },
        { "Oklahoma", 5 },
        { "Oregon", 6 },
        { "Pennsylvania", 17 },
        { "Rhode Island", 2 },
        { "South Carolina", 7 },
        { "South Dakota", 1 },
        { "Tennessee", 9 },
        { "Texas", 38 },
        { "Utah", 4 },
        { "Vermont", 1 },
        { "Virginia", 11 },
        { "Washington", 10 },
        { "West Virginia", 2 },
        { "Wisconsin", 8 },
        { "Wyoming", 1 },
    };

    EXPECT_EQUAL(apportion(populations, 435), seats);
}

PROVIDED_TEST("Stress test: works on a large number of states (should take at most a few seconds).") {
    const int kLargeNumber = 100000;

    /* kLargeNumber of states with population 1. */
    Map<string, int> populations;
    for (int i = 0; i < kLargeNumber; i++) {
        populations[to_string(i)] = 1;
    }

    /* One state with population kLargeNumber. */
    populations[to_string(kLargeNumber)] = kLargeNumber;

    /* Apportion kLargeNumber + (kLargeNumber / 4 - 1) seats. This has the effect
     * of giving everyone one seat, then giving kLargeNumber the remaining
     * kLargeNumber / 4 - 1 seats.
     */
    const int kExtraSeats = kLargeNumber / 4 - 1;

    auto result = apportion(populations, kLargeNumber + kExtraSeats);

    /* Confirm all the small states get one seat. */
    for (int i = 0; i < kLargeNumber; i++) {
        EXPECT_EQUAL(result[to_string(i)], 1);
    }

    /* Confirm the big state gets the rest. */
    EXPECT_EQUAL(result[to_string(kLargeNumber)], kExtraSeats);
}
