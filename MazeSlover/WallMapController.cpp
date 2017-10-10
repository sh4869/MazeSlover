#include "WallMapController.h"
#include <bitset>
#include <iostream>
#include <utility>

void MapController::SetWall(MapDirection dir, MapPosition pos) {
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

bool MapController::HasWall(MapDirection dir, MapPosition pos) {
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
PosStatus MapController::GetPosStatus(MapPosition pos) {
    return wMap.at(pos.first).at(pos.second).second;
}

unsigned char MapController::GetStep(MapPosition pos) { return sMap.at(pos.first).at(pos.second); }

MapController::MapController() {
    wMap = {};
    WallInfo info = std::make_pair(static_cast<std::bitset<8> >(0), PosStatus::UNSEARCHED);
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
        SetWall(MapDirection::FRONT, std::make_pair(i, mazeSize - 1));
        // 一番下
        SetWall(MapDirection::BACK, std::make_pair(i, 0));
        // 一番左
        SetWall(MapDirection::LEFT, std::make_pair(0, i));
        // 一番右
        SetWall(MapDirection::RIGHT, std::make_pair(mazeSize - 1, i));
    }
    SetWall(MapDirection::RIGHT, std::make_pair(0, 0));
    currentPos = mapPos(0, 0);
    setPosStatus(mapPos(0, 0), PosStatus::CURRENT);
}

const WallMap& MapController::GetWallMap() { return wMap; }
const StepMap& MapController::GetStepMap() { return sMap; }

void MapController::SetGoal(std::array<MapPosition, goalSize> goal) {
    goalPos = goal;
    for (auto g : goal) {
        wMap.at(g.first).at(g.second).second = PosStatus::GOAL;
        sMap.at(g.first).at(g.second) = 0;
    }
    UpdateStepMap(0);
}

void MapController::UpdateStepMap(int startStep) {
    int max = startStep;
    for (int i = 0; i < mazeSize; i++) {
        for (int j = 0; j < mazeSize; j++) {
            if (sMap.at(i).at(j) > startStep) {
                if (sMap.at(i).at(j) > max) {
                    max = sMap.at(i).at(j);
                }
                sMap.at(i).at(j) = 255;
            }
        }
    }
    int count = startStep;
    while (1) {
        for (int i = 0; i < mazeSize; i++) {
            for (int j = 0; j < mazeSize; j++) {
                if (sMap.at(i).at(j) == count) {
                    // RIGHT
                    if (i + 1 != mazeSize && !HasWall(MapDirection::RIGHT, std::make_pair(i, j)) &&
                        sMap.at(i + 1).at(j) == 255) {
                        sMap.at(i + 1).at(j) = count + 1;
                    }
                    // LEFT
                    if (i - 1 != -1 && !HasWall(MapDirection::LEFT, std::make_pair(i, j)) &&
                        sMap.at(i - 1).at(j) == 255) {
                        sMap.at(i - 1).at(j) = count + 1;
                    }
                    // FRONT
                    if (j + 1 != mazeSize && !HasWall(MapDirection::FRONT, std::make_pair(i, j)) &&
                        sMap.at(i).at(j + 1) == 255) {
                        sMap.at(i).at(j + 1) = count + 1;
                    }
                    // BACK
                    if (j - 1 != -1 && !HasWall(MapDirection::BACK, std::make_pair(i, j)) &&
                        sMap.at(i).at(j - 1) == 255) {
                        sMap.at(i).at(j - 1) = count + 1;
                    }
                }
            }
        }
        count++;
        if (count > max && count > mazeSize * mazeSize) {
            break;
        }
    }
}

std::queue<MapDirection> MapController::GetRoot() {
    std::queue<MapDirection> que;
    int step = GetStep(currentPos);
    auto cPos = currentPos;
    while (step > 0) {
        // とりあえず右左上下の順番で探してく形で
        // LEFT
        if (cPos.first - 1 > -1 && !HasWall(MapDirection::LEFT, cPos) &&
            GetStep(mapPos(cPos.first - 1, (char)cPos.second)) == step - 1) {
            que.push(MapDirection::LEFT);
            cPos = mapPos(cPos.first - 1, (char)cPos.second);
            // RIGHT
        } else if (cPos.first + 1 != mazeSize && !HasWall(MapDirection::RIGHT, cPos) &&
                   GetStep(mapPos(cPos.first + 1, (char)cPos.second)) == step - 1) {
            que.push(MapDirection::RIGHT);
            cPos = mapPos(cPos.first + 1, (char)cPos.second);
            // BACK
        } else if (cPos.second - 1 > -1 && !HasWall(MapDirection::BACK, cPos) &&
                   GetStep(mapPos((char)cPos.first, cPos.second - 1)) == step - 1) {
            que.push(MapDirection::BACK);
            cPos = mapPos((char)cPos.first, cPos.second - 1);
            // FRONT
        } else if (cPos.second + 1 != mazeSize && !HasWall(MapDirection::FRONT, cPos) &&
                   GetStep(mapPos((char)cPos.first, cPos.second + 1)) == step - 1) {
            que.push(MapDirection::FRONT);
            cPos = mapPos((char)cPos.first, cPos.second + 1);
        }
        step--;
    }
    return que;
}