#ifndef MAPCONTROLLER_H_
#define MAPCONTROLLER_H_

#include "MapPosition.h"

#include <array>
#include <bitset>
#include <queue>
#include <utility>

// Types
namespace Maze {
/**
 * Position Status of Maze
 */
enum class PosStatus : char { UNSEARCHED, SEARCHED, GOAL, CURRENT };
enum class MapDirection : int { LEFT, BACK, RIGHT, FRONT };
enum class SearchMode : int { TOGOAL, TOUNSEARCHED };


using WallInfo = std::bitset<8>;
using WallMap = std::array<std::array<WallInfo, mazeSize>, mazeSize>;
using StepMap = std::array<std::array<unsigned char, mazeSize>, mazeSize>;
using GoalPositon = std::array<MapPosition, goalSize>;

class MapController {
private:
    static MapController* instance;
    WallMap wMap;
    StepMap sMap;

    GoalPositon goalPos;
    MapPosition currentPos;

    MapController();
    void init();
    void setPosStatus(MapPosition pos, PosStatus status);

public:
    static MapController* GetInstance();
    void InitMap();

    void UpdateStepMap();

    /**
     * @brief Export Maze for filesystem
     *
     */
    void ExportMaze();

    // Getter
    
    bool HasWall(MapDirection dir, MapPosition pos);
    PosStatus GetPosStatus(MapPosition pos);
    unsigned char GetStep(MapPosition pos);
    std::queue<MapDirection> GetRoot(SearchMode mode);
    const WallMap& GetWallMap() { return wMap; }
    const StepMap& GetStepMap() { return sMap; }

    // Setter
    void SetWall(MapDirection dir, MapPosition pos);
    void SetGoal(GoalPositon goal);
};
}

#endif
