//#pragma once
//#ifndef ENVIRONMENT_H
//#define ENVIRONMENT_H __declspec(dllexport)
//#else
//#define ENVIRONMENT_H __declspec(dllimport)
//#endif

#pragma once
#ifndef ENVIRONMENT_EXPORT
#define ENVIRONMENT_API __declspec(dllexport) 
#else
#define ENVIRONMENT_API __declspec(dllimport) 
#endif

#include <vector>
#include <list>
//#include "Flock.h"
#include "Vector2.h"
#include<string>
#include"Terrain.h"

//class Flock;
class SheepFlock;
class SheepDogFlock;
//struct expectedKnowledgePerSheepdog {
//	int dogID;
//	std::string dogName;
//	int RefDogID;
//	std::string dogLocationRelevant2RefDog;
//	std::string dogCurrentState;
//	Vector2f dogCurrentLocation;
//	Vector2f goalLoc;
//	Vector2f GCM;
//	int furthestSheepID;
//	
//
//};

struct SheepDogRosterDatarow {
	int dogID;
	std::string dogAssignedTask;


};

struct expectedDrivingKnowledgePerSheepdog {
	int dogID;
	std::string dogName;
	int RefDogID;
	std::string dogLocationRelevant2RefDog;
	Vector2f dogCurrentLocation;
	Vector2f GCM;
};

struct expectedCollectingKnowledgePerSheepdog {
	int dogID;
	int AssignedSheepID;
	Vector2f AssignedSheepLoc;
	Vector2f GCM;
};

class ENVIRONMENT_API Environment
{
//private: 
	
	

public:
	static Environment& getInstance();
	//Environment(const Environment&) = default;
//	Environment& operator=(const Environment&) = default;
	int FieldWidth;
	int FieldHeight;
	int N;					//(1--201)           & Cardinality of Pi
	int M;					// (1--20)            & Cardinality of B
	float R_pi_beta;			// (65u)			& pi sensing range for beta
	float Ra_pi_pi;			// (2u)				& pi collision avoidance range for pi
	float Rs_pi_pi;			// (20u)				& pi collision avoidance range for pi

	float R_beta_beta ;// 10			// (2u)				& beta sensing range for beta
	int	card_Omega_pi_pi;	// 					& Number of  agents(neighbourhood) a sheep agent operates on
	int card_Omega_beta_pi;//					& Number of  agents(neighbourhood) a sheepDog agent operates on
	float W_pi_pi;			// (2)				& pi repulsion strength from pi
	float W_beta_beta;
	float W_pi_beta;		// (1)				& pi repulsion strength from beta
	float W_pi_Lambda;		// (1.05)			& pi attraction strength to Lambda
	float W_pi_upsilon;	// (0.5)			& Strength of pi previous direction
	float W_e_pi_i;		// (0.3)			& Strength of sheep pi_j angular noise
	float W_e_beta_j;		// (0.3)			& Strength of shepherd beta_j angular noise
	float fN;				// define how fN is calculated.. 	float fN = env.Ra_pi_pi*pow(env.N, ((float)2 / (float)3));
	float R1; // an alias for fn
	Vector2f PG;			// location of the goal;
	float S_t_beta_j;
	float eta ;					//(0.05)			& Probability of moving per time step while grazing
	int R2;
	int R3;
	int DrivingPositionEq;
	int CollectingPositionEq;
	int SheepNeignborhoodSelection;
	int ModulationDecayFactor;
	int ForceRegulated;
	bool stallingON;
	float stallingDist;
	std::vector<SheepDogRosterDatarow> SheepDogRoster;
	std::vector<expectedCollectingKnowledgePerSheepdog> sheepdogsSharedCollectingKnowledge;
	std::vector<expectedDrivingKnowledgePerSheepdog> sheepdogsSharedDrivingKnowledge;
	SheepFlock* sheepFlock;
	SheepDogFlock* sheepDogFlock;

	Terrain terrain;
	Communication communication;
	Atmosphere atmosphere;

	//Vector2f paddockLength;
	//Vector2f paddockWidth;
	//std::vector<std::vector<int>> conflictResolution;
	//std::vector<expectedKnowledgePerSheepdog> sheepdogsSharedKnowledge;
	//float S_t_beta_j;		//						&Speed of beta at time t
	//float S_t_pi_i;		//						&Speed of agent pi at time t


};



	//extern Environment MyEnv;



	