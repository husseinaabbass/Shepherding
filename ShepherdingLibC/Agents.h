//#pragma once
//#ifndef AGENTS_EXPORT
//#define AGENTS_API __declspec(dllexport)
//#else
//#define AGENTS_API __declspec(dllimport)
//#endif
//#ifndef AGENTS_H
//#define AGENTS_H
#pragma once
#ifndef AGENTS_EXPORT
#define AGENTS_API __declspec(dllexport)
#else
#define AGENTS_API __declspec(dllimport)
#endif
//#ifndef AGENTS_H
//#define AGENTS_H

#include<string>
#include <vector>
#include <list>
#include "Behaviors.h"
#include <random>
#include "Traits.h"

//#include "Environment.h"
#include "Vector2.h"
	//class AGENTS_API Globals
	//{
	//	//Omega_t Set of pi agents at time t that have not reached the goal; that is, the remaining agents to complete the mission.
	//	//card_Omega_t  Number of pi agents at time t that have not reached the goal; that is, the remaining agents to complete the mission.//

	//};
	//

struct DetectedSheepRow {
	int sheepID;
	Vector2f sheepLastSeenLocation;
	int sheepLastSeenTimeStep;
	Vector2f sheepCurrentPredictedLocation;
};



	//class AGENTS_API Agent
/// <summary>
/// Class Agent is a superclass that represent any type of agent within the library. SheepAgent and SheepDogAgent are examples of subclass of Agent class.
/// Shared prosperities of Class Agent includes the agent type, the current position, next position, local centre of mass, and the list of behaviours that this agent has.
/// </summary>
class AGENTS_API Agent
{
public:
	/// <summary>
	/// Unique identifier by agent. 
	/// </summary>
	int agentID;
	/// <summary>
	/// The agent type: Examples are: "Sheep" and "SheepDog".
	/// </summary>
	std::string agentType;
	/// <summary>
	/// The current position of the agent, stored in a vector of <x,y> 
	/// </summary>
	Vector2f position_t;
	/// <summary>
	/// The next position of the agent,  stored in a vector of <x,y>
	/// </summary>
	Vector2f position_t1;
	/// <summary>
	/// The local centre of mass of sheep in neighbourhood,  stored in a vector of <x,y>
	/// </summary>
	Vector2f Lambda_t;

	/// <summary>
	/// A list of the agent behaviors
	/// </summary>
	BehaviorList agentBehaviors;

	//Vector2f P_beta_j_d_t;
	//Vector2f P_beta_j_c_t; //P_beta_j_c_t          Position for collection by agent j at time t;

	/// <summary>
	/// The total of the forces that affects this agent to estimate the next location
	/// Total force vector: equivalent to \f$F^t_{\beta_j}\f$ movement vector of the \f$\beta_j\f$ agent at time t, and \f$F^t_{\pi_i}\f$ Force vector, movement vector of the \f$pi_i\f$ agent at time t
	/// </summary>
	Vector2f F_t;
	Vector2f F_obst_t;
	//int toBeCollectedSheepID;
	std::string LoggingSupportingInformation;


	/// <summary>
	/// A constructor to initialize a new instance of the <see cref="Agent"/> class.
	/// </summary>
	Agent();

	std::vector<DetectedSheepRow> get_DetectedSheep();
	void UpdateDetectedSheepLocation(int i, int timestep, Vector2f location);
	void add_DetectedSheep(DetectedSheepRow newRow);

private:
	std::vector<DetectedSheepRow> DetectedSheep;

	Traits agentTraits;




};











//#endif