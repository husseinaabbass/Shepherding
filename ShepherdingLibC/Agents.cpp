#include "Agents.h"
#include "stdafx.h"
#include "Environment.h"
#include "Flock.h"
#include <list>
#include "Vector2.h"
#include <typeinfo>
#include"Utilities.h"
#include <random>
//#include <type_traits>


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
		Vector2f thisBehaviorForce=Vector2f();

		if ((*behaviorIter)->behaviorType=="Jittering")
		{
			thisBehaviorForce= this->F_pi_i_E_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "AttractionBehavior")
		{
			thisBehaviorForce= this->F_pi_i_Lambda_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "CollisionAvoidanceFriends")
		{
			thisBehaviorForce= this->F_pi_i_pi_k_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "CollisionAvoidanceOpponents")
		{
			thisBehaviorForce= this->F_pi_i_beta_j_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "CollisionAvoidanceStaticObstacles")
		{
			thisBehaviorForce = this->F_obst_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "FollowingPreviousDirectionBehavior")
		{
			thisBehaviorForce = (*behaviorIter)->GetForce();   //double check later if we want to store previous direction somewhere
		}


		newForce = newForce + thisBehaviorForce *(*behaviorIter)->Weight;


	}
		newForce = newForce.normalize(); //for Strombom model only
		this->F_t = newForce;
		this->position_t1 = this->position_t + (newForce * S_t_pi_i);

//	this->position_t1 = this->position_t;


}

//SheepAgent::SheepAgent(std::mt19937 generator, int xMin, int xMax, int yMin, int yMax, int ID)
SheepAgent::SheepAgent( float x1, float y1,int ID)

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
	//this->agentBehaviors.push_back(new CollisionAvoidanceFriends());
	this->agentBehaviors.push_back(new Jittering(this));
	this->agentBehaviors.push_back(new AttractionBehavior(this));
	this->agentBehaviors.push_back(new CollisionAvoidanceFriends(this));
	this->agentBehaviors.push_back(new CollisionAvoidanceOpponents(this));
	this->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(this));
	this->agentBehaviors.push_back(new FollowingPreviousDirectionBehavior(this));


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

/// <summary>
/// Calculates the next sheep dog position.
/// </summary>
void SheepDogAgent::calculateSheepDogPositiont1()
{
	//!> Loop over the number of behaviors that this agent has

	//!> Calculate, retrieve, and store the force associated with this behavior

	//!> Retrieve the weight of this behaviour force

	//!> Add the weighted force to the total forces that affect this agent.

	//!> Use the total forces vector, the current speed, and the current position to estimate where the next position of this agent should be.

	//F_beta_j_t.x = 0;
	//F_beta_j_t.y = 0;
	Vector2f newForce = Vector2f();
	std::list<Behavior*>::iterator behaviorIter;
	
	for (behaviorIter = this->agentBehaviors.begin(); behaviorIter != this->agentBehaviors.end(); ++behaviorIter) {
		Behavior*r = (*behaviorIter);
		//TYPE* dynamic_cast<TYPE*> (r);
		//std::string s = typeid((*behaviorIter)).name();

		Vector2f thisBehaviorForce = Vector2f();



		if ((*behaviorIter)->behaviorType == "Jittering")
		{
			thisBehaviorForce=this->F_beta_j_E_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "Driving")
		{
			thisBehaviorForce= this->F_beta_j_d_t = (*behaviorIter)->GetForce();
			float magnitude = (*behaviorIter)->GetMagnitude();
			this->P_beta_j_d_t = position_t + F_beta_j_d_t * magnitude;
			
		}
		else if ((*behaviorIter)->behaviorType == "Collecting")
		{
			thisBehaviorForce= this->F_beta_j_c_t = (*behaviorIter)->GetForce();
			float magnitude= (*behaviorIter)->GetMagnitude();
			this->P_beta_j_c_t = position_t + F_beta_j_c_t * magnitude;
		}
		else if ((*behaviorIter)->behaviorType == "CollisionAvoidanceFriends")
		{
			thisBehaviorForce = this->F_beta_i_beta_k_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "CollisionAvoidanceStaticObstacles")
		{
			thisBehaviorForce = this->F_obst_t = (*behaviorIter)->GetForce();
		}

		newForce = newForce + thisBehaviorForce *(*behaviorIter)->Weight;



	}

	this->F_t = newForce;
//	this->position_t1 = this->position_t;
	Environment& env = Environment::getInstance();
	bool sheepSoClose = false;
	if (env.stallingON)
	{
		int i = 0;
		while (i < env.sheepFlock->size() && !sheepSoClose) {

			if ((this->position_t.dist((*env.sheepFlock)[i]->position_t) < env.stallingDist))
			{
				sheepSoClose = true;
			}
			i++;
		}
	}
	if (sheepSoClose && env.stallingON)
	{
			this->set_S_t_beta_j(0);
	}
	else
	{
		this->set_S_t_beta_j(env.S_t_beta_j);
	}

	this->position_t1 = this->position_t + (newForce * S_t_beta_j);

	//AgentPi.position_t1 = Vector2f();
}

//SheepDogAgent::SheepDogAgent(std::mt19937 generator, int xMin, int xMax, int yMin, int yMax, int ID, float agentSpeed, int mode)
SheepDogAgent::SheepDogAgent(float x1,  float y1, int ID, float agentSpeed, int mode)

{
	//!> Pick a random value between xMin and xMax for this agent x location.

	//!> Pick a random value between yMin and yMax for this agent y location.

	//!> Assign the agent a unique ID.

	//!> Attach to this agent a number of behaviors. 

	//!> Currently, a SheepDogAgent has the following five Behavior (s):

	//!> 1. Jittering, 2. Driving 3. Collecting 4. CollisionAvoidanceFriends 

	//!> Agent modes: 0 refers to operating as single, and 1 operating in multi-sheepdog environment.

	//!> Driving and Collecting is different under single vs multi modes.

	//std::uniform_int_distribution<int> distribution1(xMin, xMax);
	//int x1 = distribution1(generator);
	//std::uniform_int_distribution<int> distribution2(yMin, yMax);
	//int y1 = distribution2(generator);

	/*position_t.x = xMin + rand() % ((xMax + 1) - xMin);
	position_t.y = yMin + rand() % ((yMax + 1) - yMin);*/
	
	position_t.x = x1;
	position_t.y = y1;

	this->agentID = ID;
	this->agentType = "SheepDogAgent";
	this->S_t_beta_j = agentSpeed;

	this->agentBehaviors.push_back(new Jittering(this));
	if (mode == 0)
	{
		this->agentBehaviors.push_back(new Driving(this));
		this->agentBehaviors.push_back(new Collecting(this));
		this->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(this));
	}
	else
	{
		this->agentBehaviors.push_back(new DrivingMultiSheepDogMode(this));
		this->agentBehaviors.push_back(new CollectingMultiSheepDogMode(this));
		this->agentBehaviors.push_back(new CollisionAvoidanceFriends(this));
		this->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(this));
	}
}

//void SheepDogAgent::set_F_beta_j_cd_t(Vector2f F_beta_j_cd_t)
//{
//	this->F_beta_j_cd_t = F_beta_j_cd_t;
//}

void SheepDogAgent::set_F_beta_j_E_t(Vector2f F_beta_j_E_t)
{
	this->F_beta_j_E_t = F_beta_j_E_t;
}

void SheepDogAgent::set_F_beta_j_c_t(Vector2f F_beta_j_c_t)
{
	this->F_beta_j_c_t = F_beta_j_c_t;
}

void SheepDogAgent::set_F_beta_j_d_t(Vector2f F_beta_j_d_t)
{
	this->F_beta_j_d_t = F_beta_j_d_t;
}

void SheepDogAgent::set_P_beta_j_d_t(Vector2f P_beta_j_d_t)
{
	this->P_beta_j_d_t = P_beta_j_d_t;
}

void SheepDogAgent::set_P_beta_j_c_t(Vector2f P_beta_j_c_t)
{
	this->P_beta_j_c_t = P_beta_j_c_t;
}

void SheepDogAgent::set_S_t_beta_j(float S_t_beta_j)
{
	this->S_t_beta_j = S_t_beta_j;
}



//void SheepDogAgent::set_F_beta_j_t(Vector2f F_beta_j_t)
//{
//	this->F_beta_j_t = F_beta_j_t;
//}

//void SheepDogAgent::set_Omega_beta_j_pi(std::list<SheepAgent*> Omega_beta_j_pi)
//{
//	this->Omega_beta_j_pi = Omega_beta_j_pi;
//}


Agent::Agent()
{
}



//void SheepAgent::set_Omega_pi_i_pi(std::list<SheepPtr*> Omega_pi_i_pi)
//{
//	Environment& env = Environment::getInstance();
//
//	std::list<SheepPtr*> neighbourhood = std::list<SheepPtr*>();
//	
//	//this->Omega_pi_i_pi = Omega_pi_i_pi;
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

Vector2f SheepDogAgent::get_F_beta_j_E_t()
{
	return this->F_beta_j_E_t;
}

Vector2f SheepDogAgent::get_F_beta_j_c_t()
{
	return F_beta_j_c_t;
}
Vector2f SheepDogAgent::get_F_beta_i_beta_k_t()
{
	return F_beta_i_beta_k_t;
}

Vector2f SheepDogAgent::get_F_beta_j_d_t()
{
	return F_beta_j_d_t;
}
//
//Vector2f SheepDogAgent::get_F_beta_j_t()
//{
//	return this->F_beta_j_t;
//}
//
//Vector2f SheepDogAgent::get_P_beta_j_t()
//{
//	return this->P_beta_j_t;
//}

Vector2f SheepDogAgent::get_P_beta_j_d_t()
{
	return P_beta_j_d_t;
}

Vector2f SheepDogAgent::get_P_beta_j_c_t()
{
	return P_beta_j_c_t;
}

//Vector2f SheepDogAgent::get_Gamma_beta_j_t()
//{
//	return Gamma_beta_j_t;
//}

float SheepDogAgent::get_S_t_beta_j()
{
	return S_t_beta_j;
}
