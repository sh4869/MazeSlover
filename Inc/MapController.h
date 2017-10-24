#ifndef MAPCONTROLLER_H_
#define MAPCONTROLLER_H_

#include <array>
#include <bitset>
#include <queue>
#include <utility>

// Types
enum class PosStatus : char { UNSEARCHED, SEARCHED, GOAL, CURRENT };
enum class MapDirection : int { LEFT, BACK, RIGHT, FRONT };
enum class SearchMode : int { TOGOAL, TOUNSEARCHED };

// 4bitで上の桁から下左だけを保存
using WallInfo = std::bitset<8>;
static constexpr char mazeSize = 16;
using WallMap = std::array<std::array<WallInfo, mazeSize>, mazeSize>;

using MapPosition = std::pair<char, char>;
static constexpr auto mapPos = std::make_pair<MapPosition::first_type, MapPosition::second_type>;

using StepMap = std::array<std::array<unsigned char, mazeSize>, mazeSize>;

static constexpr char goalSize = 4;
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

    void UpdateStepMap(int startStep);

    // Getter
    bool HasWall(MapDirection dir, MapPosition pos);
    PosStatus GetPosStatus(MapPosition pos);
    unsigned char GetStep(MapPosition pos);
    std::queue<MapDirection> GetRoot(SearchMode mode);
    const WallMap& GetWallMap();
    const StepMap& GetStepMap();

    // Setter
    void SetWall(MapDirection dir, MapPosition pos);
    void SetGoal(GoalPositon goal);
};

#endif