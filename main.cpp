#include <stdio.h>
#include <iostream>

#include "WallMapController.h"

void PrintMap(MapController* controller) {
    WallMap map = controller->GetWallMap();
    StepMap sMap = controller->GetStepMap();
    for (int j = mazeSize - 1; j >= 0; j--) {
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (controller->hasWall(MapDirection::FRONT, mapPos(i,j))) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            if (controller->hasWall(MapDirection::LEFT, mapPos(i,j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            switch (controller->getPosStatus(mapPos(i,j))) {
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
            if (controller->hasWall(MapDirection::RIGHT, mapPos(i,j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (controller->hasWall(MapDirection::BACK, mapPos(i,j))) {
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
            if (controller->hasWall(MapDirection::FRONT, mapPos(i,j))) {
                std::cout << "-----";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            if (controller->hasWall(MapDirection::LEFT, mapPos(i,j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            printf("%3d", static_cast<int>(sMap.at(i).at(j)));
            std::cout << " ";
            if (controller->hasWall(MapDirection::RIGHT, mapPos(i,j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (controller->hasWall(MapDirection::BACK, mapPos(i,j))) {
                std::cout << "-----";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << "\r";
    }
    std::cout << std::endl;
    std::cout << "map size:" << sizeof(map) * sizeof(map[0]) << std::endl;
}

int main(void) {
    MapController* controller = new MapController();
    controller->InitMap();
    GoalPositon goal = { std::make_pair(3, 0) };
    PrintMap(controller);
    controller->SetGoal(goal);
    controller->GenerateStepMap();
    PrintMap(controller);
    return 0;
}