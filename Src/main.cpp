#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "WallMapController.h"

void PrintMap(MapController* controller) {
    WallMap map = controller->GetWallMap();
    StepMap sMap = controller->GetStepMap();
    for (int j = mazeSize - 1; j >= 0; j--) {
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(MapDirection::FRONT, mapPos(i, j))) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            if (controller->HasWall(MapDirection::LEFT, mapPos(i, j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            switch (controller->GetPosStatus(mapPos(i, j))) {
                case PosStatus::UNSEARCHED:
                    std::cout << " ? ";
                    break;
                case PosStatus::GOAL:
                    std::cout << " G ";
                    break;
                case PosStatus::SEARCHED:
                    std::cout << "   ";
                    break;
                case PosStatus::CURRENT:
                    std::cout << " ^ ";
                    break;
            }
            if (controller->HasWall(MapDirection::RIGHT, mapPos(i, j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(MapDirection::BACK, mapPos(i, j))) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "\r";
    }
    std::cout << std::endl << std::endl;

    // 歩数マップ
    for (int j = mazeSize - 1; j >= 0; j--) {
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(MapDirection::FRONT, mapPos(i, j))) {
                std::cout << "-----";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            if (controller->HasWall(MapDirection::LEFT, mapPos(i, j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            printf("%3d", static_cast<int>(sMap.at(i).at(j)));
            std::cout << " ";
            if (controller->HasWall(MapDirection::RIGHT, mapPos(i, j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(MapDirection::BACK, mapPos(i, j))) {
                std::cout << "-----";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << "\r";
    }
    std::cout << std::endl;
    std::cout << "map size:" << sizeof(map) * sizeof(map[0]) << std::endl;
    /*
    auto root = controller->GetRoot();
    while (!root.empty()) {
        switch (root.front()) {
            case MapDirection::FRONT:
                std::cout << "^ ";
                break;
            case MapDirection::BACK:
                std::cout << "v ";
                break;
            case MapDirection::LEFT:
                std::cout << "< ";
                break;
            case MapDirection::RIGHT:
                std::cout << "> ";
                break;
        }
        root.pop();
    }
    std::cout << std::endl;
    */
}

int main(void) {
    MapController* controller = new MapController();
    controller->InitMap();
    GoalPositon goal = { std::make_pair(15, 0) };
    PrintMap(controller);
    controller->SetGoal(goal);
    PrintMap(controller);
    for (int j = 0; j < mazeSize - 1; j++) {
        for (int i = 0; i < mazeSize - 1; i++) {
            controller->SetWall(MapDirection::RIGHT, mapPos(j, i + 1 * (j % 2)));
            controller->UpdateStepMap(controller->GetStep(mapPos(j, i + 1 * (j % 2))) - 1);
        }
    }
    PrintMap(controller);
    return 0;
}