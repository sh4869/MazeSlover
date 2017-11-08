#include "MapController.h"

namespace Maze {
    MapController* MapController::instance = nullptr;

    MapController::MapController() {}

    void MapController::SetWall(MapDirection dir, MapPosition pos) {
        switch (dir) {
            // 左と下はそのままset
            case MapDirection::LEFT:
            case MapDirection::BACK:
                wMap.at(pos.first).at(pos.second).set(static_cast<int>(dir));
                break;
            case MapDirection::RIGHT:
                // 一番右は常にtrueにするので設定はしない
                if (Position::IsRightEnd(pos)) {
                    return;
                } else {
                    wMap.at(pos.first + 1).at(pos.second).set(static_cast<int>(MapDirection::LEFT));
                }
                break;
            case MapDirection::FRONT:
                // 一番上は常にtrue
                if (Position::IsTop(pos)) {
                    return;
                } else {
                    wMap.at(pos.first).at(pos.second + 1).set(static_cast<int>(MapDirection::BACK));
                }
                break;
        }
    }

    void MapController::setPositionStatus(MapPosition pos, PositionStatus status) {
        switch (status) {
            case PositionStatus::CURRENT:
                // 11
                wMap.at(pos.first).at(pos.second)[3] = 1;
                wMap.at(pos.first).at(pos.second)[2] = 1;
                break;
            case PositionStatus::GOAL:
                // 10
                wMap.at(pos.first).at(pos.second)[3] = 1;
                wMap.at(pos.first).at(pos.second)[2] = 0;
                break;
            case PositionStatus::SEARCHED:
                // 01
                wMap.at(pos.first).at(pos.second)[3] = 0;
                wMap.at(pos.first).at(pos.second)[2] = 1;
                break;
            case PositionStatus::UNSEARCHED:
                // 00
                wMap.at(pos.first).at(pos.second)[3] = 0;
                wMap.at(pos.first).at(pos.second)[2] = 0;
                break;
        }
    }

    /**
     * @brief あるポジションである方向に対して壁を持っているかを判定します
     *
     * @param dir どの向きか
     * @param pos どの場所か
     * @return true
     * @return false
     */
    bool MapController::HasWall(MapPosition pos, MapDirection dir) {
        switch (dir) {
            case MapDirection::LEFT:
            case MapDirection::BACK:
                return wMap.at(pos.first).at(pos.second)[static_cast<int>(dir)];
            case MapDirection::RIGHT:
                // 一番上は常にtrue
                if (pos.first + 1 == mazeSize) {
                    return true;
                } else {
                    return wMap.at(pos.first + 1)
                        .at(pos.second)[static_cast<int>(MapDirection::LEFT)];
                }
                break;
            case MapDirection::FRONT:
                // 一番右は常にTrue
                if (pos.second + 1 == mazeSize) {
                    return true;
                } else {
                    return wMap.at(pos.first).at(pos.second +
                                                 1)[static_cast<int>(MapDirection::BACK)];
                }
                break;
        }
        return false;
    }

    PositionStatus MapController::GetPositionStatus(MapPosition pos) {
        std::bitset<8> bit = wMap.at(pos.first).at(pos.second);
        return static_cast<PositionStatus>((bit >> 2).to_ulong());
    }

    unsigned char MapController::GetStep(MapPosition pos) {
        return sMap.at(pos.first).at(pos.second);
    }

    void MapController::init() {
        wMap = {};
        WallInfo info = static_cast<std::bitset<8> >(0);
        for (auto m : wMap) {
            m.fill(info);
        }
        // 歩数マップの方の更新
        std::array<unsigned char, mazeSize> arr;
        arr.fill(255);
        sMap.fill(arr);
    }

    MapController* MapController::GetInstance() {
        if (instance == nullptr) {
            instance = new MapController();
            instance->init();
        }
        return instance;
    }

    void MapController::InitMap() {
        MapPosition pos;
        wMap = {};
        WallInfo info = static_cast<std::bitset<8> >(0);
        for (auto m : wMap) {
            m.fill(info);
        }
        for (std::size_t i = 0; i < mazeSize; ++i) {
            // 一番上
            SetWall(MapDirection::FRONT, mapPos(i, mazeSize - 1));
            // 一番下
            SetWall(MapDirection::BACK, std::make_pair(i, 0));
            // 一番左
            SetWall(MapDirection::LEFT, std::make_pair(0, i));
            // 一番右
            SetWall(MapDirection::RIGHT, std::make_pair(mazeSize - 1, i));
        }
        SetWall(MapDirection::RIGHT, std::make_pair(0, 0));
        currentPos = mapPos(0, 0);
        setPositionStatus(mapPos(0, 0), PositionStatus::CURRENT);
    }

    void MapController::SetGoal(std::array<MapPosition, goalSize> goal) {
        goalPos = goal;
        for (auto g : goal) {
            setPositionStatus(mapPos((char)g.first, (char)g.second), PositionStatus::GOAL);
            sMap.at(g.first).at(g.second) = 0;
        }
        UpdateStepMap();
    }

    void MapController::UpdateStepMap() {
        // とりあえず最大値を設定
        for (int i = 0; i < mazeSize; i++) {
            for (int j = 0; j < mazeSize; j++) {
                sMap.at(i).at(j) = 255;
            }
        }
        // ゴール座標を0に設定
        for (auto g : goalPos) {
            sMap.at(g.first).at(g.second) = 0;
        }
        // 歩数マップの生成
        int count = 0;
        while (1) {
            for (int i = 0; i < mazeSize; i++) {
                for (int j = 0; j < mazeSize; j++) {
                    if (sMap.at(i).at(j) == count) {
                        // RIGHT
                        if (i + 1 != mazeSize &&
                            !HasWall(std::make_pair(i, j), MapDirection::RIGHT) &&
                            sMap.at(i + 1).at(j) == 255) {
                            sMap.at(i + 1).at(j) = count + 1;
                        }
                        // LEFT
                        if (i - 1 != -1 && !HasWall(std::make_pair(i, j), MapDirection::LEFT) &&
                            sMap.at(i - 1).at(j) == 255) {
                            sMap.at(i - 1).at(j) = count + 1;
                        }
                        // FRONT
                        if (j + 1 != mazeSize &&
                            !HasWall(std::make_pair(i, j), MapDirection::FRONT) &&
                            sMap.at(i).at(j + 1) == 255) {
                            sMap.at(i).at(j + 1) = count + 1;
                        }
                        // BACK
                        if (j - 1 != -1 && !HasWall(std::make_pair(i, j), MapDirection::BACK) &&
                            sMap.at(i).at(j - 1) == 255) {
                            sMap.at(i).at(j - 1) = count + 1;
                        }
                    }
                }
            }
            count++;
            // TODO : ここをもうちょっと短くしたい
            if (count > mazeSize * mazeSize) {
                break;
            }
        }
    }

    std::queue<MapDirection> MapController::GetRoot(SearchMode mode) {
        std::queue<MapDirection> que;
        int step = GetStep(currentPos);
        auto cPos = currentPos;
        switch (mode) {
            case SearchMode::TOGOAL:
            // TODO: SearchMode::TOUNSEARCHEDの実装
            case SearchMode::TOUNSEARCHED:
                while (step > 0) {
                    // とりあえず右左上下の順番で探してく形で
                    // LEFT
                    if (!HasWall(cPos, MapDirection::LEFT) &&
                        GetStep(Position::GetLeft(cPos)) == step - 1) {
                        que.push(MapDirection::LEFT);
                        cPos = Position::GetLeft(cPos);
                        // RIGHT
                    } else if (!HasWall(cPos, MapDirection::RIGHT) &&
                               GetStep(Position::GetRight(cPos)) == step - 1) {
                        que.push(MapDirection::RIGHT);
                        cPos = Position::GetRight(cPos);
                        // BACK
                    } else if (!HasWall(cPos, MapDirection::BACK) &&
                               GetStep(Position::GetBack(cPos)) == step - 1) {
                        que.push(MapDirection::BACK);
                        cPos = Position::GetBack(cPos);
                        // FRONT
                    } else if (!HasWall(cPos, MapDirection::FRONT) &&
                               GetStep(Position::GetFront(cPos)) == step - 1) {
                        que.push(MapDirection::FRONT);
                        cPos = Position::GetFront(cPos);
                    }
                    step--;
                }
                break;
        }
        return que;
    }

    void MapController::ExportMaze() {}
}