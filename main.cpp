#include <stdio.h>
#include <algorithm>
#include <iostream>

#include "MapController.h"

void PrintMap(Maze::MapController* controller) {
    Maze::WallMap map = controller->GetWallMap();
    Maze::StepMap sMap = controller->GetStepMap();
    for (int j = Maze::mazeSize - 1; j >= 0; j--) {
        for (int i = 0; i < Maze::mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(Maze::MapDirection::FRONT, std::make_pair(i, j))) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < Maze::mazeSize; i++) {
            if (controller->HasWall(Maze::MapDirection::LEFT, std::make_pair(i, j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            switch (controller->GetPosStatus(std::make_pair(i, j))) {
                case Maze::PosStatus::UNSEARCHED:
                    std::cout << " ? ";
                    break;
                case Maze::PosStatus::GOAL:
                    std::cout << " G ";
                    break;
                case Maze::PosStatus::SEARCHED:
                    std::cout << "   ";
                    break;
                case Maze::PosStatus::CURRENT:
                    std::cout << " ^ ";
                    break;
            }
            if (controller->HasWall(Maze::MapDirection::RIGHT, std::make_pair(i, j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < Maze::mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(Maze::MapDirection::BACK, std::make_pair(i, j))) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "\r";
    }
    std::cout << std::endl << std::endl;

    // 歩数マップ
    for (int j = Maze::mazeSize - 1; j >= 0; j--) {
        for (int i = 0; i < Maze::mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(Maze::MapDirection::FRONT, std::make_pair(i, j))) {
                std::cout << "-----";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < Maze::mazeSize; i++) {
            if (controller->HasWall(Maze::MapDirection::LEFT, std::make_pair(i, j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            printf("%3d", static_cast<int>(sMap.at(i).at(j)));
            std::cout << " ";
            if (controller->HasWall(Maze::MapDirection::RIGHT, std::make_pair(i, j))) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < Maze::mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(Maze::MapDirection::BACK, std::make_pair(i, j))) {
                std::cout << "-----";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << "\r";
    }
    std::cout << std::endl;
    std::cout << "map size:" << sizeof(map) * sizeof(map[0]) << std::endl;

    auto root = controller->GetRoot(Maze::SearchMode::TOGOAL);
    while (!root.empty()) {
        switch (root.front()) {
            case Maze::MapDirection::FRONT:
                std::cout << "^ ";
                break;
            case Maze::MapDirection::BACK:
                std::cout << "v ";
                break;
            case Maze::MapDirection::LEFT:
                std::cout << "< ";
                break;
            case Maze::MapDirection::RIGHT:
                std::cout << "> ";
                break;
        }
        root.pop();
    }
    std::cout << std::endl;
}

int main(void) {
    Maze::MapController* controller = Maze::MapController::GetInstance();
    controller->InitMap();
    Maze::GoalPositon goal = { std::make_pair(5, 6), std::make_pair(5, 7), std::make_pair(6, 6),
                         std::make_pair(6, 7) };
    controller->SetGoal(goal);
    PrintMap(controller);
    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < Maze::mazeSize - 1; i++) {
            controller->SetWall(Maze::MapDirection::RIGHT, std::make_pair(j, i + 1 * (j % 2)));
            controller->UpdateStepMap(controller->GetStep(std::make_pair(j, i + 1 * (j % 2))) - 1);
        }
    }
    PrintMap(controller);
    return 0;
}