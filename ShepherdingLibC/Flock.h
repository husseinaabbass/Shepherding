#pragma once
#ifndef FLOCK_EXPORT
#define FLOCK_API __declspec(dllexport)
#else
#define FLOCK_API __declspec(dllimport)
#endif

#include "Agents.h"
#include <vector>
#include <list>





class FLOCK_API SheepFlock: public std::vector<SheepAgent*> {
public:
	SheepFlock();
	SheepFlock(std::mt19937 generator, int numSheepList, float xMin, float xMax, float yMin, float yMax, int startingID, std::string pattern);
	
	void CalcNewLoc();
	void Move();

private:
	int numSheepList;
	};

class FLOCK_API SheepDogFlock :public std::vector<SheepDogAgent*> {
public:
	SheepDogFlock();
	SheepDogFlock(std::mt19937 generator, int numSheepDogsList, float xMin, float xMax, float yMin, float yMax, int startingID, float sheepDogAgentSpeed);
	void CalcNewLoc();
	void Move();

private:

	int numSheepDogsList;
};

class FLOCK_API SheepList : public std::vector<SheepAgent*>

{
	//public:

};

//
//class FLOCK_API SheepDogsList : public std::vector<SheepDogAgent*>
//{
//public:
//
//};