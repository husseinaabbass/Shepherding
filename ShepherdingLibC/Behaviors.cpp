#include "stdafx.h"
#include "Behaviors.h"
#include "Environment.h"
#include "Agents.h"
#include "SheepDogAgent.h"

#include "Flock.h"
//#include <typeinfo>
#include <algorithm>
#include <numeric>      // std::iota
#include <iostream>
#include "Utilities.h"
#include <math.h>       /* pow */
#include <tuple>

Environment& env = Environment::getInstance();


Vector2f AttractionBehavior::GetForce()
{
	Vector2f AttractionForce = Vector2f();
	SheepList neighborhoodSheep;
	if (env.SheepNeignborhoodSelection==1)
	neighborhoodSheep = SenseSheepInNeighborhoodBasedOnDist(this->agent, env,env.Rs_pi_pi); 	// identify sheep within neighborhod
	else if (env.SheepNeignborhoodSelection == 0)
		neighborhoodSheep = SenseSheepInNeighborhoodBasedOnNumber(this->agent, env.card_Omega_pi_pi, env); 	// identify sheep within neighborhod
	
	//calculate the cohesion force

	if (neighborhoodSheep.size() != 0)
	{
		//calculate the LCM of those sheep
		Vector2f neighborhood_LCM = calculateLocalCentreOfMass(neighborhoodSheep); //Lambda_t // summing the positions and divide the results per the list size. The list doesn't include the sheep location itself.	
		this->agent->Lambda_t = neighborhood_LCM;
		this->magnitude = neighborhood_LCM.dist(this->agent->position_t);
		if (this->magnitude > 0)
		{
		
			AttractionForce = (neighborhood_LCM - this->agent->position_t) / magnitude;
		}
		//AttractionForce.normalize();
	}
	return AttractionForce;

}

float AttractionBehavior::GetMagnitude()
{

	return this->magnitude;
}

AttractionBehavior::AttractionBehavior(Agent * agent)
{
	this->Weight = env.W_pi_Lambda;
	this->agent = agent;
	this->behaviorType = "AttractionBehavior";
}


Vector2f Covering::GetForce()
{
		Vector2f coveringForce = Vector2f();


		Vector2f coveringPosition = GetNextCoveringPosition();
		
		//this->agent->P_beta_j_d_t = drivingPosition;
		if ((coveringPosition.x == 0) && (coveringPosition.y == 0)) // Not Covering, coveringForce set to Zero.. Needs to be updated based on a decision not value
		{
			this->magnitude = 0;
		}
		else
		{
			coveringForce = (coveringPosition - this->agent->position_t) / coveringPosition.dist(this->agent->position_t);
			this->magnitude = coveringPosition.dist(this->agent->position_t);

		}





		return coveringForce;
}

float Covering::GetMagnitude()
{
	return 0.0f;
}

Covering::Covering(Agent* agent)
{
	this->Weight = 1;
	this->agent = agent;
	this->behaviorType = "Covering";
}

Vector2f Covering::GetNextCoveringPosition()
{
	Vector2f coveringPosition = Vector2f();
	
	SheepList sheepOutOfFlock = SenseSheepOutOfFlock(this->agent, env);

	if (env.openCoveringTask)
	{
		if (this->agent->position_t.dist(env.coveringPoints.front()) < 1) /// if the sheepdog is too close to the nextPoint on the list, mark it as visited and move to the next point

		{
			env.coveringPoints.pop_front();
		}

		if (env.coveringPoints.empty())
		{
			env.openCoveringTask = false;
		}
		else
		{
			coveringPosition = env.coveringPoints.front();
		}
	}
	return coveringPosition;
}


Vector2f CollisionAvoidanceFriends::GetForce()
{
	Vector2f collisionAvoidanceForce = Vector2f();
	if (this->agent->agentType == "SheepAgent")
	{
		if (env.ForceRegulated == 1)
		{


			int potentioalSheepCollisionCounter = 0; //This variable is calculated in advance to be used by regulation function M2 function (Number of sheeps that within collision range)
			for (int i = 0; i < env.sheepFlock->size(); i++) {

				if ((agent->position_t.dist((*env.sheepFlock)[i]->position_t) < env.Ra_pi_pi) && (agent->agentID != (*env.sheepFlock)[i]->agentID)) //if sheep within collision range excluding the agent itself.
				{
					potentioalSheepCollisionCounter++;
				}
			}

			for (int i = 0; i < env.sheepFlock->size(); i++) {

				if ((agent->position_t.dist((*env.sheepFlock)[i]->position_t) < env.Ra_pi_pi) && (agent->agentID != (*env.sheepFlock)[i]->agentID))//if sheep within collision range excluding the agent itself.
				{
					float regulation_factor = calc_regulated_force_magnitudeM2(this->agent->position_t.dist((*env.sheepFlock)[i]->position_t), 0, env.Ra_pi_pi, potentioalSheepCollisionCounter, env.ModulationDecayFactor); //calculate the regulation factor using M2
					collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.sheepFlock)[i]->position_t) / this->agent->position_t.dist((*env.sheepFlock)[i]->position_t)*regulation_factor); // update the collision avoidance force to cater for avoiding this single sheep
				}


			}

		}
		else if (env.ForceRegulated == 0)
		{
			for (int i = 0; i < env.sheepFlock->size(); i++) {

				if ((agent->position_t.dist((*env.sheepFlock)[i]->position_t) < env.Ra_pi_pi) && (agent->agentID != (*env.sheepFlock)[i]->agentID))
				{
					collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.sheepFlock)[i]->position_t) / this->agent->position_t.dist((*env.sheepFlock)[i]->position_t)); // update the collision avoidance force to cater for avoiding this single sheep
				}
			}
		}
	}


		
	
	else if (this->agent->agentType == "SheepDogAgent")
		{
			if (env.ForceRegulated == 1)
			{
				int potentioalSheepDogCollisionCounter = 0;
				for (int i = 0; i < env.sheepDogFlock->size(); i++) {

					if ((agent->position_t.dist((*env.sheepDogFlock)[i]->position_t) < env.R_beta_beta) && (agent->agentID != (*env.sheepDogFlock)[i]->agentID))
					{
						potentioalSheepDogCollisionCounter++;
					}
				}

				for (int i = 0; i < env.sheepDogFlock->size(); i++) {

					if ((agent->position_t.dist((*env.sheepDogFlock)[i]->position_t) < env.R_beta_beta) && (agent->agentID != (*env.sheepDogFlock)[i]->agentID))
					{
						float regulation_factor = calc_regulated_force_magnitudeM2(this->agent->position_t.dist((*env.sheepDogFlock)[i]->position_t), 0, env.R_beta_beta, potentioalSheepDogCollisionCounter, env.ModulationDecayFactor);
						collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.sheepDogFlock)[i]->position_t) / this->agent->position_t.dist((*env.sheepDogFlock)[i]->position_t))*regulation_factor;
					}
				}
			}
			else if (env.ForceRegulated == 0)
			{
				for (int i = 0; i < env.sheepDogFlock->size(); i++) {

					if ((agent->position_t.dist((*env.sheepDogFlock)[i]->position_t) < env.R_beta_beta) && (agent->agentID != (*env.sheepDogFlock)[i]->agentID))
					{
						collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.sheepDogFlock)[i]->position_t) / this->agent->position_t.dist((*env.sheepDogFlock)[i]->position_t));
					}
				}

			}


		}

	magnitude = collisionAvoidanceForce.length();

	return collisionAvoidanceForce;
}

float CollisionAvoidanceFriends::GetMagnitude()
{
	return this->magnitude;
}

CollisionAvoidanceFriends::CollisionAvoidanceFriends(Agent * agent)
{
	//this->Weight = env.W_pi_pi;
	this->agent = agent;
	if (this->agent->agentType == "SheepAgent")
	{
		this->Weight = env.W_pi_pi;
	}
	else if (this->agent->agentType == "SheepDogAgent")
	{
		this->Weight = env.W_beta_beta;
	}

	this->behaviorType = "CollisionAvoidanceFriends";
}


Vector2f Jittering::GetForce()
{

	Vector2f jittering_force = Vector2f();

	jittering_force.x = (float)((rand() / double(RAND_MAX) * 2 - 1)* (float)env.eta);
	jittering_force.y = (float)((rand() / double(RAND_MAX) * 2 - 1)* (float)env.eta);

	return jittering_force;

}

Jittering::Jittering(Agent* agent )
{
	this->agent = agent;
	//this->Weight = env.W_e_pi_i;

	this->behaviorType = "Jittering";
	if (this->agent->agentType == "SheepAgent")
	{
		this->Weight = env.W_e_pi_i;
	}
	else if (this->agent->agentType == "SheepDogAgent")
	{
		this->Weight = env.W_e_beta_j;
	}


}

Vector2f Behavior::GetForce()
{
	return Vector2f();
}

float Behavior::GetMagnitude()
{
	return this->magnitude;
}






Vector2f RepulsionBehaviorM1::GetForce()
{
	return Vector2f();
}

Vector2f RepulsionBehaviorM2::GetForce()
{
	return Vector2f();
}

Vector2f CollisionAvoidanceOthers::GetForce()
{
	return Vector2f();
}

Vector2f CollisionAvoidanceOpponents::GetForce()
{	

	Vector2f collisionAvoidanceForce = Vector2f();   //Initialize this force to zero.
	if (this->agent->agentType == "SheepAgent")
	{

		for (int i = 0; i < env.sheepDogFlock->size(); i++) {
			float temp = agent->position_t.dist((*env.sheepDogFlock)[i]->position_t) ;
			if ((agent->position_t.dist((*env.sheepDogFlock)[i]->position_t) < env.R_pi_beta)) //for each sheepDog within R_pi_beta distance except self.
			{
				/*float regulated_factor = calc_regulated_force_magnitudeM1(this->agent->position_t.dist((*env.sheepDogFlock)[i]->position_t), 0, 20);*/
				if (env.ForceRegulated == 1)
				{
					float regulated_factor = (env.S_t_beta_j / 1)*calc_regulated_force_magnitudeM1(this->agent->position_t.dist((*env.sheepDogFlock)[i]->position_t), (env.R2), (env.R2 + env.R3), env.ModulationDecayFactor); //1 to be replace by sheepSpeed

					collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.sheepDogFlock)[i]->position_t) / this->agent->position_t.dist((*env.sheepDogFlock)[i]->position_t))*regulated_factor; //add a force opposite to that agent direction
				}
				else if (env.ForceRegulated == 0)
				{
				collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.sheepDogFlock)[i]->position_t) / this->agent->position_t.dist((*env.sheepDogFlock)[i]->position_t));
				//	collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.sheepDogFlock)[i]->position_t)); //based on strombom paper

					
				}

		

			}

		}


	}


	magnitude = collisionAvoidanceForce.length();
	
	return collisionAvoidanceForce;

}

float CollisionAvoidanceOpponents::GetMagnitude()
{
	return this->magnitude;
}

CollisionAvoidanceOpponents::CollisionAvoidanceOpponents(Agent * agent)
{
	this->Weight = env.W_pi_beta;
	this->agent = agent;
	this->behaviorType = "CollisionAvoidanceOpponents";
}

Vector2f CollisionAvoidanceStaticObstacles::GetForce()
{
	Vector2f collisionAvoidanceForce = Vector2f();   //Initialize this force to zero.
	
		for (int i = 0; i < env.terrain.staticObstacles->size(); i++) {
			float distance = agent->position_t.dist((*env.terrain.staticObstacles)[i]->position_t);
			if (distance < 5) //for each obstacle within R_pi_beta distance except self.
			{
				/*float regulated_factor = calc_regulated_force_magnitudeM1(this->agent->position_t.dist((*env.sheepDogFlock)[i]->position_t), 0, 20);*/
				if (env.ForceRegulated == 1)
				{
					float speed=1;
					/*if (this->agent->agentType == "Sheep")
					{
						speed = 1;
					}*/
					if (this->agent->agentType == "SheepDog")
					{
						speed = env.S_t_beta_j;
					}
					float regulated_factor = (speed) * calc_regulated_force_magnitudeM1(distance, 0, 5, env.ModulationDecayFactor);

					collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.terrain.staticObstacles)[i]->position_t) / distance * regulated_factor); //add a force opposite to that obstacle direction
				}
				else if (env.ForceRegulated == 0)
				{
					collisionAvoidanceForce = collisionAvoidanceForce + ((this->agent->position_t - (*env.terrain.staticObstacles)[i]->position_t) / distance);


				}



			}

	


	}


	magnitude = collisionAvoidanceForce.length();

	return collisionAvoidanceForce;

}

float CollisionAvoidanceStaticObstacles::GetMagnitude()
{
	return this->magnitude;
}

CollisionAvoidanceStaticObstacles::CollisionAvoidanceStaticObstacles(Agent* agent)
{
	this->agent = agent;
	//this->Weight = 3;
	/*if (this->agent->agentType == "SheepAgent")
	{
		this->Weight = 3;
	}
	else if (this->agent->agentType == "SheepDogAgent")
	{
		this->Weight = 1;
	}*/

	if (this->agent->agentType == "SheepAgent")
	{
		this->Weight = 3;
	}
	else if (this->agent->agentType == "SheepDogAgent")
	{
		this->Weight = 2;
	}


	
	this->behaviorType = "CollisionAvoidanceStaticObstacles";
}

Vector2f CollisionAvoidanceDynamicObstacles::GetForce()
{
	return Vector2f();
}

Driving::Driving(Agent * agent)
{
	this->Weight = 1;
	this->agent = agent;
	this->behaviorType = "Driving";
}

Vector2f Driving::GetForce()
{
	Vector2f DrivingForce = Vector2f();

	Vector2f drivingPosition = GetDrivingPosition();
	//this->agent->P_beta_j_d_t = drivingPosition;
	if ((drivingPosition.x == 0) && (drivingPosition.y == 0)) // Not Driving, DrivingForce set to Zero.. Needs to be updated based on a decision not value
	{
		this->magnitude = 0;
	}
	else
	{
	DrivingForce = (drivingPosition - this->agent->position_t) / drivingPosition.dist(this->agent->position_t);
	this->magnitude = drivingPosition.dist(this->agent->position_t);

	}


	return DrivingForce;
}

Vector2f Driving::GetDrivingPosition()
{
	Vector2f drivingPosition = Vector2f();
	// 1. Each shepherd needs to check if the sheep in their neighbourhood are grouped or not.
	// 2. If the sheep are clustered, then calculate the driving position.

//	SheepList sheepOutOfFlock = SenseSheepOutOfFlock(this->agent, env);
	std::vector<DetectedSheepRow>  sheepOutOfFlock = SenseSheepOutOfFlockUsingLocalInformation(this->agent->Lambda_t, this->agent->get_DetectedSheep(), env);


	if (sheepOutOfFlock.size() == 0) //if this list is empty, then the sheep are clustered and ready to be driven.
	{
		//drivingPosition = this->agent->Lambda_t + ((this->agent->Lambda_t - env.PG) / this->agent->Lambda_t.dist(env.PG))* env.fN;

		//SheepList neighborhoodSheep = SenseSheepInNeighborhoodBasedOnNumber(agent, env.card_Omega_beta_pi, env); 	// identify sheep within neighborhod

	  //	std::vector<int> y = RankSheepBasedOnDistTo(this->agent->Lambda_t, neighborhoodSheep);

		//Vector2f furthestSheepLoc = neighborhoodSheep[y[y.size() - 1]]->position_t;

		this->agent->LoggingSupportingInformation = "SheepDog Role:C";

		//env.R1 = min(env.fN, furthestSheepLoc.dist(this->agent->Lambda_t));
		if (env.DrivingPositionEq == 1)
		{
			env.R1 = env.fN; //if the sheep are clustered than max(furthestSheep, fn) will always return fn;
			drivingPosition = this->agent->Lambda_t - ((env.PG - this->agent->Lambda_t) / env.PG.dist(this->agent->Lambda_t))* (env.R1 + env.R2);
		}
		else if (env.DrivingPositionEq == 0)
		{
			drivingPosition = this->agent->Lambda_t - ((env.PG - this->agent->Lambda_t) / env.PG.dist(this->agent->Lambda_t))* (env.Ra_pi_pi*sqrt(env.N)); //ra*sqrt(N) is Strombom equation for driving location
			//drivingPosition = this->agent->Lambda_t - ((env.PG - this->agent->Lambda_t) / env.PG.dist(this->agent->Lambda_t))* env.fN; //ra*power(N,2/3) 
		}
	}
	// before returning the expected driving position.
	return drivingPosition;
}

Collecting::Collecting(Agent * agent)
{
	this->Weight = 1;
	this->agent = agent;
	this->behaviorType = "Collecting";
}


Vector2f Collecting::GetForce()
{
	Vector2f CollectingForce = Vector2f();

	Vector2f CollectingPosition = GetCollectingPosition();
	//this->agent->P_beta_j_c_t = CollectingPosition;

	if( (CollectingPosition.x == 0) && (CollectingPosition.y == 0)) // Not Collecting, CollectingForce set to Zero.. Needs to be updated based on a decision not value
	{
		this->magnitude = 0;
	}
	else
	{
		CollectingForce = (CollectingPosition - this->agent->position_t) / CollectingPosition.dist(this->agent->position_t);
		//CollectingForce = (this->agent->position_t- CollectingPosition) / this->agent->position_t.dist(CollectingPosition);
		this->magnitude = CollectingPosition.dist(this->agent->position_t);

	}
//SheepDogAgent* cs = dynamic_cast<SheepDogAgent *>(agent);
return CollectingForce;


}
//
//Vector2f Collecting::GetCollectingPosition()
//{
//	Vector2f CollectingPosition = Vector2f();
//	// 1. Each shepherd needs to check if the sheep in their neighbourhood are grouped or not.
//	// 2. If the sheep are clustered, then calculate the driving position.
//
//	SheepList sheepOutOfFlock = SenseSheepOutOfFlock(this->agent, env);
//
//	if (sheepOutOfFlock.size() > 0) //if this list is not empty, then find the furthest sheep from the group.
//	{
//		std::vector<int> y = RankSheepBasedOnDistTo(this->agent->Lambda_t, sheepOutOfFlock);
//
//		Vector2f furthestSheepLoc = sheepOutOfFlock[y[y.size() - 1]]->position_t;
//
//		int SheeptoCollectID = sheepOutOfFlock[y[y.size() - 1]]->agentID;
//		this->agent->LoggingSupportingInformation = "toBeCollectedSheepID:" + std::to_string(SheeptoCollectID);
//
//		if (env.CollectingPositionEq == 1)
//		{
//			CollectingPosition = furthestSheepLoc - ((this->agent->Lambda_t - furthestSheepLoc) / this->agent->Lambda_t.dist(furthestSheepLoc)) * env.R2;
//		}
//		else if (env.CollectingPositionEq == 0)
//		{
//			CollectingPosition = furthestSheepLoc - ((this->agent->Lambda_t - furthestSheepLoc) / this->agent->Lambda_t.dist(furthestSheepLoc)) * env.Ra_pi_pi;
//		}
//	}
//
//
//	return CollectingPosition;
//
//}

Vector2f Collecting::GetCollectingPosition()
{
	Vector2f CollectingPosition = Vector2f();
	// 1. Each shepherd needs to check if the sheep in their neighbourhood are grouped or not.
	// 2. If the sheep are clustered, then calculate the driving position.

	Environment& env = Environment::getInstance();
	std::vector<DetectedSheepRow> currentDetectedSheepList = this->agent->get_DetectedSheep();

	std::vector<DetectedSheepRow>  sheepOutOfFlock = SenseSheepOutOfFlockUsingLocalInformation(this->agent->Lambda_t , currentDetectedSheepList, env);

	if (sheepOutOfFlock.size() > 0) //if this list is not empty, then find the furthest sheep from the group.
	{
		std::vector<int> y = RankSheepBasedOnDistTo(this->agent->Lambda_t, sheepOutOfFlock);


		Vector2f furthestSheepLoc = sheepOutOfFlock[y[y.size() - 1]].sheepLastSeenLocation;

		int SheeptoCollectID = sheepOutOfFlock[y[y.size() - 1]].sheepID;
		this->agent->LoggingSupportingInformation = "toBeCollectedSheepID:" + std::to_string(SheeptoCollectID);

		if (env.CollectingPositionEq == 1)
		{
			CollectingPosition = furthestSheepLoc - ((this->agent->Lambda_t - furthestSheepLoc) / this->agent->Lambda_t.dist(furthestSheepLoc)) * env.R2;
		}
		else if (env.CollectingPositionEq == 0)
		{
			CollectingPosition = furthestSheepLoc - ((this->agent->Lambda_t - furthestSheepLoc) / this->agent->Lambda_t.dist(furthestSheepLoc)) * env.Ra_pi_pi;
		}
	}


	return CollectingPosition;

}


Vector2f FollowingPreviousDirectionBehavior::GetForce()
{
	Vector2f followingPreviousDirectionBehavior = Vector2f();
	followingPreviousDirectionBehavior.x = this->agent->F_t.x;
	followingPreviousDirectionBehavior.y = this->agent->F_t.y;
	return followingPreviousDirectionBehavior;
}

FollowingPreviousDirectionBehavior::FollowingPreviousDirectionBehavior(Agent* agent)
{
	this->Weight = env.W_pi_upsilon;
	this->agent = agent;
	this->behaviorType = "FollowingPreviousDirectionBehavior";
}

DrivingMultiSheepDogMode::DrivingMultiSheepDogMode(Agent* agent)
{
	this->Weight = 1;
	this->agent = agent;
	this->behaviorType = "Driving";
}

Vector2f DrivingMultiSheepDogMode::GetForce()
{
	Vector2f DrivingForce = Vector2f();

	Vector2f drivingPosition = GetDrivingPosition();
	//this->agent->P_beta_j_d_t = drivingPosition;
	if ((drivingPosition.x == 0) && (drivingPosition.y == 0)) // Not Driving, DrivingForce set to Zero.. Needs to be updated based on a decision not value
	{
		this->magnitude = 0;
	}
	else
	{
		DrivingForce = (drivingPosition - this->agent->position_t) / drivingPosition.dist(this->agent->position_t);
		this->magnitude = drivingPosition.dist(this->agent->position_t);

	}


	return DrivingForce;
}

Vector2f DrivingMultiSheepDogMode::GetDrivingPosition()
{
	Vector2f drivingPosition = Vector2f();

	Environment& env = Environment::getInstance();
	//Find my role. Am I driving or collecting. For a centralized decision, look up the Roster table.
	//this->agent->agentID this is the agent ID. we need to access the corresponding record in the sheepdogsSharedKnowledge, which will be (agentID-1) as the vector starts from zero, and the IDs starts from one.
	std::string thisSheepDogRole = (env.SheepDogRoster)[this->agent->agentID - 1].dogAssignedTask;



	if (thisSheepDogRole == "Driving")
	{
		//if driving find my row in the sheepdogsSharedDrivingKnowledge
		int thisAgentInd = 0;
		for (int i = 0; i < env.sheepdogsSharedDrivingKnowledge.size(); i++)
		{
			if ((env.sheepdogsSharedDrivingKnowledge)[i].dogID == this->agent->agentID )
			{
			thisAgentInd = i;
}
		}
		Vector2f GCM = ((env.sheepdogsSharedDrivingKnowledge)[thisAgentInd]).GCM; //Let me know the GCM
		this->agent->Lambda_t = GCM;
		this->agent->LoggingSupportingInformation = "SheepDog Role:" + ((env.sheepdogsSharedDrivingKnowledge)[thisAgentInd]).dogName;
		//Is this the central sheepDog?
		if (((env.sheepdogsSharedDrivingKnowledge)[thisAgentInd]).dogName == "C")
		{
			if (env.DrivingPositionEq == 1)
			{
				env.R1 = env.fN; //if the sheep are clustered than max(furthestSheep, fn) will always return fn;
				drivingPosition = GCM - ((env.PG - GCM) / env.PG.dist(GCM)) * (env.R1 + env.R2);
			}
			else if (env.DrivingPositionEq == 0)
			{
				drivingPosition = GCM - (env.PG - GCM) / env.PG.dist(GCM) * (env.Ra_pi_pi * sqrt(env.N)); //ra*sqrt(N) is Strombom equation for driving location
				//drivingPosition = this->agent->Lambda_t - ((env.PG - this->agent->Lambda_t) / env.PG.dist(this->agent->Lambda_t))* env.fN; //ra*power(N,2/3) 
			}
		}
		else
		{
			int myRefDogID = ((env.sheepdogsSharedDrivingKnowledge)[thisAgentInd]).RefDogID; //Let me know my reference dog
			//find this refDog Index in the sheepdogsSharedDrivingKnowledge
			int myRefDogIndx = 0;
			bool found = false;
			int i = 0;
			while (!found)
			{
				if ((env.sheepdogsSharedDrivingKnowledge)[i].dogID == myRefDogID)
				{
					myRefDogIndx = i;
					found = true;

				}
				i++;
			}
			Vector2f myRefDogLoc = ((env.sheepdogsSharedDrivingKnowledge)[myRefDogIndx]).dogCurrentLocation; //Use the previous information to access its location

			//Now I need to position my self relevant to this dog.
			float RefSheepDog2GCM_Angle = atan2(myRefDogLoc.y - GCM.y, myRefDogLoc.x - GCM.x);
			float RefSheepDog2Dist = myRefDogLoc.dist(GCM);
			std::string Direction = ((env.sheepdogsSharedDrivingKnowledge)[thisAgentInd]).dogLocationRelevant2RefDog;
			float pi = 22 / (float)7;
			float dist_theta = 0.5 * pi / (float)env.M;

			if (Direction == "L")
			{
				float ThisSheepDog2GCM_Angle = RefSheepDog2GCM_Angle - dist_theta;
				drivingPosition.x = RefSheepDog2Dist * cos(ThisSheepDog2GCM_Angle) + GCM.x;
				drivingPosition.y = RefSheepDog2Dist * sin(ThisSheepDog2GCM_Angle) + GCM.y;
			}
			else if (Direction == "R")
			{
				float ThisSheepDog2GCM_Angle = RefSheepDog2GCM_Angle + dist_theta;
				drivingPosition.x = RefSheepDog2Dist * cos(ThisSheepDog2GCM_Angle) + GCM.x;
				drivingPosition.y = RefSheepDog2Dist * sin(ThisSheepDog2GCM_Angle) + GCM.y;
			}
		}


	}
	else //Collecting
	{
		//Nothing here, go to collecting behavior
	}

	//int CurrentFurthestSheep = ((env.sheepdogsSharedKnowledge)[this->agent->agentID - 1]).furthestSheepID;
	//bool IamCollecting = false;
	//Vector2f furthestSheepLoc = Vector2f();
	//if (CurrentFurthestSheep >0) // if not -1, check if it is assigned to this agent
	//{
	//	std::vector<int> thisAgentAssignedSheep = env.conflictResolution[this->agent->agentID - 1];
	//	for (int i = 0; i < thisAgentAssignedSheep.size(); i++) {

	//		{
	//			if (thisAgentAssignedSheep[i] == CurrentFurthestSheep)
	//			{
	//				IamCollecting = true;
	//			}

	//		}
	//	}
	//}

	//if (!IamCollecting) // Driving OR following a collecting agent, then set the driving position relevant to my RefDog.
	//{
	//	Vector2f GCM = ((env.sheepdogsSharedKnowledge)[this->agent->agentID - 1]).GCM; //Let me know the GCM

	//	//Is this the central sheepDog?
	//	if (((env.sheepdogsSharedKnowledge)[this->agent->agentID - 1]).dogName == "C")
	//	{
	//		if (env.DrivingPositionEq == 1)
	//		{
	//			env.R1 = env.fN; //if the sheep are clustered than max(furthestSheep, fn) will always return fn;
	//			drivingPosition = GCM - ((env.PG - GCM) / env.PG.dist(GCM)) * (env.R1 + env.R2);
	//		}
	//		else if (env.DrivingPositionEq == 0)
	//		{
	//			drivingPosition = GCM - (env.PG - GCM) / env.PG.dist(GCM) * (env.Ra_pi_pi * sqrt(env.N)); //ra*sqrt(N) is Strombom equation for driving location
	//			//drivingPosition = this->agent->Lambda_t - ((env.PG - this->agent->Lambda_t) / env.PG.dist(this->agent->Lambda_t))* env.fN; //ra*power(N,2/3) 
	//		}
	//	}
	//	else
	//	{
	//		int myRefDogID = ((env.sheepdogsSharedKnowledge)[this->agent->agentID - 1]).RefDogID; //Let me know my reference dog
	//		Vector2f myRefDogLoc = ((env.sheepdogsSharedKnowledge)[myRefDogID - 1]).dogCurrentLocation; //Use the previous information to access its location

	//		//Now I need to position my self relevant to this dog.
	//		float RefSheepDog2GCM_Angle = atan2(myRefDogLoc.y - GCM.y, myRefDogLoc.x - GCM.x);
	//		float RefSheepDog2Dist = myRefDogLoc.dist(GCM);
	//		std::string Direction = ((env.sheepdogsSharedKnowledge)[this->agent->agentID - 1]).dogLocationRelevant2RefDog;
	//		float pi = 22 / (float)7;
	//		float dist_theta = 0.5*pi / (float)env.M;

	//		if (Direction == "L")
	//		{
	//			float ThisSheepDog2GCM_Angle = RefSheepDog2GCM_Angle - dist_theta;
	//			drivingPosition.x = RefSheepDog2Dist * cos(ThisSheepDog2GCM_Angle) + GCM.x;
	//			drivingPosition.y = RefSheepDog2Dist * sin(ThisSheepDog2GCM_Angle) + GCM.y;
	//		}
	//		else if (Direction == "R")
	//		{
	//			float ThisSheepDog2GCM_Angle = RefSheepDog2GCM_Angle + dist_theta;
	//			drivingPosition.x = RefSheepDog2Dist * cos(ThisSheepDog2GCM_Angle) + GCM.x;
	//			drivingPosition.y = RefSheepDog2Dist * sin(ThisSheepDog2GCM_Angle) + GCM.y;
	//		}
	//	}





	//}


	return drivingPosition;
}

CollectingMultiSheepDogMode::CollectingMultiSheepDogMode(Agent* agent)
{
	this->Weight = 1;
	this->agent = agent;
	this->behaviorType = "Collecting";
}

Vector2f CollectingMultiSheepDogMode::GetForce()
{

	Vector2f CollectingForce = Vector2f();

	Vector2f CollectingPosition = GetCollectingPosition();
	//this->agent->P_beta_j_c_t = CollectingPosition;

	if ((CollectingPosition.x == 0) && (CollectingPosition.y == 0)) // Not Collecting, CollectingForce set to Zero.. Needs to be updated based on a decision not value
	{
		this->magnitude = 0;
	}
	else
	{
		this->magnitude = CollectingPosition.dist(this->agent->position_t);
		if (this->magnitude > 0)
		{
				CollectingForce = (CollectingPosition - this->agent->position_t) / CollectingPosition.dist(this->agent->position_t);
		}
		//CollectingForce = (this->agent->position_t- CollectingPosition) / this->agent->position_t.dist(CollectingPosition);
		

	}
	//SheepDogAgent* cs = dynamic_cast<SheepDogAgent *>(agent);
	return CollectingForce;
}

Vector2f CollectingMultiSheepDogMode::GetCollectingPosition()
{	//1.The sheepdog find its own record in the sheepdog shared information table
	//2. The sheepdog test if the furthest sheepID is assigned to it or no via searching its own record in the conflict resolution table.
	//3. If this sheepdog is assigned to that sheepdog, then it goes to collect it.
	Vector2f CollectingPosition = Vector2f();

	Environment& env = Environment::getInstance();
	//this->agent->agentID this is the agent ID. we need to access the corresponding record in the sheepdogsSharedKnowledge, which will be (agentID-1) as the vector starts from zero, and the IDs starts from one.
	
		//find my record in the Roster
	std::string thisSheepDogRole = (env.SheepDogRoster)[this->agent->agentID - 1].dogAssignedTask;



	

		// if collecting find my record in the collecting table

	if (thisSheepDogRole == "Collecting")
	{
		//if driving find my row in the sheepdogsSharedDrivingKnowledge
		int thisAgentInd = 0;
		for (int i = 0; i < env.sheepdogsSharedCollectingKnowledge.size(); i++)
		{
			if ((env.sheepdogsSharedCollectingKnowledge)[i].dogID == this->agent->agentID)
			{
				thisAgentInd = i;
			}
		}

		int SheeptoCollectID = ((env.sheepdogsSharedCollectingKnowledge)[thisAgentInd]).AssignedSheepID;
		this-> agent->LoggingSupportingInformation= "toBeCollectedSheepID:"+ std::to_string(SheeptoCollectID);
		int selectedSheepIndex = SheeptoCollectID - (env.M + 1);
		Vector2f furthestSheepLoc = ((env.sheepdogsSharedCollectingKnowledge)[thisAgentInd]).AssignedSheepLoc;
		//furthestSheepLoc = (*(*env.sheepFlock)[selectedSheepIndex]).position_t;
		this->agent->Lambda_t = (env.sheepdogsSharedCollectingKnowledge)[thisAgentInd].GCM;
		if (env.CollectingPositionEq == 1)
		{
			CollectingPosition = furthestSheepLoc - (((env.sheepdogsSharedCollectingKnowledge)[thisAgentInd].GCM - furthestSheepLoc) / (env.sheepdogsSharedCollectingKnowledge)[thisAgentInd].GCM.dist(furthestSheepLoc)) * env.R2;
		}
		else if (env.CollectingPositionEq == 0)
		{
			CollectingPosition = furthestSheepLoc - (((env.sheepdogsSharedCollectingKnowledge)[thisAgentInd].GCM - furthestSheepLoc) / (env.sheepdogsSharedCollectingKnowledge)[thisAgentInd].GCM.dist(furthestSheepLoc)) * env.Ra_pi_pi;
		}
		//}

	}
	

	return CollectingPosition;
}
