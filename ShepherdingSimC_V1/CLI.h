#pragma once
#include <iostream>
#include<vector>
#include <list>
#include<fstream>
#include "Flock.h"

class CLI
{
public:
	CLI();
	~CLI();
	



	
	void init(int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float R_beta_pi, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor,	int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius);

	void init(int randomNumberSeed, int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float R_beta_pi, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius);

	//void init(int randomNumberSeed, int fieldStartX, int fieldStartY, int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta,  float R_beta_pi, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius);

	void handleEvents();
	
	void update();

	//std::list<float> streamOut(std::ofstream & outfile, std::ofstream & outputCompletionTimefile);
	void streamOut(std::ofstream & outfile, std::ofstream & outputCompletionTimefile);
	bool running();
private:
	bool isRunning;



	int startTime;
	int currentTime;

	int fieldStartX;
	int fieldStartY;


};

