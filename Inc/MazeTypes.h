#ifndef MAZEMAP_TYPES_H_
#define MAZEMAP_TYPES_H_

namespace Maze {
    enum class PositionStatus : char { UNSEARCHED, SEARCHED, GOAL, CURRENT };
    enum class MapDirection : int { LEFT, BACK, RIGHT, FRONT };
    enum class SearchMode : int { TOGOAL, TOUNSEARCHED };
}

#endif