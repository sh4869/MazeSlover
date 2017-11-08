#ifndef MAPCONTROLLER_H_
#define MAPCONTROLLER_H_

#include "MapPosition.h"
#include "MazeTypes.h"
#include <array>
#include <bitset>
#include <queue>
#include <utility>

// Types
namespace Maze {

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
    void setPositionStatus(MapPosition pos, PositionStatus status);

public:
    static MapController* GetInstance();
    void InitMap();
    void ExportMaze();    
    void UpdateStepMap();

    bool HasWall(MapPosition pos, MapDirection dir);
    PositionStatus GetPositionStatus(MapPosition pos);
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
