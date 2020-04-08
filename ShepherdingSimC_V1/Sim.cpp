//#include "pch.h"
#include <iostream>
#include "Sim.h"
#include <list>
#include "Environment.h"
#include "Terrain.h"
#include "Flock.h"
#include <Vector2.h>
#include "SupportingCalc.h"
#include <tuple>
#define _USE_MATH_DEFINES
#include <math.h>
#include <algorithm>
#include <random>

//int circularPathPlanningMode;
//int circularPathPlanningRadius;
//bool circularPathPlanning;
//int R3;
Simulation::Simulation()
{
}

Simulation::~Simulation()
{
}

//Flock* Simulation::init(int numSheepAgents, int numSheepDogAgents, int fieldStartX, int fieldStartY, int fieldWidth, int fieldHeight)
//{
//	this->fieldStartX = fieldStartX;
//	this->fieldStartY = fieldStartY;
//	this->fieldWidth = fieldWidth;
//	this->fieldHeight = fieldHeight;
//	return new Flock(numSheepAgents, numSheepDogAgents, fieldStartX, fieldStartX+fieldWidth, fieldStartY, fieldStartY+fieldHeight);
//
//	
//	
//}

//void Simulation::init(int numSheepAgents, int numSheepDogAgents, int fieldStartX, int fieldStartY, int fieldWidth, int fieldHeight, int paddockLength, int paddockWidth)
//{
//	timestep = 0;
//	goalFound = false;
//
//	Environment& env = Environment::getInstance();
//	
//	
//	this->fieldStartX = fieldStartX;
//	this->fieldStartY = fieldStartY;
//	this->paddockWidth = paddockWidth;
//	this->paddockLength = paddockLength;
//
//	//this->fieldWidth = fieldWidth;
//	//this->fieldHeight = fieldHeight;
//	
//	env.FieldHeight = fieldHeight;
//	env.FieldWidth = fieldWidth;
//	env.N= numSheepAgents;	//(1--201)          & Cardinality of Pi
//	env.M= numSheepDogAgents;// (1--20)         & Cardinality of B
//	env.R_pi_beta=65;		// (65u)			& pi sensing range for beta
//	env.R_beta_beta = 2;
//	env.Ra_pi_pi=2;			// (2u)				& pi collision avoidance range for pi
//	env.Rs_pi_pi = 20;
//	env.card_Omega_pi_pi = numSheepAgents-1; //maximum N-1		& Number of  agents(neighbourhood) a sheep agent operates on
//	env.card_Omega_beta_pi = numSheepAgents; //maximum N		& Number of  agents(neighbourhood) a sheepDog agent operates on
//	env.W_pi_pi=2;			// (2)				& pi repulsion strength from pi
//	env.W_beta_beta = 2;
//	env.W_pi_beta=1;		// (1)				& pi repulsion strength from beta
//	env.W_pi_Lambda=1.05;	// (1.05)			& pi attraction strength to Lambda
//	env.W_pi_upsilon=0.5;	// (0.5)			& Strength of pi previous direction
//	env.W_e_pi_i=0.3;		// (0.3)			& Strength of sheep pi_j angular noise
//	env.W_e_beta_j=0.3;		// (0.3)			& Strength of shepherd beta_j angular noise
//	//env.S_t_beta_j = 1;		//					& Speed of beta at time t
//	env.eta = 0.05;			//(0.05)			& Probability of moving per time step while grazing
//	//env.fN= env.Ra_pi_pi*pow(env.N, ((float)2 / (float)3));
//	env.fN = std::sqrt(2)*env.Ra_pi_pi*sqrt(env.N);
//	env.R1 = env.fN; //R1 is an alias for fn;
//	env.PG.x = (fieldStartX + fieldWidth);
//	env.PG.y = (fieldStartY + fieldHeight);
//	env.S_t_beta_j = 2;
//	env.R2 = 4;
//	env.R3 = 4;
//	
//	//env.S_t_pi_i = 1;
//	env.sheepDogFlock = new SheepDogFlock(numSheepDogAgents, fieldStartX, fieldStartX + fieldWidth, fieldStartY, fieldStartY + fieldHeight, 1, env.S_t_beta_j);
//	env.sheepFlock= new SheepFlock(numSheepAgents, fieldStartX, fieldStartX + fieldWidth, fieldStartY, fieldStartY + fieldHeight,env.M+1, std::string("P1"));
//	
//
//	paddockBoundry = { Vector2f(env.PG.x - paddockWidth / 2, env.PG.y - paddockLength / 2) ,
//	Vector2f((env.PG.x - paddockWidth / 2 + paddockWidth), env.PG.y - paddockLength / 2) ,
//				Vector2f(env.PG.x - paddockWidth / 2 + paddockWidth, env.PG.y - paddockLength / 2 + paddockLength),
//		 Vector2f(env.PG.x - paddockWidth / 2, env.PG.y - paddockLength / 2 + paddockLength)
//	};
//
//}
void Simulation::init(int randomNumberSeed, int numSheepAgents, int numSheepDogAgents, int fieldStartX, int fieldStartY, int fieldWidth, int fieldHeight, float R_pi_beta, float Ra_pi_pi,float Rs_pi_pi, float R_beta_beta, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLength, int paddockWidth, bool paddockON, bool CircularPathPlanningON, bool StallingON, float StallingDistance, int R2, int r3, int GoalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, float obstaclesDensity, float obstaclesRadius)
{
	std::mt19937 generator(randomNumberSeed);

	timestep = 0;
	goalFound = false;
	goalRadius = GoalRadius;
	this->circularPathPlanning = CircularPathPlanningON;
	//circularPathPlanningMode = CircularPathPlanningMode;
	//circularPathPlanningRadius = CircularPathPlanningRadius;
	Environment& env = Environment::getInstance();

	this->fieldStartX = fieldStartX;
	this->fieldStartY = fieldStartY;
	//this->fieldWidth = fieldWidth;
	//this->fieldHeight = fieldHeight;
	this->paddockWidth = paddockWidth;
	this->paddockLength = paddockLength;
	



	env.FieldHeight = fieldHeight;
	env.FieldWidth = fieldWidth;
	env.N= numSheepAgents;					//(1--201)           & Cardinality of Pi
	env.M= numSheepDogAgents;					// (1--20)            & Cardinality of B
	env.R_pi_beta = R_pi_beta;			// (65u)			& pi sensing range for beta
	env.R_beta_beta = R_beta_beta;
	env.Ra_pi_pi = Ra_pi_pi;			// (2u)				& pi collision avoidance range for pi
	env.Rs_pi_pi = Rs_pi_pi;
	env.card_Omega_pi_pi = card_Omega_pi_pi;			//&Number of  agents(neighbourhood) a sheep agent operates on
	env.card_Omega_beta_pi = card_Omega_beta_pi;		//& Number of  agents(neighbourhood) a sheepDog agent operates on
	env.W_pi_pi = W_pi_pi;			// (2)				& pi repulsion strength from pi
	env.W_beta_beta = W_beta_beta;
	env.W_pi_beta = W_pi_beta;		// (1)				& pi repulsion strength from beta
	env.W_pi_Lambda = W_pi_Lambda;		// (1.05)			& pi attraction strength to Lambda
	env.W_pi_upsilon = W_pi_upsilon;	// (0.5)			& Strength of pi previous direction
	env.W_e_pi_i = W_e_pi_i;		// (0.3)			& Strength of sheep pi_j angular noise
	env.W_e_beta_j = W_e_beta_j;		// (0.3)			& Strength of shepherd beta_j angular noise
	//env.S_t_beta_j = S_t_beta_j;
	//env.S_t_pi_i = S_t_pi_i;
	env.eta = eta;
	//env.fN= env.Ra_pi_pi*pow(env.N, ((float)2 / (float)3));
	if (fNequation == 1)
	{
		env.fN = env.Ra_pi_pi*sqrt(2*env.N);
	}
	if (fNequation == 0)
	{
		env.fN = env.Ra_pi_pi*pow(env.N, ((float)2 / (float)3));
	}

	env.R1 = env.fN;
	env.PG.x = goalLocX;
	env.PG.y = goalLocY;
	env.S_t_beta_j = S_t_beta_j;
	env.R2 = R2;
	env.R3 = r3;
	env.DrivingPositionEq = DrivingPositionEq;
	env.CollectingPositionEq = CollectingPositionEq;
	env.SheepNeignborhoodSelection = SheepNeignborhoodSelection;
	env.ModulationDecayFactor = ModulationDecayFactor;
	env.ForceRegulated = ForceRegulated;
	env.stallingON = StallingON;
	env.stallingDist = StallingDistance;
	//env.sheepDogFlock = new SheepDogFlock(numSheepDogAgents, fieldStartX, fieldStartX + fieldWidth, fieldStartY, fieldStartY + fieldHeight, 1);

	//env.sheepFlock = new SheepFlock(numSheepAgents, fieldStartX, fieldStartX + fieldWidth, fieldStartY, fieldStartY + fieldHeight, env.M + 1);

	env.sheepDogFlock = new SheepDogFlock(generator, numSheepDogAgents, sheepDogInitializationStartingX, sheepDogInitializationStartingX + sheepDogInitializationXRange, sheepDogInitializationStartingY, sheepDogInitializationStartingY + sheepDogInitializationYRange, 1, S_t_beta_j);

	env.sheepFlock = new SheepFlock(generator, numSheepAgents, sheepInitializationStartingX, sheepInitializationStartingX+sheepInitializationXRange,  sheepInitializationStartingY, sheepInitializationStartingY+ sheepInitializationYRange, env.M + 1, sheepInitializationPattern);
	
	if (paddockON)
	{
		paddockBoundry = { Vector2f(env.PG.x - paddockWidth / 2, env.PG.y - paddockLength / 2) ,
		Vector2f((env.PG.x - paddockWidth / 2 + paddockWidth), env.PG.y - paddockLength / 2) ,
		Vector2f(env.PG.x - paddockWidth / 2 + paddockWidth, env.PG.y - paddockLength / 2 + paddockLength),
		Vector2f(env.PG.x - paddockWidth / 2, env.PG.y - paddockLength / 2 + paddockLength)
		};
	}
	env.terrain.staticObstacles= new StaticObstaclesList(generator, obstaclesDensity, obstaclesRadius, fieldStartX, fieldStartX + fieldWidth, fieldStartY, fieldStartY + fieldHeight);
}

//Flock*  Simulation::init()
//{
//	this->fieldStartX = 0;
//	this->fieldStartY = 0;
//	return new Flock();
//}

void Simulation::update()
{
	Environment& env = Environment::getInstance();
	
	if (!goalFound)
	{
	env.sheepFlock->CalcNewLoc();
	env.sheepDogFlock->CalcNewLoc();
	if (circularPathPlanning)
	{
	//checkSheepDogNotDisturbingSheep(env.sheepDogFlock, env.sheepFlock,circularPathPlanningRadius, circularPathPlanningMode);
	checkSheepDogNotDisturbingSheep(env.sheepDogFlock, env.sheepFlock);
	}
		
	//before updating t1 to t. Check if moving from t to t1 is a valid move

	if (paddockBoundry.size()>0)
	{
		CheckFenceViolation(paddockBoundry, env.sheepFlock, env.sheepDogFlock);
	}
	
	
	env.sheepFlock->Move();
	env.sheepDogFlock->Move();
	timestep = timestep + 1;
	}

	checkIfGoalFound(); //Ours: Goal found if all sheep within radius from the goal
	//checkIfGoalFound2(); //Strombom: Goal found based on distance between GCM and goal
	

}
void Simulation::checkIfGoalFound()
{
	Environment& env = Environment::getInstance();
	bool sheepAtGoal = true;
	if (paddockBoundry.size()>0) //if there is a paddock, then if all sheep within paddock, task is complete.
	{
		int i = 0;
		//bool test = false;
		/*test = PointInPolygon((*env.sheepFlock)[9]->position_t, paddockBoundry);
		if (test)
		{
			float stop2 = 1;
		}
		*/
		while ((sheepAtGoal) && i < env.sheepFlock->size())
		{

			//if ((*env.sheepFlock)[i]->position_t.dist(env.PG) > env.Ra_pi_pi*5 )
			if (!PointInPolygon((*env.sheepFlock)[i]->position_t, paddockBoundry))
			{
				sheepAtGoal = false;
			}
			i++;

		}
	}
	else //if there is no paddock, then if all sheep within an x distance from the goal, then task is completed. this x is a radius around the goal point. We can use the paddock length parameter from the config file for radius.
	{
		int i = 0;
		
		while ((sheepAtGoal) && i < env.sheepFlock->size())
		{

			if ((*env.sheepFlock)[i]->position_t.dist(env.PG) > goalRadius )
			{
				sheepAtGoal = false;
			}
			i++;

		}
	}
	if (sheepAtGoal)
	{
		goalFound = true;
	}
	
}

void Simulation::checkIfGoalFound2() //Strombom based on distance between GCM and goal
{
	Environment& env = Environment::getInstance();
	bool goalFound = false;
	Vector2f GCM = Vector2f();
	for (int i = 0; i < env.sheepFlock->size(); i++)
	{
		GCM = GCM + (*env.sheepFlock)[i]->position_t;

	}
	GCM = GCM / env.sheepFlock->size();
	if (GCM.dist(env.PG) < goalRadius)
		this->goalFound = true;
}

void Simulation::checkNotDisturbingSheep(float safeDist, SheepDogAgent* sheepDog)
{ //calculate the following to be used
	float SP[] = { sheepDog->position_t.x,sheepDog->position_t.y };
	float LCM[] = { sheepDog->Lambda_t.x, sheepDog->Lambda_t.y };
	float TP[] = { sheepDog->position_t1.x, sheepDog->position_t1.y };
	float theta_step = 0.1;
	float TP_theta = atan2(TP[1] - LCM[1], TP[0] - LCM[0]);
	
	//check if the sheepDog is already so close to the driving or collecting position. if within small distance, allow them to break in the circle, otherwise, update their position.
	Vector2f Pcd = Vector2f();
	// 1. Identify if Driving or collecting, and retrieve the target position
	if (sheepDog->get_F_beta_j_c_t().x != 0 && sheepDog->get_F_beta_j_c_t().y != 0)
	{
		Pcd.x = sheepDog->get_P_beta_j_c_t().x;
		Pcd.y = sheepDog->get_P_beta_j_c_t().y;
	}
	else if (sheepDog->get_F_beta_j_d_t().x != 0 && sheepDog->get_F_beta_j_d_t().y != 0)
	{
		Pcd.x = sheepDog->get_P_beta_j_d_t().x;
		Pcd.y = sheepDog->get_P_beta_j_d_t().y;
	}
	//2. Pcd theta 
	float Pcd_theta = atan2(Pcd.y - LCM[1], Pcd.x - LCM[0]);
	//if (std::abs(TP_theta - Pcd_theta) < 5 * theta_step)
	//{//do nothing
	//no need to update the position
		//the sheepDog is close to its driving or collecting position and it is allowed to access the outer circle
	//}
	//else
	float sheepDogNextDistance = sheepDog->position_t1.dist(sheepDog->Lambda_t);
		if ((sheepDog->position_t1.dist(sheepDog->Lambda_t) < safeDist) && (std::abs(TP_theta - Pcd_theta) > 2 * theta_step))
	{

		/*printf(" SheepDog's next position is within %.2f distance from its LCM\n ", sheepDog->position_t1.dist(sheepDog->Lambda_t) );
		printf("Safe Distance should not be less than  %.2f \n ", safeDist);

		printf("TP_theta - Pcd_theta equal to %.2f \n ", std::abs(TP_theta - Pcd_theta));
		printf("Difference should be be less than  %.2f \n ", 5 * theta_step);*/


		float r = std::min(safeDist, sheepDog->position_t.dist(sheepDog->Lambda_t)+sheepDog->get_S_t_beta_j());
		float NP_cx;
		float NP_cy;


		//Define the closest points to SP and TP on the circle
		float SP_theta = atan2(SP[1] - LCM[1], SP[0] - LCM[0]);
		float SP_cx = r * cos(SP_theta) + LCM[0];
		float SP_cy = r * sin(SP_theta) + LCM[1];


		
		float TP_cx = r * cos(TP_theta) + LCM[0];
		float TP_cy = r * sin(TP_theta) + LCM[1];

		//Identify the next step until reaching the target point
		float NP_x = SP_cx;
		float NP_y = SP_cy;

		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//check if clockwise is shorter or counterclockwise
		//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
		//1. first augment the negative values
		if (SP_theta < 0) {
			SP_theta = SP_theta + 2 * M_PI;
		}
		if ((TP_theta) < 0)
		{
			TP_theta = TP_theta + 2 * M_PI;
		}


		//2. Decide on clockwise or counterclockwise based on distance between
		//Starting point SP and target point TP
		float NP_theta = SP_theta;
		//NP refers to Next point.Identify its theta first, then estimat its x, y values

		if (0 < (SP_theta - TP_theta) && (SP_theta - TP_theta) < M_PI)
		{
			//clockwise is shorter
			//std::cout << "clockwise is shorter" << std::endl;

			while (NP_theta > TP_theta)

			{
				NP_theta = NP_theta - theta_step;
				NP_cx = r * cos(NP_theta) + LCM[0];
				NP_cy = r * sin(NP_theta) + LCM[1];
			}
		}
		else if ((SP_theta - TP_theta) > M_PI)
		{
			//counterclockwise is shorter
			//std::cout << "counterclockwise is shorter" << std::endl;
			while (NP_theta < TP_theta + 2 * M_PI)
			{
				NP_theta = NP_theta + theta_step;
				NP_cx = r * cos(NP_theta) + LCM[0];
				NP_cy = r * sin(NP_theta) + LCM[1];
			}
		}
		else if ((SP_theta - TP_theta) < 0)
		{
			//counterclockwise is shorter
			//std::cout << "counterclockwise is shorter" << std::endl;
			while (NP_theta < TP_theta)
			{
				NP_theta = NP_theta + theta_step;
				NP_cx = r * cos(NP_theta) + LCM[0];
				NP_cy = r * sin(NP_theta) + LCM[1];
			}
		}
	/*	std::cout << "SheepDog ID " << std::to_string(sheepDog->agentID) << std::endl;
		std::cout << "Safe Dist " << std::to_string(safeDist) << std::endl;
		std::cout << "Next Pos Dist to GCM " << std::to_string(sheepDog->position_t1.dist(sheepDog->Lambda_t)) << std::endl;
		printf(" SheepDog t1 has been updated from (%.2f , %.2f) to (%.2f , %.2f)\n ", sheepDog->position_t1.x, sheepDog->position_t1.y, NP_cx, NP_cy);
		*/
		sheepDog->position_t1 = Vector2f(NP_cx, NP_cy);
		/*	std::cout << "Now the next Pos Dist to GCM " << std::to_string(sheepDog->position_t1.dist(sheepDog->Lambda_t)) << std::endl;

			std::cout << "**************" << std::endl;*/

	}
}

//void Simulation::checkSheepDogNotDisturbingSheep(SheepDogFlock * sheepDogFlock, SheepFlock * sheepFlock, int CircularPathPlanningRadius, int CircularPathPlanningMode)
void Simulation::checkSheepDogNotDisturbingSheep(SheepDogFlock * sheepDogFlock, SheepFlock * sheepFlock)
{
	SheepDogFlock::iterator sheepDogIter;
	for (sheepDogIter = sheepDogFlock->begin(); sheepDogIter != sheepDogFlock->end(); sheepDogIter++)
	{
		// Modify the next step to be lying on a the circle surface that does not disturb the sheep
		float sheepDog2LCM_Angle = atan2((*sheepDogIter)->position_t1.y - (*sheepDogIter)->Lambda_t.y, (*sheepDogIter)->position_t1.x - (*sheepDogIter)->Lambda_t.x);
		//float sheepDog2LCM_radius = (*sheepDogIter)->position_t1.dist((*sheepDogIter)->Lambda_t);
		/*Environment& env = Environment::getInstance();
					float sheepDog_t1_2LCM_MinRadius = env.fN + safety_dist;*/

		//int safety_dist = 0;

		//float	sheepDog_t1_2LCM_MinRadius = 0;
		//if (circularPathPlanningMode == 0)
		//{
			//sheepDog_t1_2LCM_MinRadius = circularPathPlanningRadius;

		//}
		//else if (circularPathPlanningMode == 1)
		//{
			float furthestDist = 0;

			SheepFlock::iterator sheepIter;
			for (sheepIter = sheepFlock->begin(); sheepIter != sheepFlock->end(); sheepIter++)
			{
				if ((*sheepIter)->position_t.dist((*sheepDogIter)->Lambda_t) > furthestDist)
				{
					furthestDist = (*sheepIter)->position_t.dist((*sheepDogIter)->Lambda_t);
				}

			}
			Environment& env = Environment::getInstance();
			
			float sheepDog_t1_2LCM_MinRadius = std::max(furthestDist,env.R1)+env.R2+env.R3; //outter (3rd) circle radius
		//}
		checkNotDisturbingSheep(sheepDog_t1_2LCM_MinRadius, (*sheepDogIter));

	}
}



void Simulation::clean()
{
}
//float  Simulation::roundFloat2f(float myfloat)
//{
//	float amp = trunc(myfloat * 100);
//	return  amp / 100;
//}

void Simulation::CheckFenceViolation(std::vector<Vector2f> paddockBoundry, SheepFlock* sheepFlock, SheepDogFlock* sheepDogFlock)

{
	Line line1 = { paddockBoundry[0],  paddockBoundry[1] };
	Line  line2 = { paddockBoundry[0], paddockBoundry[3] };
	Line  line3 = { paddockBoundry[3], paddockBoundry[2] };

	std::vector<Line> lines = { line1, line2, line3 };
	std::vector<Line>::iterator lineIter;
	SheepFlock::iterator sheepIter;

	for (sheepIter = sheepFlock->begin(); sheepIter != sheepFlock->end(); sheepIter++)
	{
		Line sheepMoveline = { Vector2f((*sheepIter)->position_t.x, (*sheepIter)->position_t.y), Vector2f((*sheepIter)->position_t1.x, (*sheepIter)->position_t1.y) };
		int i = 0;
		bool conflictNotFound = true;
		while ((conflictNotFound) && (i < lines.size()))
		{
			Line lineTested = lines[i];
			float intersect_x;
			float intersect_y;
			bool intersect_exist = get_line_intersection(sheepMoveline.p, sheepMoveline.q, lineTested.p, lineTested.q, &intersect_x, &intersect_y);

			if (intersect_exist)
			{
				conflictNotFound = false;
				Vector2f intersect_loc = Vector2f(intersect_x, intersect_y);
				if (lineTested.p.x == lineTested.q.x)
				{
					if ((*sheepIter)->position_t.x > (*sheepIter)->position_t1.x)
					{
						(*sheepIter)->position_t1.x = intersect_loc.x + 1;
						(*sheepIter)->position_t1.y = intersect_loc.y;
					}
					else if ((*sheepIter)->position_t.x < (*sheepIter)->position_t1.x)

					{
						(*sheepIter)->position_t1.x = intersect_loc.x - 1;
						(*sheepIter)->position_t1.y = intersect_loc.y;

					}
				}
				if (lineTested.p.y == lineTested.q.y)
				{
					if ((*sheepIter)->position_t.y > (*sheepIter)->position_t1.y)
					{
						(*sheepIter)->position_t1.x = intersect_loc.x;
						(*sheepIter)->position_t1.y = intersect_loc.y + 1;


					}
					else if ((*sheepIter)->position_t.y < (*sheepIter)->position_t1.y)
					{
						(*sheepIter)->position_t1.x = intersect_loc.x;
						(*sheepIter)->position_t1.y = intersect_loc.y - 1;


					}
				}
			}
			i++;
		}
	}


	SheepDogFlock::iterator sheepDogIter;
	for (sheepDogIter = sheepDogFlock->begin(); sheepDogIter != sheepDogFlock->end(); sheepDogIter++)
	{
		Line sheepDogMoveline = { Vector2f((*sheepDogIter)->position_t.x, (*sheepDogIter)->position_t.y), Vector2f((*sheepDogIter)->position_t1.x, (*sheepDogIter)->position_t1.y) };
		int i = 0;
		bool conflictNotFound = true;
		while ((conflictNotFound) && (i < lines.size()))
		{
			Line lineTested = lines[i];
			float intersect_x = 0;
			float intersect_y = 0;
			bool intersect_exist = get_line_intersection(sheepDogMoveline.p, sheepDogMoveline.q, lineTested.p, lineTested.q, &intersect_x, &intersect_y);

			if (intersect_exist)
			{
				conflictNotFound = false;
				Vector2f intersect_loc = Vector2f(intersect_x, intersect_y);
				if (lineTested.p.x == lineTested.q.x)
				{
					if ((*sheepDogIter)->position_t.x > (*sheepDogIter)->position_t1.x)
					{
						(*sheepDogIter)->position_t1.x = intersect_loc.x + 1;
						(*sheepDogIter)->position_t1.y = intersect_loc.y;
					}
					else if ((*sheepDogIter)->position_t.x < (*sheepDogIter)->position_t1.x)

					{
						(*sheepDogIter)->position_t1.x = intersect_loc.x - 1;
						(*sheepDogIter)->position_t1.y = intersect_loc.y;

					}
				}
				if (lineTested.p.y == lineTested.q.y)
				{
					if ((*sheepDogIter)->position_t.y > (*sheepDogIter)->position_t1.y)
					{
						(*sheepDogIter)->position_t1.x = intersect_loc.x;
						(*sheepDogIter)->position_t1.y = intersect_loc.y + 1;


					}
					else if ((*sheepDogIter)->position_t.y < (*sheepDogIter)->position_t1.y)
					{
						(*sheepDogIter)->position_t1.x = intersect_loc.x;
						(*sheepDogIter)->position_t1.y = intersect_loc.y - 1;
					}
				}
			}
			i++;
		}
	}

}