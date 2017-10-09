#ifndef STEPMAP_H_
#define STEPMAP_H_

#include "Types.h"

class StepMapController {
    StepMap sMap;
public:
    StepMapController();
    void GenerateStepMap(Map map,GoalPositon goal);
    const StepMap& GetStepMap();
};

#endif