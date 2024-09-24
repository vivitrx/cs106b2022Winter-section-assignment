#ifndef Labyrinth_Included
#define Labyrinth_Included

#include "GUI/MemoryDiagnostics.h"
#include <string>

/**
 * Type representing an item in the maze.
 */
enum class Item {
    NOTHING, SPELLBOOK, POTION, WAND
};

/**
 * Type representing a cell in the maze.
 */
struct MazeCell {
    Item whatsHere; // Which item, if any, is present.

    MazeCell* north;
    MazeCell* south;
    MazeCell* east;
    MazeCell* west;
};

// 自定义变量，用于确认是否找到三件宝物
struct Treasure {
    bool spellbook = 0;
    bool potion = 0;
    bool wand = 0;
};
/**
 * Given a location in a maze, returns whether the given sequence of
 * steps will let you escape the maze.
 *
 * To escape the maze, you need to find the Potion, the Spellbook, and
 * the Wand. You can only take steps in the four cardinal directions,
 * and you can't move in directions that don't exist in the maze.
 */
bool isPathToFreedom(MazeCell* start, const std::string& moves);

void findTueasure(Treasure& treasure, Item item);

MazeCell* goTo_nextRoom(MazeCell* current_room, char i);


/**
 * We provide this function for you so that, if you so choose, you can
 * store Item variables in a HashMap or HashSet.
 */
inline int hashCode(Item item) {
    return static_cast<int>(item);
}

#endif
