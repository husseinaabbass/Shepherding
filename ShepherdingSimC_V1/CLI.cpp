#include "CLI.h"
#include "pch.h"
#include "Flock.h"
//#include <assert.h>     /* assert */
#include "Sim.h"
/* CLI class
* Holds all information dealing with the Simulation without visual feedback. It saves the information to a log file
*/

//int screenWIDTH, screenHEIGHT;
//int fieldWIDTH, fieldHEIGHT;
//int goalLOCX, goalLOCY;
//int PaddockLength, PaddockWidth;
//int simulationSpeed;
int InterfaceClock;
//bool PaddockOn;
//int GoalRadius;

Simulation* CLIsim;
int maximumNumSteps;
int GoalRadius_cli;



CLI::CLI()
{
}


CLI::~CLI()
{
}


void CLI::init( int randomNumberSeed, int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi,  float R_beta_beta, float R_beta_pi, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor,
	int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius)
{
	//simulationSpeed = simSpeed;
	//InterfaceClock = 0;
//	PaddockLength = paddockLENGTH;
	//PaddockWidth = paddockWIDTH;
	//PaddockOn = paddockON;
	//GoalRadius = goalRadius;

	
	//fieldWIDTH = fieldWidth;
	//fieldHEIGHT = fieldHeight;
	//this->fieldStartX = 0;
	//this->fieldStartY = 0;
	//goalLOCX = goalLocX;
	//goalLOCY = goalLocY;
	GoalRadius_cli = goalRadius;
	CLIsim = new Simulation();
	CLIsim->init(randomNumberSeed, N, M, fieldStartX, fieldStartY, fieldWidth, fieldHeight, R_pi_beta, Ra_pi_pi, Rs_pi_pi, R_beta_beta, R_beta_pi, W_pi_pi, W_beta_beta, W_pi_beta, W_pi_Lambda, W_pi_upsilon, W_e_pi_i, W_e_beta_j, S_t_beta_j, eta, card_Omega_pi_pi, card_Omega_beta_pi, goalLocX, goalLocY, paddockLENGTH, paddockWIDTH, paddockON, circularPathPlanningON,  StallingON,  StallingDistance, R2, R3, goalRadius, ForceRegulated, fNequation, DrivingPositionEq, CollectingPositionEq, SheepNeignborhoodSelection, ModulationDecayFactor, sheepInitializationStartingX, sheepInitializationStartingY, sheepInitializationXRange, sheepInitializationYRange, sheepInitializationPattern, sheepDogInitializationStartingX, sheepDogInitializationStartingY, sheepDogInitializationXRange, sheepDogInitializationYRange, obstaclesDensity, obstaclesRadius);

	CLI::isRunning = true;
	maximumNumSteps = MaximumNumSteps;
}

void CLI::handleEvents()
{

		/*if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;
		}*/
	
}

void CLI::update()
{
	//if (InterfaceClock%simulationSpeed == 0)
	//{
	CLIsim->update();
	//}
	//InterfaceClock++;
}



//std::list<float> CLI::streamOut(std::ofstream & outfile, std::ofstream & outputCompletionTimefile)
void CLI::streamOut(std::ofstream & outfile, std::ofstream & outputCompletionTimefile)
{
	Environment& env = Environment::getInstance();

	//printf(" Simulation step %d ", CLIsim->timestep);
	//std::list<float> newRow;
	outfile << CLIsim->timestep << ",";

	for (int i = 0; i < env.sheepDogFlock->size(); i++) {
		/*printf(" SheepDog is moving from (%.2f , %.2f) \n ", (*env.sheepDogFlock)[i]->position_t.x, (*env.sheepDogFlock)[i]->position_t.y);*/
		//std::cout << "**************" << std::endl;
		outfile << (*env.sheepDogFlock)[i]->agentID << ",";
		outfile << (*env.sheepDogFlock)[i]->position_t.x << ",";
		outfile << (*env.sheepDogFlock)[i]->position_t.y << ",";
		outfile << (*env.sheepDogFlock)[i]->F_t.x << ",";
		outfile << (*env.sheepDogFlock)[i]->F_t.y << ",";
		if ((*env.sheepDogFlock)[i]->get_F_beta_j_d_t().x != 0 || (*env.sheepDogFlock)[i]->get_F_beta_j_d_t().y != 0)
		{
			outfile << "Driving" << ",";
			std::string supportingInfo = (*env.sheepDogFlock)[i]->LoggingSupportingInformation;
			std::string role = supportingInfo.substr(supportingInfo.find(":")+1);
			outfile << role << ",";
		}
		else if ((*env.sheepDogFlock)[i]->get_F_beta_j_c_t().x != 0 || (*env.sheepDogFlock)[i]->get_F_beta_j_c_t().y != 0)
		{
			outfile << "Collecting" << ",";
			std::string supportingInfo = (*env.sheepDogFlock)[i]->LoggingSupportingInformation;
			std::string toBeCollectedSheepID = supportingInfo.substr(supportingInfo.find(":")+1);
			outfile << toBeCollectedSheepID << ",";
		}
		else
		{
			outfile << "" << ",";
			outfile << "" << ",";

		}
	
	}
	for (int i = 0; i < env.sheepFlock->size(); i++) {
		/*printf(" Sheep is moving from (%.2f , %.2f) \n ", (*env.sheepFlock)[i]->position_t.x, (*env.sheepFlock)[i]->position_t.y);
		std::cout << "**************" << std::endl;*/
		outfile << (*env.sheepFlock)[i]->agentID << ",";
		outfile << (*env.sheepFlock)[i]->position_t.x << ",";
		outfile << (*env.sheepFlock)[i]->position_t.y << ",";
		outfile << (*env.sheepFlock)[i]->F_t.x << ",";
		outfile << (*env.sheepFlock)[i]->F_t.y << ",";

	}
	outfile << std::endl;
	std::cout << "*" ;

	if (CLIsim->goalFound == true)
	{
		CLI::isRunning  = false;
		std::cout << "Task completed at time step: "<< CLIsim->timestep <<". All sheep are at goal" << std::endl;
		outputCompletionTimefile << CLIsim->timestep << ",1," << std::endl;
	}
	else if (CLIsim->timestep>=maximumNumSteps)
	{
		CLI::isRunning = false;
		std::cout << "Task Not completed, Time exceeded, and simulation will be terminated off" << std::endl;
		//Count Number of Sheep at Goal
		int NsheepAtGoal = 0;
		for (int i = 0; i < env.sheepFlock->size(); i++) {
			if ((*env.sheepFlock)[i]->position_t.dist(env.PG) <= GoalRadius_cli)
			{
				NsheepAtGoal++;
			}
		}

		outputCompletionTimefile << CLIsim->timestep << "," <<(float)NsheepAtGoal/(float)env.N  << std::endl;


		//outputCompletionTimefile << "Not completed within time" << std::endl;
	}
	//return newRow;

}


bool CLI::running()
{
	return isRunning;
}













