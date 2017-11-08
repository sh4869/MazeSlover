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
            if (controller->HasWall(std::make_pair(i, j),Maze::MapDirection::FRONT)) {
                std::cout << "---";
            } else {
                std::cout << "   ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < Maze::mazeSize; i++) {
            if (controller->HasWall(std::make_pair(i, j),Maze::MapDirection::LEFT)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            switch (controller->GetPositionStatus(std::make_pair(i, j))) {
                case Maze::PositionStatus::UNSEARCHED:
                    std::cout << " ? ";
                    break;
                case Maze::PositionStatus::GOAL:
                    std::cout << " G ";
                    break;
                case Maze::PositionStatus::SEARCHED:
                    std::cout << "   ";
                    break;
                case Maze::PositionStatus::CURRENT:
                    std::cout << " ^ ";
                    break;
            }
            if (controller->HasWall(std::make_pair(i, j),Maze::MapDirection::RIGHT)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < Maze::mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(std::make_pair(i, j),Maze::MapDirection::BACK)) {
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
            if (controller->HasWall(std::make_pair(i, j),Maze::MapDirection::FRONT)) {
                std::cout << "-----";
            } else {
                std::cout << "     ";
            }
        }
        std::cout << "*" << std::endl;
        for (int i = 0; i < Maze::mazeSize; i++) {
            if (controller->HasWall(std::make_pair(i, j),Maze::MapDirection::LEFT)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << " ";
            printf("%3d", static_cast<int>(sMap.at(i).at(j)));
            std::cout << " ";
            if (controller->HasWall(std::make_pair(i, j),Maze::MapDirection::RIGHT)) {
                std::cout << "|";
            } else {
                std::cout << " ";
            }
            std::cout << "\b";
        }
        std::cout << std::endl;
        for (int i = 0; i < Maze::mazeSize; i++) {
            std::cout << "*";
            if (controller->HasWall(std::make_pair(i, j),Maze::MapDirection::BACK)) {
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
    Maze::GoalPositon goal = { Maze::mapPos(5, 6), Maze::mapPos(5, 7), Maze::mapPos(6, 6),
                               Maze::mapPos(6, 7) };
    controller->SetGoal(goal);
    PrintMap(controller);
    for (int j = 0; j < Maze::mazeSize - 1; j++) {
        for (int i = 0; i < Maze::mazeSize - 1; i++) {
            controller->SetWall(Maze::MapDirection::RIGHT, std::make_pair(j, i + 1 * (j % 2)));
            controller->UpdateStepMap();
        }
    }
    PrintMap(controller);
    return 0;
}