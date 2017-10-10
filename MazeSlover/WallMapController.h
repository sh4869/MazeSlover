#ifndef MAPCONTROLLER_H_
#define MAPCONTROLLER_H_

#include "Types.h"
#include <array>
#include <queue>

enum class MapDirection : int { LEFT, BACK, RIGHT, FRONT };

class MapController {
private:
    WallMap wMap;
    StepMap sMap;
    
    void setPosStatus(MapPosition pos, PosStatus status);
    GoalPositon goalPos;
    MapPosition currentPos;
public:

    MapController();
    void InitMap();

    void UpdateStepMap(int startStep);

    // Getter
    bool HasWall(MapDirection dir, MapPosition pos);
    PosStatus GetPosStatus(MapPosition pos);
    unsigned char GetStep(MapPosition pos);
    std::queue<MapDirection> GetRoot();
    const WallMap& GetWallMap();
    const StepMap& GetStepMap();
    
    // Setter
    void SetWall(MapDirection dir, MapPosition pos);
    void SetGoal(GoalPositon goal);
    
};

#endif