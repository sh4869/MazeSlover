#include <iostream>
#include <stdio.h>

#include "MapController.h"
#include "StepMapController.h"

void PrintMap(Map map,StepMap sMap) {
    for (int j = mazeSize - 1; j >= 0; j--) {
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (MapController::hasWall(MapDirection::FRONT, std::make_pair(i, j), map)) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            if (MapController::hasWall(MapDirection::LEFT, std::make_pair(i, j), map)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            switch(MapController::getPosStatus(std::make_pair(i,j),map)){
                case PosStatus::UNSEARCHED:
                    std::cout << " ? ";
                    break;
                case PosStatus::GOAL:
                    std::cout << " G ";
                    break;
                case PosStatus::SEARCHED:
                    std::cout << "   ";
                    break;
            }
            if (MapController::hasWall(MapDirection::RIGHT, std::make_pair(i, j), map)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (MapController::hasWall(MapDirection::BACK, std::make_pair(i, j), map)) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "\r";
    }
    std::cout << std::endl << std::endl;

    for (int j = mazeSize - 1; j >= 0; j--) {
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (MapController::hasWall(MapDirection::FRONT, std::make_pair(i, j), map)) {
                std::cout << "-----";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            if (MapController::hasWall(MapDirection::LEFT, std::make_pair(i, j), map)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            printf("%3d",static_cast<int>(sMap.at(i).at(j)));
            std::cout << " ";
            if (MapController::hasWall(MapDirection::RIGHT, std::make_pair(i, j), map)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < mazeSize; i++) {
            std::cout << "*";
            if (MapController::hasWall(MapDirection::BACK, std::make_pair(i, j), map)) {
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
    MapController *controller = new MapController();
    StepMapController *sMapController = new StepMapController();
    controller->InitMap();
    GoalPositon goal = {
        std::make_pair(3,0)
    };
    PrintMap(controller->GetMap(),sMapController->GetStepMap());
    controller->SetGoal(goal);
    sMapController->GenerateStepMap(controller->GetMap(),goal);
    PrintMap(controller->GetMap(),sMapController->GetStepMap());
    return 0;
}