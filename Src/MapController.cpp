#include "MapController.h"
#include <bitset>
#include <iostream>
#include <utility>

void MapController::setWall(MapDirection dir, MapPosition pos) {
    switch (dir) {
        // 左と下はそのままset
        case MapDirection::LEFT:
        case MapDirection::BACK:
            map.at(pos.first).at(pos.second).first.set(static_cast<int>(dir));
            break;
        case MapDirection::RIGHT:
            // 一番右は常にtrueにするので設定はしない
            if (pos.first + 1 == mazeSize) {
                return;
            } else {
                map.at(pos.first + 1).at(pos.second).first.set(static_cast<int>(MapDirection::LEFT));
            }
            break;
        case MapDirection::FRONT:
            // 一番上は常にtrue
            if (pos.second + 1 == mazeSize) {
                return;
            } else {
                map.at(pos.first).at(pos.second + 1).first.set(static_cast<int>(MapDirection::BACK));
            }
            break;
    }
}

void MapController::setPosStatus(MapPosition pos,PosStatus status){
    map.at(pos.first).at(pos.second).second = status;
}

bool MapController::hasWall(MapDirection dir, MapPosition pos, const Map& map) {
    switch(dir){
        case MapDirection::LEFT:
        case MapDirection::BACK:
            return map.at(pos.first).at(pos.second).first[static_cast<int>(dir)];
        case MapDirection::RIGHT:
            // 一番上は常にtrue
            if(pos.first + 1 == mazeSize){
                return true;
            } else {
                return map.at(pos.first + 1).at(pos.second).first[static_cast<int>(MapDirection::LEFT)];
            }
            break;
        case MapDirection::FRONT:
            // 一番右は常にTrue
            if(pos.second + 1 == mazeSize){
                return true;
            } else {
                return map.at(pos.first).at(pos.second + 1).first[static_cast<int>(MapDirection::BACK)];
            }
            break;
    }
    return false;
}
PosStatus MapController::getPosStatus(MapPosition pos, const Map& map) {
    return map.at(pos.first).at(pos.second).second;
}

MapController::MapController() {
    map = {};
    WallInfo info = std::make_pair(static_cast<std::bitset<2> >(0), PosStatus::UNSEARCHED);
    for (auto m : map) {
        m.fill(info);
    }
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
    setPosStatus(std::make_pair(0,0),PosStatus::SEARCHED);
}

const Map& MapController::GetMap() { return map; }

void MapController::SetGoal(std::array<MapPosition,goalSize> goal){
    goalPos = goal;
    for(auto v: goal){
        map.at(v.first).at(v.second).second = PosStatus::GOAL;
    }
}