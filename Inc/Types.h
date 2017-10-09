#ifndef TYPES_H_
#define TYPES_H_

#include <array>
#include <bitset>
#include <utility>

enum class PosStatus : char { UNSEARCHED, SEARCHED, GOAL };
// 4bitで上の桁から下左だけを保存
using WallInfo = std::pair<std::bitset<2>, PosStatus>;
static constexpr int mazeSize = 16;
// X,Yの順番で指定することにします
using Map = std::array<std::array<WallInfo, mazeSize>, mazeSize>;
using MapPosition = std::pair<int, int>;
using StepMap = std::array<std::array<unsigned char,mazeSize>,mazeSize>;

static constexpr int goalSize = 1;
using GoalPositon = std::array<MapPosition,goalSize>;

#endif