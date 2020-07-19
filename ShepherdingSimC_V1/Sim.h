//#pragma once
//#ifndef Simu.h
//#define Simu.h

#include <iostream>
#include <string> 
//#include "Agents.h"
#include "SheepDogAgent.h"
#include "Environment.h"
#include"Vector2.h"
//int numSheepAgents = 10;
//Flock* flock;
//SheepAgent sheep;


class Simulation{
public:
	Simulation();
	~Simulation();
	//void init(int numSheepAgents, int numSheepDogAgents, int fieldStartX, int fieldStartY, int fieldWidth, int fieldHeight, int paddockLength, int paddockWidth);
	void init(int numSheepAgents, int numSheepDogAgents, int fieldStartX, int fieldStartY, int fieldWidth, int fieldHeight, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float R_beta_pi, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLength, int paddockWidth, bool paddockON, bool CircularPathPlanningON, bool StallingON, float StallingDistance, int R2, int r3, int GoalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, 		int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, float obstaclesDensity, float obstaclesRadius);

	
	
	

	void init(int randomNumberSeed, int numSheepAgents, int numSheepDogAgents, int fieldStartX, int fieldStartY, int fieldWidth, int fieldHeight, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float R_beta_pi, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLength, int paddockWidth, bool paddockON, bool CircularPathPlanningON, bool StallingON, float StallingDistance, int R2, int r3, int GoalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, float obstaclesDensity, float obstaclesRadius);

	void update();
	void checkIfGoalFound();
	void checkIfGoalFound2();
	void checkNotDisturbingSheep(float safeDist, SheepDogAgent * sheepDog);

	void checkSheepDogNotDisturbingSheep(SheepDogFlock * sheepDogFlock, SheepFlock * sheepFlock);

	/*void checkSheepDogNotDisturbingSheep(SheepDogFlock * sheepDogFlock, SheepFlock * sheepFlock, int circularPathPlanningRadius, int CircularPathPlanningMode);*/
	

	void clean();
	void CheckFenceViolation(std::vector<Vector2f> paddockBoundry, SheepFlock * sheepFlock, SheepDogFlock * sheepDogFlock);
	//float roundFloat2f(float myfloat);
	int timestep;
	bool goalFound ;

private:
	int fieldStartX;
	int fieldStartY;
	int paddockLength;
	int paddockWidth;
	int goalRadius;
	std::vector<Vector2f> paddockBoundry;
	bool circularPathPlanning;
	

	//bool circularPathPlanning;
	
	
};


//#endif
