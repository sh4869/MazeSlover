#include "StepMapController.h"
#include "MapController.h"

StepMapController::StepMapController() {
    std::array<unsigned char,mazeSize> arr;
    arr.fill(255);
    sMap.fill(arr);
}

void StepMapController::GenerateStepMap(Map map, GoalPositon goal) {
    for (auto g : goal) {
        sMap.at(g.first).at(g.second) = 0;
    }
    int count = 0;
    while (1) {
        for (int i = 0; i < mazeSize; i++) {
            for (int j = 0; j < mazeSize; j++) {
                if (sMap.at(i).at(j) == count) {
                    // RIGHT
                    if (i + 1 != mazeSize &&
                        !MapController::hasWall(MapDirection::RIGHT, std::make_pair(i, j), map) &&
                        sMap.at(i + 1).at(j) == 255) {
                        sMap.at(i + 1).at(j) = count + 1;
                    }
                    // LEFT
                    if (i - 1 != -1 &&
                        !MapController::hasWall(MapDirection::LEFT, std::make_pair(i, j), map) &&
                        sMap.at(i - 1).at(j) == 255) {
                        sMap.at(i - 1).at(j) = count + 1;
                    }
                    // FRONT
                    if (j + 1 != mazeSize &&
                        !MapController::hasWall(MapDirection::FRONT, std::make_pair(i, j), map) &&
                        sMap.at(i).at(j + 1) == 255) {
                        sMap.at(i).at(j + 1) = count + 1;
                    }
                    // BACK
                    if (j - 1 != -1 &&
                        !MapController::hasWall(MapDirection::BACK, std::make_pair(i, j), map) &&
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

const StepMap& StepMapController::GetStepMap() { return sMap; }