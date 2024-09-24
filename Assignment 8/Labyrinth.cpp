#include <iostream>
#include "Labyrinth.h"
using namespace std;

bool isPathToFreedom(MazeCell* start, const string& moves) {
    // 前置
    MazeCell* current_room = start;
    Treasure treasure;
    int input_size = moves.size();// 搞出数组长度
    // // // // // // // // // // // // // // // //

    // moves说什么我做什么,跟着moves走;
    int i = 0;
    while(true){
        if (current_room->whatsHere != Item::NOTHING){
            findTueasure(treasure, current_room->whatsHere);
        }
        if(i == input_size){
            break; // 说明已经走完全程
        }
        if (goTo_nextRoom(current_room, moves[i]) != nullptr){
            current_room = goTo_nextRoom(current_room, moves[i]); // 去下一个房间
        }
        i++;
    }

    return (treasure.spellbook &&
            treasure.potion &&
            treasure.wand);
}

void findTueasure(Treasure& treasure, Item item){
    switch (item) {
    case Item::SPELLBOOK:
        treasure.spellbook = 1;
        break;
    case Item::POTION:
        treasure.potion = 1;
        break;
    case Item::WAND:
        treasure.wand = 1;
        break;
    default:
        break;
    }
}

MazeCell* goTo_nextRoom(MazeCell* current_room, char i){
    // SWNE
    // char S = 'S';
    // W = W, N = N, E = E;
    switch (i) {
    case 'S':

            cout << "S" << endl;
            return current_room->south;

    case 'W':

            cout << "W" << endl;
            return current_room->west;

    case 'N':

            cout << "N" << endl;
            return current_room->north;

    case 'E':

            cout << "E" << endl;
            return current_room->east;

    default:
        break;
    }
    return nullptr;
}

/* * * * * * Test Cases Below This Point * * * * * */
#include "GUI/SimpleTest.h"
#include "Demos/MazeGenerator.h"

/* Optional: Add your own custom tests here! */














/* * * * * Provided Tests Below This Point * * * * */

/* Utility function to free all memory allocated for a maze. */
void deleteMaze(const Grid<MazeCell*>& maze) {
    for (auto* elem: maze) {
        delete elem;
    }
    /* Good question to ponder: why don't we write 'delete maze;'
     * rather than what's shown above?
     */
}

PROVIDED_TEST("Checks paths in the sample maze.") {
    auto maze = toMaze({"* *-W *",
                        "| |   |",
                        "*-* * *",
                        "  | | |",
                        "S *-*-*",
                        "|   | |",
                        "*-*-* P"});

    /* These paths are the ones in the handout. They all work. */
    EXPECT(isPathToFreedom(maze[2][2], "ESNWWNNEWSSESWWN"));
    EXPECT(isPathToFreedom(maze[2][2], "SWWNSEENWNNEWSSEES"));
    EXPECT(isPathToFreedom(maze[2][2], "WNNEWSSESWWNSEENES"));

    /* These paths don't work, since they don't pick up all items. */
    EXPECT(!isPathToFreedom(maze[2][2], "ESNW"));
    EXPECT(!isPathToFreedom(maze[2][2], "SWWN"));
    EXPECT(!isPathToFreedom(maze[2][2], "WNNE"));

    /* These paths don't work, since they aren't legal paths. */
    EXPECT(!isPathToFreedom(maze[2][2], "WW"));
    EXPECT(!isPathToFreedom(maze[2][2], "NN"));
    EXPECT(!isPathToFreedom(maze[2][2], "EE"));
    EXPECT(!isPathToFreedom(maze[2][2], "SS"));

    deleteMaze(maze);
}

PROVIDED_TEST("Can't walk through walls.") {
    auto maze = toMaze({"* S *",
                        "     ",
                        "W * P",
                        "     ",
                        "* * *"});

    EXPECT(!isPathToFreedom(maze[1][1], "WNEES"));
    EXPECT(!isPathToFreedom(maze[1][1], "NWSEE"));
    EXPECT(!isPathToFreedom(maze[1][1], "ENWWS"));
    EXPECT(!isPathToFreedom(maze[1][1], "SWNNEES"));

    deleteMaze(maze);
}

PROVIDED_TEST("Works when starting on an item.") {
    auto maze = toMaze({"P-S-W"});

    EXPECT(isPathToFreedom(maze[0][0], "EE"));
    EXPECT(isPathToFreedom(maze[0][1], "WEE"));
    EXPECT(isPathToFreedom(maze[0][2], "WW"));

    deleteMaze(maze);
}

