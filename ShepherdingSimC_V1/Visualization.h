//#pragma once
//#ifndef Simu.h
//#define Simu.h
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string> 
#include "Environment.h"
#include "SDL_image.h"
#include "Vector2.h"
#include<fstream>
class Visualization {
public:
	Visualization();
	~Visualization();
	//void init(const char * title, int screenWidth, int screenHeight, int fieldWidth, int fieldHeight);




	//void init(std::string title, int inScale, int simSpeed, int screenWidth, int screenHeight, int fieldWidth, int fieldHeight, int N, int M, int R_pi_beta, int Ra_pi_pi, int R_beta_beta, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, int R2, int R3, int goalRadius, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange);



	void init(std::string title, int inScale, int simSpeed, int screenWidth, int screenHeight, int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, 		int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius);

	void init(std::string title, int inScale, int simSpeed, int screenWidth, int screenHeight, int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius, bool CollisionAvoidanceOpponentsForceOn, bool CollisionAvoidanceFriendsForceOn, bool AttractionBehaviorForceOn, bool CollisionAvoidanceStaticObstaclesForceOn, bool JitteringForceOn);

	void init(std::string title, int inScale, int simSpeed, int screenWidth, int screenHeight, int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius, bool CollisionAvoidanceOpponentsForceON, bool CollisionAvoidanceFriendsForceON, bool AttractionBehaviorForceON, bool CollisionAvoidanceStaticObstaclesForceON, bool JitteringForceON, bool scaleForceVisualization);

	void init(int randomNumberSeed, std::string title, int inScale, int simSpeed, int screenWidth, int screenHeight, int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius, bool CollisionAvoidanceOpponentsForceON, bool CollisionAvoidanceFriendsForceON, bool AttractionBehaviorForceON, bool CollisionAvoidanceStaticObstaclesForceON, bool JitteringForceON, bool scaleForceVisualization);

	void handleEvents();
	void update(std::ofstream & outfile, std::ofstream & outputCompletionTimefile);
	//void update();
	void render();
	void clean();
	bool running();	
	//void streamOut(std::ofstream & outfile);
	void streamOut(std::ofstream & outfile, std::ofstream & outputCompletionTimefile);


	//double Time();
private:
	bool isRunning;
	SDL_Window *   window = NULL;
	SDL_Renderer * gRenderer = NULL;
	SDL_Surface* screen = NULL;
	SDL_Texture* texture = NULL;
	

	Uint32 startTime;
	int currentTime;

	void DrawText(std::string stringText, int x, int y, TTF_Font * font1, std::string pos);
	//void DrawPoint(int pointLocationx, int pointLocationy, int scale);
	void DrawFlock();
	void DrawObstacles();
	//std::list<float> streamOut(std::ofstream & outfile);
	int fieldStartX;
	int fieldStartY;
	//void DrawPoint(int pointLocationx, int pointLocationy, int scale, Uint8 r, Uint8 g, Uint8 b);
	void DrawPoint(float pointLocationx, float pointLocationy, float pointSize, Uint8 r, Uint8 g, Uint8 b);
	void DrawForce(float x, float y, Vector2f force, SDL_Texture* arrowTexture, int arrowimageScale, bool ScaleForceVisualization);
	void DrawForce(float x, float y, Vector2f force, SDL_Texture * arrowTexture, int arrowscale);

};


//#endif
