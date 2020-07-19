//#include "Agents.h"
#include "stdafx.h"
#include "SheepDogAgent.h"
#include "Environment.h"
//#include "Flock.h"
#include <list>
#include "Vector2.h"
#include <typeinfo>
#include"Utilities.h"
#include <random>




void SheepDogAgent::UpdateDetectedSheepList()
{
	Environment& env = Environment::getInstance();

	for (int i = 0; i < env.sheepFlock->size(); i++) {

		if ((this->position_t.dist((*env.sheepFlock)[i]->position_t) <= env.R_beta_pi))
		{
		
			// if this sheep is within the range, then check first if it has been seen earlier
			// if it has been seen earlier, its last seen location and last seen time will be updated
			//otherwise, add new record.
			
		if (this->get_DetectedSheep().size()==0)
		{
			DetectedSheepRow newRow = DetectedSheepRow();
			newRow.sheepID = (*env.sheepFlock)[i]->agentID;
			newRow.sheepLastSeenLocation = (*env.sheepFlock)[i]->position_t;
			newRow.sheepLastSeenTimeStep = env.currentTime;
			this->add_DetectedSheep(newRow);
		}
		else
		{
			bool found = false;
			int j = 0;
			while (!found && (j < this->get_DetectedSheep().size()))
			{
				if ((*env.sheepFlock)[i]->agentID == this->get_DetectedSheep()[j].sheepID)
				{
					//this->get_DetectedSheep()[j].sheepLastSeenTimeStep = env.currentTime;
					//this->get_DetectedSheep()[j].sheepLastSeenLocation = (*env.sheepFlock)[i]->position_t;
					UpdateDetectedSheepLocation(j, env.currentTime, (*env.sheepFlock)[i]->position_t);

					found = true;

				}
			j++;
		}
			if (!found)
				{
					DetectedSheepRow newRow = DetectedSheepRow();
					newRow.sheepID = (*env.sheepFlock)[i]->agentID;
					newRow.sheepLastSeenLocation = (*env.sheepFlock)[i]->position_t;
					newRow.sheepLastSeenTimeStep = env.currentTime;
					this->add_DetectedSheep(newRow);
				}

			
		}
			
		}
	}


	

}

void SheepDogAgent::UpdateSheepDogAgentLCM()
{
	Vector2f LocalCentreOfMass = Vector2f(); // 1. set the value of the summation variable to zero
	for (int i = 0; i < this->get_DetectedSheep().size(); i++)
	{
		LocalCentreOfMass.x = LocalCentreOfMass.x + this->get_DetectedSheep()[i].sheepLastSeenLocation.x;  // 2a. sum all x locations using a loop
		LocalCentreOfMass.y = LocalCentreOfMass.y + this->get_DetectedSheep()[i].sheepLastSeenLocation.y;  // 2b. sum all y locations using a loop	
	}
	LocalCentreOfMass.x = LocalCentreOfMass.x / this->get_DetectedSheep().size();				// 3. divide by the number of agents in the list.
	LocalCentreOfMass.y = LocalCentreOfMass.y / this->get_DetectedSheep().size();

	this->Lambda_t = LocalCentreOfMass;
}

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

	UpdateDetectedSheepList();
	UpdateSheepDogAgentLCM();

	Vector2f newForce = Vector2f();
	std::list<Behavior*>::iterator behaviorIter;

	for (behaviorIter = this->agentBehaviors.begin(); behaviorIter != this->agentBehaviors.end(); ++behaviorIter) {
		Behavior* r = (*behaviorIter);
		//TYPE* dynamic_cast<TYPE*> (r);
		//std::string s = typeid((*behaviorIter)).name();

		Vector2f thisBehaviorForce = Vector2f();



		if ((*behaviorIter)->behaviorType == "Jittering")
		{
			thisBehaviorForce = this->F_beta_j_E_t = (*behaviorIter)->GetForce();
		}
		else if ((*behaviorIter)->behaviorType == "Driving")
		{
			thisBehaviorForce = this->F_beta_j_d_t = (*behaviorIter)->GetForce();
			float magnitude = (*behaviorIter)->GetMagnitude();
			this->P_beta_j_d_t = position_t + F_beta_j_d_t * magnitude;

		}
		else if ((*behaviorIter)->behaviorType == "Collecting")
		{
			thisBehaviorForce = this->F_beta_j_c_t = (*behaviorIter)->GetForce();
			float magnitude = (*behaviorIter)->GetMagnitude();
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

		else if ((*behaviorIter)->behaviorType == "Covering")
		{
			thisBehaviorForce = this->F_beta_j_cv_t = (*behaviorIter)->GetForce();
			float magnitude = (*behaviorIter)->GetMagnitude();
			if (magnitude > 0)
			{
				this->P_beta_j_cv_t = position_t + F_beta_j_cv_t * magnitude;
			}
		}

		newForce = newForce + thisBehaviorForce * (*behaviorIter)->Weight;



	}

	this->F_t = newForce;
	//	this->position_t1 = this->position_t;
	Environment& env = Environment::getInstance();
	bool sheepSoClose = false;
	if (env.stallingON)
	{
		int i = 0;
		/*while (i < env.sheepFlock->size() && !sheepSoClose) {

			if ((this->position_t.dist((*env.sheepFlock)[i]->position_t) < env.stallingDist))
			{
				sheepSoClose = true;
			}
			i++;
		}*/
		
		while (i < this->get_DetectedSheep().size() && !sheepSoClose) {

			if ((this->position_t.dist(this->get_DetectedSheep()[i].sheepLastSeenLocation) < env.stallingDist))
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

}

//SheepDogAgent::SheepDogAgent(std::mt19937 generator, int xMin, int xMax, int yMin, int yMax, int ID, float agentSpeed, int mode)
SheepDogAgent::SheepDogAgent(float x1, float y1, int ID, float agentSpeed, int mode)

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
	//temporary disable all behaviours to test the covering behavior

	////this->agentBehaviors.push_back(new Jittering(this));
	//if (mode == 0)
	//{
	//	//temporary disable all behaviours to test the covering behavior
	//	//this->agentBehaviors.push_back(new Driving(this));
	//	//this->agentBehaviors.push_back(new Collecting(this));
	//	//this->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(this));
	//	this->agentBehaviors.push_back(new Covering(this));
	//}
	//else
	//{
	//	this->agentBehaviors.push_back(new DrivingMultiSheepDogMode(this));
	//	this->agentBehaviors.push_back(new CollectingMultiSheepDogMode(this));
	//	this->agentBehaviors.push_back(new CollisionAvoidanceFriends(this));
	//	this->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(this));
	//}
}


void SheepDogAgent::set_F_beta_j_E_t(Vector2f F_beta_j_E_t)
{
	this->F_beta_j_E_t = F_beta_j_E_t;
}

void SheepDogAgent::set_F_beta_j_c_t(Vector2f F_beta_j_c_t)
{
	this->F_beta_j_c_t = F_beta_j_c_t;
}

void SheepDogAgent::set_F_beta_j_cv_t(Vector2f F_beta_j_cv_t)
{
	this->F_beta_j_cv_t = F_beta_j_cv_t;
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
void SheepDogAgent::set_P_beta_j_cv_t(Vector2f P_beta_j_cv_t)
{
	this->P_beta_j_cv_t = P_beta_j_cv_t;
}

void SheepDogAgent::set_S_t_beta_j(float S_t_beta_j)
{
	this->S_t_beta_j = S_t_beta_j;
}



Vector2f SheepDogAgent::get_F_beta_j_E_t()
{
	return this->F_beta_j_E_t;
}

Vector2f SheepDogAgent::get_F_beta_j_c_t()
{
	return F_beta_j_c_t;
}

Vector2f SheepDogAgent::get_F_beta_j_cv_t()
{
	return F_beta_j_cv_t;
}

Vector2f SheepDogAgent::get_F_beta_i_beta_k_t()
{
	return F_beta_i_beta_k_t;
}

Vector2f SheepDogAgent::get_F_beta_j_d_t()
{
	return F_beta_j_d_t;
}

Vector2f SheepDogAgent::get_P_beta_j_d_t()
{
	return P_beta_j_d_t;
}

Vector2f SheepDogAgent::get_P_beta_j_c_t()
{
	return P_beta_j_c_t;
}

Vector2f SheepDogAgent::get_P_beta_j_cv_t()
{
	return P_beta_j_cv_t;
}

//std::vector<DetectedSheepRow> SheepDogAgent::get_DetectedSheep()
//{
	//return DetectedSheep;
//}


float SheepDogAgent::get_S_t_beta_j()
{
	return S_t_beta_j;
}
