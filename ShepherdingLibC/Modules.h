#pragma once
#ifndef MODULES_H
#define MODULES_H
//#include "Agents.h"
#include "SheepDogAgent.h"
#include "SheepAgent.h"

//#include <vector>
//#include <list>
//#include "Vector2.h"
//#include<string>

void UpdateSheepBehaviors(SheepAgent* sheepIter, int timestep);
void UpdateSheepDogBehaviors(SheepDogAgent* sheepDog, int timestep, int mode);
std::list<Vector2f> computeCoveringPoints(std::string coveringAlgorithm, int parameter);
std::list<Vector2f> hilbert(int n);

#endif

