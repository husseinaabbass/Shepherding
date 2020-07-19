#pragma once
#ifndef UTILITIES_H
#define UTILITIES_H
//#include "Agents.h"
#include <vector>
#include <list>
#include "Vector2.h"
#include <numeric>      // std::iota
#include <algorithm>    // std::sort
#include "SheepDogAgent.h"

#include"Flock.h"
#include "Environment.h"



		//double calcDistTwoLoc(Vector2f Loc1, Vector2f Loc2); //return the Euclidean distance between two locations

		Vector2f calculateLocalCentreOfMass(SheepList sheepList);

		Vector2f calculateGloablCentreOfMass(SheepFlock* sheepList);
		
		//std::tuple<SheepList, std::vector<int>> SenseSheepInNeighborhood(Agent* agent, int targetSizeOfNeighborhood, Environment& env);
		//SheepList SenseSheepInNeighborhood(Agent* agent, int targetSizeOfNeighborhood, Environment& env);
		SheepList SenseSheepInNeighborhoodBasedOnNumber(Agent* agent, int targetSizeOfNeighborhood, Environment& env);

		SheepList SenseSheepInNeighborhoodBasedOnDist(Agent * agent, Environment & env, float Dist);

		SheepList SenseSheepOutOfFlock(Agent* agent, Environment& env);

		std::vector<int> RankSheepBasedOnDistTo(Vector2f pointP, SheepList mySheepList);
		std::vector<int> RankSheepBasedOnDistTo(Vector2f pointP, SheepFlock mySheepList); //overrid using sheeplist rather than the sheepflock
		std::vector<int> RankSheepBasedOnDistTo(Vector2f pointP, std::vector<DetectedSheepRow> mySheepList); //overrid using vector of detected sheeprow


		//template <typename T>
		//std::vector<size_t> sort_indexes(const std::vector<T> &v);

		template <typename T>
		std::vector<int> sort_indexes(const std::vector<T> &v);

		std::string type_name();
		float calc_regulated_force_magnitudeM1(float d1, float minD, float maxD, float ModulationDecayFactor);
		float calc_regulated_force_magnitudeM2(float d1, float minD, float maxD, int numAgents, float ModulationDecayFactor);

		SheepList SenseSheepOutOfFlockCentrally(Environment& env, Vector2f GCM);
		std::vector<DetectedSheepRow> SenseSheepOutOfFlockUsingLocalInformation(Vector2f LCM, std::vector<DetectedSheepRow> totalList, Environment& env);



#endif