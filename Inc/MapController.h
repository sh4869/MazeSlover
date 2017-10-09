#ifndef MAPCONTROLLER_H_
#define MAPCONTROLLER_H_

#include "Types.h"
#include <array>

enum class MapDirection : int { LEFT, BACK, RIGHT, FRONT };

class MapController {
private:
    Map map;
    void setWall(MapDirection dir, MapPosition pos);
    void setPosStatus(MapPosition pos, PosStatus status);
    GoalPositon goalPos;
public:
    static bool hasWall(MapDirection dir, MapPosition pos, const Map& map);
    static PosStatus getPosStatus(MapPosition pos, const Map& map);
    MapController();
    void InitMap();
    const Map& GetMap();
    void SetGoal(GoalPositon goal);
};

#endif