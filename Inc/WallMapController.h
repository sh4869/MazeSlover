#ifndef MAPCONTROLLER_H_
#define MAPCONTROLLER_H_

#include "Types.h"
#include <array>

enum class MapDirection : int { LEFT, BACK, RIGHT, FRONT };

class MapController {
private:
    WallMap wMap;
    StepMap sMap;
    void setWall(MapDirection dir, MapPosition pos);
    void setPosStatus(MapPosition pos, PosStatus status);
    GoalPositon goalPos;
    MapPosition currentPos;
public:
    bool hasWall(MapDirection dir, MapPosition pos);
    PosStatus getPosStatus(MapPosition pos);
    MapController();
    void InitMap();
    const WallMap& GetWallMap();
    const StepMap& GetStepMap();
    void SetGoal(GoalPositon goal);
    void GenerateStepMap();
};

#endif