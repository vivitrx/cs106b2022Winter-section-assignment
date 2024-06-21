#include "RisingTides.h"
#include "GUI/SimpleTest.h"
#include "queue.h"
#include "grid.h"
using namespace std;

void flood(GridLocation loc, Grid<bool> &FLOOD); // 淹没函数的接口

Grid<bool> floodedRegionsIn(const Grid<double>& terrain,
                            const Vector<GridLocation>& sources,
                            double height)
{
    Queue<GridLocation> water_queue;
    double height_temp;
    Grid<bool> FLOOD(terrain.numRows(), terrain.numCols(), false);
    Grid<bool> &FLOOD_ref = FLOOD;

    for (GridLocation sources_element : sources) // 遍历sources中的所有元素
    {
        height_temp = terrain.get(sources_element); // 别忘了sources_element实际上是一个GridLocation类型的实例！
        if (terrain.inBounds(sources_element) && height_temp <= height)
        {
            flood(sources_element, FLOOD_ref); // 淹没这个位置
            water_queue.enqueue(sources_element); // 把这个格子enqueue到water_queue中方便后续去淹没别的格子
        }
    }

    //现在，水源尝试向着他所在位置的四个方向蔓延
    GridLocation temp2;
    GridLocation temp_orbit;
    while (!water_queue.isEmpty())
    {
        temp2 = water_queue.dequeue();
        // 然后去看看temp2上下左右的4个格子会不会被淹没，如果有被淹没的资格，就加入到water_queue中

        temp_orbit = temp2;
        temp_orbit.col++; // temp2头上的格子
        if (terrain.inBounds(temp_orbit) && terrain.get(temp_orbit) <= height && (FLOOD.get(temp_orbit) == false)) // 为了避免越界
        {
            flood(temp_orbit, FLOOD_ref);
            water_queue.enqueue(temp_orbit);
        }
        ////////////////////////
        temp_orbit = temp2;
        temp_orbit.col--; // temp2脚下的格子
        if (terrain.inBounds(temp_orbit) && terrain.get(temp_orbit) <= height && (FLOOD.get(temp_orbit) == false)) // 为了避免越界
        {
            flood(temp_orbit, FLOOD_ref);
            water_queue.enqueue(temp_orbit);
        }
        ////////////////////////
        temp_orbit = temp2;
        temp_orbit.row++; // temp2右边的格子
        if (terrain.inBounds(temp_orbit) && terrain.get(temp_orbit) <= height && (FLOOD.get(temp_orbit) == false)) // 为了避免越界
        {
            flood(temp_orbit, FLOOD_ref);
            water_queue.enqueue(temp_orbit);
        }
        ////////////////////////
        temp_orbit = temp2;
        temp_orbit.row--; // temp2左边的格子
        if (terrain.inBounds(temp_orbit) && terrain.get(temp_orbit) <= height && (FLOOD.get(temp_orbit) == false)) // 为了避免越界
        {
            flood(temp_orbit, FLOOD_ref);
            water_queue.enqueue(temp_orbit);
        }
    }
    return FLOOD;
}

void flood(GridLocation loc, Grid<bool> &FLOOD) // 淹没函数的实现
{
    FLOOD.set(loc, true); // ture的意思是确实淹了
}




/***** Test Cases Below This Point *****/
STUDENT_TEST("试试自定义测试！")
{
    Grid<double> world = {
        { 0 },
        { 0 },
        { 0 }
    };

    Vector<GridLocation> sources = {
        { 1, 0 }
    };

    /* There are no water sources, so nothing should be underwater. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { true },
        { true },
        { true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Nothing gets wet if there are no water sources.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        // empty
    };

    /* There are no water sources, so nothing should be underwater. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Everything gets wet if all locations are below the water level.") {
    Grid<double> world = {
        { 0, 0, 0 },
        { 0, 0, 0 },
        { 0, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Everything should flood; there are no barriers to stop the water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true,  true },
        {  true,  true,  true },
        {  true,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a vertical levee.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 0, 2, 0 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Only locations to the left of the barrier should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true, false, false },
        {  true, false, false },
        {  true, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't cross a diagonal levee.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* Water only flows in the four cardinal directions, so it can't
     * pass through the barrier. Only the top should be flooded.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can't flow diagonally.") {
    Grid<double> world = {
        { 0, 2, 0 },
        { 2, 0, 2 },
        { 0, 2, 0 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* Water should be trapped in the center, since it can't move
     * diagonally.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false, false, false },
        { false,  true, false },
        { false, false, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow in all cardinal directions.") {
    Grid<double> world = {
        { 2, 0, 2 },
        { 0, 0, 0 },
        { 2, 0, 2 }
    };

    Vector<GridLocation> sources = {
        { 1, 1 }
    };

    /* The water in this case should flow up, down, left, and right. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        { false,  true, false },
        {  true,  true,  true },
        { false,  true, false }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Water can flow from multiple sources.") {
    Grid<double> world = {
        { 0, 0, 2 },
        { 0, 2, 0 },
        { 2, 0, 0 }
    };

    Vector<GridLocation> sources = {
        { 0, 0 },
        { 2, 2 }
    };

    /* Everything except the levee should be under water. */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    Grid<bool> expected = {
        {  true,  true, false },
        {  true, false,  true },
        { false,  true,  true }
    };

    EXPECT_EQUAL(water, expected);
}

PROVIDED_TEST("Handles asymmetric worlds and non-square grids") {
    Grid<double> world = {
        { 3, 1, 4, 1 },
        { 5, 9, 2, 6 },
        { 5, 3, 5, 8 }
    };

    /* Initial test - water shouldn't leak out from the 2 if the height is 3.5. */
    Vector<GridLocation> sources = {
        { 1, 2 }
    };

    Grid<bool> expected = {
        { false, false, false, false },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 3.5), expected);

    /* Now, increase the water height to 4.5. */
    expected = {
        {  true,  true,  true,  true },
        { false, false,  true, false },
        { false, false, false, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 4.5), expected);

    /* Now, increase the water height to 5.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true, false },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 5.5), expected);

    /* Now, increase the water height to 6.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true, false,  true,  true },
        {  true,  true,  true, false },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 6.5), expected);

    /* Now, increase the water height to 9.5. */
    expected = {
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
        {  true,  true,  true,  true },
    };

    EXPECT_EQUAL(floodedRegionsIn(world, sources, 9.5), expected);
}

PROVIDED_TEST("Stress test: Handles a large, empty world quickly.") {
    Grid<double> world(100, 100); // Large world, everything defaults to 0 height.
    Vector<GridLocation> sources = {
        { 0, 0 }
    };

    /* This may take a long time to complete if the solution is inefficient. Look
     * for things like
     *
     * 1. passing around large objects by *value* rather than by *reference*,
     * 2. revisiting the same squares multiple times (e.g. flooding the same
     *    cell many times due to not checking if something is flooded),
     *
     * etc.
     */
    Grid<bool> water = floodedRegionsIn(world, sources, 1.0);
    EXPECT_EQUAL(water.numRows(), world.numRows());
    EXPECT_EQUAL(water.numCols(), world.numCols());

    /* Everything should be flooded. */
    for (int row = 0; row < world.numRows(); row++) {
        for (int col = 0; col < world.numCols(); col++) {
            EXPECT_EQUAL(water[row][col], true);
        }
    }
}
