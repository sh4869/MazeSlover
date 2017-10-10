#ifndef TYPES_H_
#define TYPES_H_

#include <array>
#include <bitset>
#include <utility>

enum class PosStatus : char { UNSEARCHED, SEARCHED, GOAL, CURRENT };
// 4bitで上の桁から下左だけを保存
using WallInfo = std::pair<std::bitset<2>, PosStatus>;
static constexpr char mazeSize = 16;
// X,Yの順番で指定することにします
using WallMap = std::array<std::array<WallInfo, mazeSize>, mazeSize>;

using MapPosition = std::pair<char, char>;
// Function Alias
static constexpr MapPosition mapPos(char x, char y) { return std::make_pair(x, y); }

using StepMap = std::array<std::array<unsigned char, mazeSize>, mazeSize>;

static constexpr char goalSize = 1;
using GoalPositon = std::array<MapPosition, goalSize>;

#endif