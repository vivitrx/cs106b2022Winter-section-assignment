#include "ShiftScheduling.h"
using namespace std;

int call_times = 0;

Set<Shift> hVSF_helper
    (
        Set<Shift> work_table, int maxHours,
        Set<Shift>& present_schedule, Set<Shift>& last_schedule,
        double work_time
        );

Set<Shift> highestValueScheduleFor(const Set<Shift>& shifts, int maxHours)
{
    if (maxHours == 0)
    {
        return {};
    }
    if (maxHours < 0)
    {
        error("请输入正数");
    }
    Set<Shift> last_schedule;
    Set<Shift> present_schedule;
    double work_time = 0.0;
    Set<Shift> work_table = shifts;
    auto result = hVSF_helper(work_table, maxHours, present_schedule, last_schedule, work_time);
    cout << call_times << endl;
    return result;
}


Set<Shift> hVSF_helper
    (
        Set<Shift> work_table, int maxHours,
        Set<Shift>& present_schedule, Set<Shift>& last_schedule,
        double work_time
        )
{
    call_times ++;

    if (work_table.isEmpty()) // base case
    {
        double earn_money = 0;
        for (Shift i : present_schedule)
        {
            earn_money += valueOf(i);
        }

        double last_earn_money = 0;
        for (Shift j : last_schedule)
        {
            last_earn_money += valueOf(j);
        }

        if (earn_money > last_earn_money) // 当前轮班present_schedule能赚到的钱earn_money > 上一次轮班last_schedule能赚到的钱last_earn_money
        {
            last_schedule = present_schedule;
        }
        return last_schedule;

    }


    // recursive case
    // 开始进行排班冲突和非法加班检定
    Shift first = work_table.first();


    // 排班冲突检定
    bool flag = true;
    double temp = 0;
    for (Shift i : present_schedule)
    {
        temp += lengthOf(i);
        if (overlapsWith(first, i) == true)
        {
            flag = false;
        }
    }
    // 非法加班检定
    if (temp + lengthOf(first) > maxHours)
    {
        flag = false;
    }

    /////////////////////////////////
    if (flag == true)
    {
        present_schedule.add(first); // 如果成功就正常add()
        // work_time += lengthOf(first);

        Set<Shift> new_work_table = work_table;
        new_work_table.remove(first);

        auto a = hVSF_helper(  // 设work_table为abcde ，该行代码会寻找以a开头的轮班组合（a轮）的最佳结果
            new_work_table, maxHours,
            present_schedule, last_schedule,
            work_time); // 递归点，注意，一般来说，下一个call stack执行完全部语句后，会返回上一个call stack的递归点

        present_schedule.remove(first);

        auto b = hVSF_helper( // 设work_table为abcde ，该行代码会寻找以b开头的轮班组合（b轮）的最佳结果
            new_work_table, maxHours,
            present_schedule, last_schedule,
            work_time);

        double a_money = 0;
        for (Shift i : a){
            a_money += valueOf(i);
        }
        double b_money = 0;
        for (Shift j : b){
            b_money += valueOf(j);
        }

        if (a_money > b_money) // 当前轮班present_schedule能赚到的钱earn_money > 上一次轮班last_schedule能赚到的钱last_earn_money
        {
            return a;
        }else
        {
            return b;
        }

        // work_time -= lengthOf(first); // 确保 work_time 在每次递归调用后恢复到调用前的状态   但是我是按值传递
    }else
    {
        Set<Shift> new_work_table = work_table;
        new_work_table.remove(first);
        return hVSF_helper( /*第一轮的结果 = */
                           new_work_table, maxHours,
                           present_schedule, last_schedule,
                           work_time); // 递归点，注意，一般来说，下一个call stack执行完全部语句后，会返回上一个call stack的递归点
    }
}



/* * * * * * Test Cases * * * * * */
#include "GUI/SimpleTest.h"

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */
STUDENT_TEST("最重要的测试，需要回溯才能得出正确答案，因为你能赚更多钱你才会把(赚钱最少的)b班次换成e班次") {
    Set<Shift> shifts = {
                         { Day::MONDAY, 8, 12, 270 },
                         { Day::MONDAY, 12, 16, 25 }, // b班次 只能赚25块
                         { Day::MONDAY, 16, 20, 28 },
                         // // //
                         { Day::MONDAY, 8, 14, 39 },
                         { Day::MONDAY, 14, 20, 310 }, // e班次
                         };

    Set<Shift> test_target = {
                        { Day::MONDAY, 8, 12, 270 },
                        { Day::MONDAY, 14, 20, 310 },
                        };

    EXPECT_EQUAL(highestValueScheduleFor(shifts, 16), test_target);
}


// STUDENT_TEST("考虑20小时工作制下的突出奖励(周日工作超级加薪)情况") {
//     Set<Shift> shifts = {
//         { Day::MONDAY, 9, 17, 1 },  // Monday, 9 - 17, value is 1
//         { Day::TUESDAY, 1, 12, 11 },  // Monday, 1 - 12, value is 11
//         { Day::WEDNESDAY, 1, 13, 12 },  // Monday, 1 - 13, value is 12
//         { Day::FRIDAY, 1, 15, 14 },  // Monday, 1 - 15, value is 14
//         { Day::SUNDAY, 1, 13, 2800 },  // Monday, 1 - 13, value is 2800 周日还工作啊哥
//     };
    
//     Set<Shift> test_target = {
//         { Day::MONDAY, 9, 17, 1 },  // Monday, 9 - 17, value is 1
//         { Day::SUNDAY, 1, 13, 2800 },
//         };
    
//     EXPECT_EQUAL(highestValueScheduleFor(shifts, 20), test_target);
// }

// STUDENT_TEST("考虑20小时工作制下的穷逼雇主(不怎么喜欢给员工加薪)情况") {
//     Set<Shift> shifts = {
//         { Day::MONDAY, 1, 2, 1 },  // Monday, 1 - 2, value is 1
//         { Day::TUESDAY, 2, 3, 2 },  // Monday, 2 - 3, value is 2
//         { Day::WEDNESDAY, 3, 4, 3 },  // Monday, 3 - 4, value is 3
//         { Day::FRIDAY, 4, 5, 4 },  // Monday, 4 - 5, value is 4
//         { Day::SUNDAY, 1, 13, 1},  // Monday, 1 - 13, value is 1 就算你周日拉满，你也只能挣一块钱
//     };
    
//     Set<Shift> test_target = {
//         { Day::MONDAY, 1, 2, 1 },
//         { Day::TUESDAY, 2, 3, 2 },
//         { Day::WEDNESDAY, 3, 4, 3 },
//         { Day::FRIDAY, 4, 5, 4 },
//         { Day::SUNDAY, 1, 13, 1},
//                         };
    
//     EXPECT_EQUAL(highestValueScheduleFor(shifts, 20), test_target);
// }





// /* * * * * * Test cases from the starter files below this point. * * * * * */
// #include "vector.h"
// #include "error.h"

// /* This nice utility function lets you call highestValueScheduleFor, passing in
//  * a Vector of shifts rather than a Set. This makes it a bit easier to test things.
//  * You shouldn't need this function outside of these test cases.
//  */
// Set<Shift> asSet(const Vector<Shift>& shifts) {
//     Set<Shift> result;
//     for (Shift s: shifts) {
//         result += s;
//     }
//     return result;
// }

// PROVIDED_TEST("Pick only shift if you have time for it.") {
//     Set<Shift> shifts = {
//         { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
//     };

//     EXPECT_EQUAL(highestValueScheduleFor(shifts, 24).size(), 1);
//     EXPECT_EQUAL(highestValueScheduleFor(shifts, 24), shifts);
// }

// PROVIDED_TEST("Don't pick only shift if ou don't have time for it.") {
//     Set<Shift> shifts = {
//         { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
//     };

//     EXPECT_EQUAL(highestValueScheduleFor(shifts, 3).size(), 0);
// }

// PROVIDED_TEST("Don't pick overlapping shifts.") {
//     Vector<Shift> shifts = {
//         { Day::MONDAY, 9, 17, 1000 },  // Monday,  9AM - 5PM, value is 1000
//         { Day::MONDAY, 8, 18, 2000 },  // Monday, 10AM - 6PM, value is 2000
//     };

//     EXPECT_EQUAL(highestValueScheduleFor(asSet(shifts), 100), { shifts[1] });
// }

// PROVIDED_TEST("Doesn't always use highest-value shift.") {
//     Vector<Shift> shifts = {
//         { Day::MONDAY,    10, 20, 1000 }, // 10-hour shift, value is 1000
//         { Day::TUESDAY,   10, 15,  500 }, //  5-hour shift, value is 500
//         { Day::WEDNESDAY, 10, 16,  501 }, //  6-hour shift, value is 501
//     };

//     /* The correct strategy is to forgo the highest-value shift in favor of the two
//      * shorter shifts.
//      */
//     auto schedule = highestValueScheduleFor(asSet(shifts), 11);

//     EXPECT_EQUAL(schedule, { shifts[1], shifts[2] });
// }

// PROVIDED_TEST("Handles no shifts.") {
//     EXPECT_EQUAL(highestValueScheduleFor({}, 137).size(), 0);
// }

// PROVIDED_TEST("Doesn't always use the shift with the highest value per unit time.") {
//     Vector<Shift> shifts = {
//         { Day::MONDAY,    10, 17, 21 }, //  7-hour shift, value is 21 ($3 / hour)
//         { Day::TUESDAY,   10, 16, 12 }, //  6-hour shift, value is 12 ($2 / hour)
//         { Day::WEDNESDAY, 10, 16, 12 }, //  6-hour shift, value is 12 ($2 / hour)
//     };

//     /* If you have 12 hours, the correct strategy is to pick the two six-hour shifts
//      * for a total of $24 value. Picking the shift with the highest value per unit
//      * time (the seven-hour shift) produces only $21 value.
//      */
//     auto schedule = highestValueScheduleFor(asSet(shifts), 12);

//     EXPECT_EQUAL(schedule, { shifts[1], shifts[2] });
// }




// PROVIDED_TEST("Reports an error with negative hours.") {
//     /* From the assignment description. */
//     Vector<Shift> shifts = {
//         { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27
//         { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28
//         { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25
//         { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
//         { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
//         { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
//         { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
//         { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
//         { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
//         { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
//         { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
//         { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
//         { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
//         { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
//         { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25
//     };

//     /* Should be an error. */
//     EXPECT_ERROR(highestValueScheduleFor(asSet(shifts), -1));

//     /* Still an error even if there are no shifts. */
//     EXPECT_ERROR(highestValueScheduleFor({}, -1));
// }

// PROVIDED_TEST("Handles zero free hours.") {
//     /* From the assignment description. */
//     Vector<Shift> shifts = {
//         { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27
//         { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28
//         { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25
//         { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
//         { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
//         { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
//         { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
//         { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
//         { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
//         { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
//         { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
//         { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
//         { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
//         { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
//         { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25
//     };

//     /* Shouldn't be an error if time is zero - that means we just don't pick anything. */
//     EXPECT_EQUAL(highestValueScheduleFor(asSet(shifts), 0).size(), 0);
// }

// PROVIDED_TEST("Passes the example from the assignment description.") {
//     Vector<Shift> shifts = {
//         { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27 *
//         { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28 *
//         { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25 *
//         { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
//         { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
//         { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
//         { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
//         { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
//         { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
//         { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
//         { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
//         { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
//         { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
//         { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
//         { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25 *
//     };

//     /* Get back the solution. */
//     Set<Shift> computedSolution = highestValueScheduleFor(asSet(shifts), 20);

//     /* Form the correct answer. It's the starred entries. */
//     Set<Shift> actualSolution = {
//         shifts[0], shifts[1], shifts[2], shifts[14]
//     };

//     EXPECT_EQUAL(computedSolution, actualSolution);
// }

// PROVIDED_TEST("Stress test: Don't generate shift combinations with overlapping shifts.") {
//     /* All of these shifts overlap one another. If you try producing all combinations
//      * of these shifts and only check at the end whether they're valid, you'll be
//      * checking 2^100 ~= 10^30 combinations of shifts, which will take so long the
//      * sun will have burnt out before you're finished.
//      *
//      * Instead, as you're going through your decision tree and building up your shifts,
//      * make sure not to include any shifts that clearly conflict with something you
//      * picked earlier.
//      */
//     Set<Shift> trickySet;
//     for (int i = 0; i < 100; i++) {
//         trickySet += Shift{ Day::MONDAY, 1, 2, i };
//     }
//     EXPECT_EQUAL(trickySet.size(), 100);

//     auto result = highestValueScheduleFor(trickySet, 1);
//     EXPECT_EQUAL(result.size(), 1);
// }

// PROVIDED_TEST("Stress test: Don't generate shift combinations that exceed time limits.") {
//     /* Here's a collection of one shift per hour of the week. Your worker has exactly
//      * one hour free. If you try all possible combinations of these shifts, ignoring time
//      * constraints, you will have to check over 2^100 = 10^30 combinations, which will
//      * take longer than the length of the known universe to process.
//      *
//      * Instead, as you're exploring the decision tree to generate shift combinations,
//      * make sure not to add shifts that would exceed the time limit.
//      */
//     Set<Shift> trickySet;
//     for (Day day: { Day::SUNDAY,
//                     Day::MONDAY,
//                     Day::TUESDAY,
//                     Day::WEDNESDAY,
//                     Day::THURSDAY,
//                     Day::FRIDAY,
//                     Day::SATURDAY}) {
//         for (int start = 0; start < 24; start++) {
//             trickySet += Shift{ day, start, start + 1, 10 };
//         }
//     }
//     EXPECT_EQUAL(trickySet.size(), 7 * 24);

//     auto result = highestValueScheduleFor(trickySet, 1);
//     EXPECT_EQUAL(result.size(), 1);
// }

// PROVIDED_TEST("Stress test: Can handle a decent number of shifts (should take at most 10-15 seconds)") {
//     /* Available shifts. */
//     Vector<Shift> shifts = {
//         { Day::SUNDAY,  8, 14, 12 },
//         { Day::SUNDAY, 12, 18, 36 },

//         { Day::MONDAY,  8, 12, 44 },
//         { Day::MONDAY, 12, 16, 32 },
//         { Day::MONDAY, 16, 20,  0 },
//         { Day::MONDAY,  8, 16, 16 },
//         { Day::MONDAY, 12, 20, 22 },

//         { Day::TUESDAY,  8, 12, 48 },
//         { Day::TUESDAY, 12, 16, 20 },
//         { Day::TUESDAY, 16, 20, 24 },
//         { Day::TUESDAY,  8, 16, 24 },
//         { Day::TUESDAY, 12, 20, 80 },

//         { Day::WEDNESDAY,  8, 12, 20 },
//         { Day::WEDNESDAY, 12, 16,  8 },
//         { Day::WEDNESDAY, 16, 20,  8 },
//         { Day::WEDNESDAY,  8, 16, 40 },
//         { Day::WEDNESDAY, 12, 20, 16 },

//         { Day::THURSDAY,  8, 12, 40 },
//         { Day::THURSDAY, 12, 16,  0 },
//         { Day::THURSDAY, 16, 20, 24 },
//         { Day::THURSDAY,  8, 16, 56 },
//         { Day::THURSDAY, 12, 20, 32 },

//         { Day::FRIDAY,  8, 12,  4 },
//         { Day::FRIDAY, 12, 16,  8 },
//         { Day::FRIDAY, 16, 20, 40 },
//         { Day::FRIDAY,  8, 16, 72 },
//         { Day::FRIDAY, 12, 20, 40 },

//         { Day::SATURDAY,  8, 14, 18 },
//         { Day::SATURDAY, 12, 18, 66 },
//     };

//     auto answer = highestValueScheduleFor(asSet(shifts), 30);
//     EXPECT_EQUAL(answer, { shifts[2], shifts[7], shifts[11], shifts[17], shifts[24], shifts[28] });
// }
