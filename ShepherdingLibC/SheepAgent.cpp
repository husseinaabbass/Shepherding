#include "stdafx.h"
#include "SheepAgent.h"
#include "Environment.h"

//#include "Flock.h"
#include <list>
#include "Vector2.h"
#include <typeinfo>
#include"Utilities.h"
#include <random>


/// <summary>
/// Calculates the sheep positiont1.
/// </summary>
void SheepAgent::calculateSheepPositiont1()
{
	//!> Loop over the number of behaviors that this agent has

	//!> Calculate, retrieve, and store the force associated with this behavior

	//!> Retrieve the weight of this behaviour force

	//!> Add the weighted force to the total forces that affect this agent.

	//!> Use the total forces vector, the current speed, and the current position to estimate where the next position of this agent should be.

	std::list<Behavior*>::iterator behaviorIter;
	//F_pi_i_t.x = 0;
	//F_pi_i_t.y = 0;
	Vector2f newForce = Vector2f();
	for (behaviorIter = this->agentBehaviors.begin(); behaviorIter != this->agentBehaviors.end(); ++behaviorIter)
	{
		Vector2f thisBehaviorForce = Vector2f();

		if ((*behaviorIter)->behaviorType == "Jittering")
		{
			thisBehaviorForce = this->F_pi_i_E_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "AttractionBehavior")
		{
			thisBehaviorForce = this->F_pi_i_Lambda_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "CollisionAvoidanceFriends")
		{
			thisBehaviorForce = this->F_pi_i_pi_k_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "CollisionAvoidanceOpponents")
		{
			thisBehaviorForce = this->F_pi_i_beta_j_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "CollisionAvoidanceStaticObstacles")
		{
			thisBehaviorForce = this->F_obst_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "FollowingPreviousDirectionBehavior")
		{
			thisBehaviorForce = (*behaviorIter)->GetForce();   //double check later if we want to store previous direction somewhere
		}


		newForce = newForce + thisBehaviorForce * (*behaviorIter)->Weight;


	}
	newForce = newForce.normalize(); //for Strombom model only
	this->F_t = newForce;
	this->position_t1 = this->position_t + (newForce * S_t_pi_i);

	//	this->position_t1 = this->position_t;


}

//SheepAgent::SheepAgent(std::mt19937 generator, int xMin, int xMax, int yMin, int yMax, int ID)
SheepAgent::SheepAgent(float x1, float y1, int ID)

{
	//!> Pick a random value between xMin and xMax for this agent x location.

	//!> Pick a random value between yMin and yMax for this agent y location.

	//!> Specify the agentType

	//!> Assign the agent a unique ID.

	//!> Attach to this agent a number of behaviors.

	//!> Currently, a SheepAgent has the following five Behavior (s):

	//!> 1. Jittering, 2. AttractionBehavior 3. CollisionAvoidanceFriends 4. CollisionAvoidanceOpponents 5. FollowingPreviousDirectionBehavior  



	//position_t.x = xMin + rand() % ((xMax + 1) - xMin); //returned only random integer for x locations between xMin and Xmax
	//position_t.y = yMin + rand() % ((yMax + 1) - yMin);

	//position_t.x = xMin + (((float)rand()) / (float)RAND_MAX) * (xMax - xMin); //returned only random integer for x locations between xMin and Xmax
	//position_t.y = yMin + (((float)rand()) / (float)RAND_MAX) * (yMax - yMin);
	//std::uniform_int_distribution<int> distribution1(xMin, xMax);
	//int x1 = distribution1(generator);
	//std::uniform_int_distribution<int> distribution2(yMin, yMax);
	//int y1 = distribution2(generator);
	position_t.x = x1;
	position_t.y = y1;


	this->agentType = "SheepAgent";
	this->agentID = ID;
	//this->agentBehaviors.push_back(new Jittering(this));
	//this->agentBehaviors.push_back(new AttractionBehavior(this));
	//this->agentBehaviors.push_back(new CollisionAvoidanceFriends(this));
	//this->agentBehaviors.push_back(new CollisionAvoidanceOpponents(this));
	//this->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(this));
	//this->agentBehaviors.push_back(new FollowingPreviousDirectionBehavior(this));


	this->F_t = Vector2f();

}

void SheepAgent::set_F_pi_i_beta_j_t(Vector2f F_pi_i_beta_j_t)
{
	this->F_pi_i_beta_j_t = F_pi_i_beta_j_t;
}

void SheepAgent::set_F_pi_i_pi_k_t(Vector2f F_pi_i_pi_k_t)
{
	this->F_pi_i_pi_k_t = F_pi_i_pi_k_t;
}

void SheepAgent::set_F_pi_i_Lambda_t(Vector2f F_pi_i_Lambda_t)
{
	this->F_pi_i_Lambda_t = F_pi_i_Lambda_t;
}

void SheepAgent::set_F_pi_i_E_t(Vector2f F_pi_i_E_t)
{
	this->F_pi_i_E_t = F_pi_i_E_t;
}

//void SheepAgent::updateNeighbourhood(SheepAgent * sheep)
//{
//	
//	Environment& env = Environment::getInstance();
//	std::list<SheepAgent*>::iterator sheepIter;
//	std::list<SheepAgent*> neighbourhoodList;
//	for (sheepIter = env.flock->sheepList.begin(); sheepIter != env.flock->sheepList.end(); ++sheepIter) {
//
//		if ((sheep->agentID != (*sheepIter)->agentID))
//		{
//			SheepAgent* sh2 = (*sheepIter);
//			SheepPtr* a = sh2;
//			neighborhoodList.push_back(sh2);
//		}
//
//	}
//	this->Omega_pi_i_pi = neighbourhoodList;
//	
//}




void SheepAgent::set_S_t_pi_i(float S_t_pi_i)
{
	this->S_t_pi_i = S_t_pi_i;
}

Vector2f SheepAgent::get_F_pi_i_beta_j_t()
{
	return this->F_pi_i_beta_j_t;
}

Vector2f SheepAgent::get_F_pi_i_pi_k_t()
{
	return this->F_pi_i_pi_k_t;
}

Vector2f SheepAgent::get_F_pi_i_Lambda_t()
{
	return this->F_pi_i_Lambda_t;
}

Vector2f SheepAgent::get_F_pi_i_E_t()
{
	return this->F_pi_i_E_t;
}


float SheepAgent::get_S_t_pi_i()
{
	return this->S_t_pi_i;
}

