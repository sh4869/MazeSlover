#include "WallMapController.h"
#include <bitset>
#include <iostream>
#include <utility>

void MapController::setWall(MapDirection dir, MapPosition pos) {
    switch (dir) {
        // 左と下はそのままset
        case MapDirection::LEFT:
        case MapDirection::BACK:
            wMap.at(pos.first).at(pos.second).first.set(static_cast<int>(dir));
            break;
        case MapDirection::RIGHT:
            // 一番右は常にtrueにするので設定はしない
            if (pos.first + 1 == mazeSize) {
                return;
            } else {
                wMap.at(pos.first + 1)
                    .at(pos.second)
                    .first.set(static_cast<int>(MapDirection::LEFT));
            }
            break;
        case MapDirection::FRONT:
            // 一番上は常にtrue
            if (pos.second + 1 == mazeSize) {
                return;
            } else {
                wMap.at(pos.first)
                    .at(pos.second + 1)
                    .first.set(static_cast<int>(MapDirection::BACK));
            }
            break;
    }
}

void MapController::setPosStatus(MapPosition pos, PosStatus status) {
    wMap.at(pos.first).at(pos.second).second = status;
}

bool MapController::hasWall(MapDirection dir, MapPosition pos) {
    switch (dir) {
        case MapDirection::LEFT:
        case MapDirection::BACK:
            return wMap.at(pos.first).at(pos.second).first[static_cast<int>(dir)];
        case MapDirection::RIGHT:
            // 一番上は常にtrue
            if (pos.first + 1 == mazeSize) {
                return true;
            } else {
                return wMap.at(pos.first + 1)
                    .at(pos.second)
                    .first[static_cast<int>(MapDirection::LEFT)];
            }
            break;
        case MapDirection::FRONT:
            // 一番右は常にTrue
            if (pos.second + 1 == mazeSize) {
                return true;
            } else {
                return wMap.at(pos.first)
                    .at(pos.second + 1)
                    .first[static_cast<int>(MapDirection::BACK)];
            }
            break;
    }
    return false;
}
PosStatus MapController::getPosStatus(MapPosition pos) {
    return wMap.at(pos.first).at(pos.second).second;
}

MapController::MapController() {
    wMap = {};
    WallInfo info = std::make_pair(static_cast<std::bitset<2> >(0), PosStatus::UNSEARCHED);
    for (auto m : wMap) {
        m.fill(info);
    }
    // 歩数マップの方の更新
    std::array<unsigned char, mazeSize> arr;
    arr.fill(255);
    sMap.fill(arr);
    // とりあえずスタート地点は(0,0)
}

void MapController::InitMap() {
    MapPosition pos;
    for (std::size_t i = 0; i < mazeSize; ++i) {
        // 一番上
        setWall(MapDirection::FRONT, std::make_pair(i, mazeSize - 1));
        // 一番下
        setWall(MapDirection::BACK, std::make_pair(i, 0));
        // 一番左
        setWall(MapDirection::LEFT, std::make_pair(0, i));
        // 一番右
        setWall(MapDirection::RIGHT, std::make_pair(mazeSize - 1, i));
    }
    setWall(MapDirection::RIGHT, std::make_pair(0, 0));
    currentPos = mapPos(0,0);
    setPosStatus(mapPos(0, 0), PosStatus::CURRENT);
}

const WallMap& MapController::GetWallMap() { return wMap; }
const StepMap& MapController::GetStepMap() { return sMap; }

void MapController::SetGoal(std::array<MapPosition, goalSize> goal) {
    goalPos = goal;
    for (auto v : goal) {
        wMap.at(v.first).at(v.second).second = PosStatus::GOAL;
    }
}

void MapController::GenerateStepMap() {
    for (auto g : goalPos) {
        sMap.at(g.first).at(g.second) = 0;
    }
    int count = 0;
    while (1) {
        for (int i = 0; i < mazeSize; i++) {
            for (int j = 0; j < mazeSize; j++) {
                if (sMap.at(i).at(j) == count) {
                    // RIGHT
                    if (i + 1 != mazeSize &&
                        !MapController::hasWall(MapDirection::RIGHT, std::make_pair(i, j)) &&
                        sMap.at(i + 1).at(j) == 255) {
                        sMap.at(i + 1).at(j) = count + 1;
                    }
                    // LEFT
                    if (i - 1 != -1 &&
                        !MapController::hasWall(MapDirection::LEFT, std::make_pair(i, j)) &&
                        sMap.at(i - 1).at(j) == 255) {
                        sMap.at(i - 1).at(j) = count + 1;
                    }
                    // FRONT
                    if (j + 1 != mazeSize &&
                        !MapController::hasWall(MapDirection::FRONT, std::make_pair(i, j)) &&
                        sMap.at(i).at(j + 1) == 255) {
                        sMap.at(i).at(j + 1) = count + 1;
                    }
                    // BACK
                    if (j - 1 != -1 &&
                        !MapController::hasWall(MapDirection::BACK, std::make_pair(i, j)) &&
                        sMap.at(i).at(j - 1) == 255) {
                        sMap.at(i).at(j - 1) = count + 1;
                    }
                }
            }
        }
        count++;
        if (count > mazeSize * mazeSize) {
            break;
        }
    }
}