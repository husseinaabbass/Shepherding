#include "stdafx.h"

#include "Utilities.h"
#include <numeric>      // std::iota
#include<vector>
#include "Vector2.h"
#include "Flock.h"
#include "Environment.h"
#include <tuple>
#include <math.h>

//template <typename T>


//std::vector<size_t> sort_indexes(const vector<T> &v) {
//
//	// initialize original index locations
//	vector<size_t> idx(v.size());
//	iota(idx.begin(), idx.end(), 0);
//
//	// sort indexes based on comparing values in v
//	sort(idx.begin(), idx.end(),
//		[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });
//
//	return idx;
//}
double calcDistTwoLoc(Vector2f Loc1, Vector2f Loc2)
{

	return Loc1.dist(Loc2);
}

Vector2f calculateLocalCentreOfMass(SheepList sheepList)
{//this function calculate the local centre of mass of a list of sheep
	// 1. set the value of the summation variable to zero
	// 2. sum all the locations using a loop
	// 3. divide by the number of agents in the list.

	Vector2f LocalCentreOfMass = Vector2f(); // 1. set the value of the summation variable to zero
	for (int i = 0; i < sheepList.size(); i++)
	{
		LocalCentreOfMass.x = LocalCentreOfMass.x+sheepList[i]->position_t.x;  // 2a. sum all x locations using a loop
		LocalCentreOfMass.y = LocalCentreOfMass.y+sheepList[i]->position_t.y;  // 2b. sum all y locations using a loop	
	}
	LocalCentreOfMass.x = LocalCentreOfMass.x / sheepList.size();				// 3. divide by the number of agents in the list.
	LocalCentreOfMass.y = LocalCentreOfMass.y / sheepList.size();

	return LocalCentreOfMass;					
}

Vector2f calculateGloablCentreOfMass(SheepFlock* sheepList)
{//this function calculate the Global centre of mass of a list of sheep
	// 1. set the value of the summation variable to zero
	// 2. sum all the locations using a loop
	// 3. divide by the number of agents in the list.
	
	Vector2f GlobalCentreOfMass = Vector2f(); // 1. set the value of the summation variable to zero
	for (int i = 0; i < sheepList->size(); i++)
	{
		GlobalCentreOfMass.x = GlobalCentreOfMass.x + (*sheepList)[i]->position_t.x;  // 2a. sum all x locations using a loop
		GlobalCentreOfMass.y = GlobalCentreOfMass.y + (*sheepList)[i]->position_t.y;  // 2b. sum all y locations using a loop	
	}
	GlobalCentreOfMass.x = GlobalCentreOfMass.x / (*sheepList).size();				// 3. divide by the number of agents in the list.
	GlobalCentreOfMass.y = GlobalCentreOfMass.y / (*sheepList).size();

	return GlobalCentreOfMass;
}

//std::tuple<SheepList, std::vector<int>> SenseSheepInNeighborhood(Agent* agent, int targetSizeOfNeighborhood, Environment& env) {
	
SheepList SenseSheepInNeighborhoodBasedOnNumber(Agent* agent, int targetSizeOfNeighborhood, Environment& env) {



	//initialise an empty list
	SheepList neighborhoodList = SheepList();


	//sort the distances, and retrieve the indices of sheep in the sheepFlock based on distance
	std::vector<int> y = RankSheepBasedOnDistTo(agent->position_t, (*env.sheepFlock));

	int k = 0; // sheepFlock while loop counter
	if (agent->agentType == "SheepAgent")
	{

		while (neighborhoodList.size() < targetSizeOfNeighborhood)   // Loop over the sheepFlock using k until  neighborhoodList is filled with a number of sheep equal to target size of neigborhood
		{

			if ((y[k] <= targetSizeOfNeighborhood) && (y[k] > 0))  //check the distance rank of each sheep using y[k]. If card_Omega_pi_pi is equal to 3. Only sheep with distance rank as 1 to 3 will be added to the neighborhoodlist.
																// which means closest 3 sheep. y[k] >0 will exclude the agent itself, as y starts from 0.
			{
				neighborhoodList.push_back((*env.sheepFlock)[k]);

			}
			k++;
		}
	}
	else
	{
		while (neighborhoodList.size() < targetSizeOfNeighborhood)   // Loop over the sheepFlock using k until  neighborhoodList is filled with a number of sheep equal to target size of neigborhood
		{

			if (y[k] <= targetSizeOfNeighborhood)   //check the distance rank of each sheep using y[k]. If card_Omega_pi_pi is equal to 3. Only sheep with distance rank as 1 to 3 will be added to the neighborhoodlist.
																// which means closest 3 sheep. 
			{
				neighborhoodList.push_back((*env.sheepFlock)[k]);

			}
			k++;
		}


	}
	//return std::make_tuple(neighborhoodList, y);
	return neighborhoodList;

}


SheepList SenseSheepInNeighborhoodBasedOnDist(Agent* agent,  Environment& env, float Dist) {



	//initialise an empty list
	SheepList neighborhoodList = SheepList();


	for (int i = 0; i < env.sheepFlock->size(); i++) {

		if ((agent->position_t.dist((*env.sheepFlock)[i]->position_t) < Dist) && (agent->agentID != (*env.sheepFlock)[i]->agentID))
		{
			neighborhoodList.push_back((*env.sheepFlock)[i]);
		}
	}

	
	return neighborhoodList;

}

//SheepList SenseSheepInNeighborhood(Agent* agent, int targetSizeOfNeighborhood, Environment& env)
//{
//
//	//Environment& env = Environment::getInstance();
//
//
//	//initialise an empty list
//	SheepList neighborhoodList = SheepList();
//
//	
//	//sort the distances, and retrieve the indices of sheep in the sheepFlock based on distance
//	std::vector<int> y = RankSheepBasedOnDistTo(agent->position_t, (*env.sheepFlock));
//	
//	int k = 0; // sheepFlock while loop counter
//
//	while (neighborhoodList.size() < targetSizeOfNeighborhood)   // Loop over the sheepFlock using k until  neighborhoodList is filled with a number of sheep equal to target size of neigborhood
//	{
//		if ((y[k] <= targetSizeOfNeighborhood) && (y[k] > 0))  //check the distance rank of each sheep using y[k]. If card_Omega_pi_pi is equal to 3. Only sheep with distance rank as 1 to 3 will be added to the neighborhoodlist.
//															// which means closest 3 sheep. y[k] >0 will exclude the agent itself, as y starts from 0.
//		{
//			neighborhoodList.push_back((*env.sheepFlock)[k]);
//
//		}
//		k++;
//	}
//
//
//	return neighborhoodList;
//}

SheepList SenseSheepOutOfFlock(Agent* agent, Environment & env)
{
	//Each shepherd needs to check if the sheep in their neighbourhood are grouped or not.
	// 1. Each shepherd, j, needs to find the nearest n pi agents to form its neighbourhood at this time step,
	// 2. Each needs to calculate the centre of mass of the sheep in its neighbourhood.
	// 3. loop over the sheep and check the distance between the sheep and the local centre of mass.

	// 1. Each shepherd, j, needs to find the nearest n pi agents to form its neighbourhood at this time step,
	SheepList neighborhoodSheep = SenseSheepInNeighborhoodBasedOnNumber(agent, env.card_Omega_beta_pi, env); 	// identify sheep within neighborhod

	//SheepList neighborhoodSheep;
	//std::vector<int> y;

	//std::tie(neighborhoodSheep, y) = SenseSheepInNeighborhood(agent, env.card_Omega_beta_pi, env); 	// identify sheep within neighborhod

	// 2. Calculate the centre of mass of the sheep in its neighbourhood.

	if (neighborhoodSheep.size() != 0)
	{
		//calculate the LCM of those sheep
		Vector2f neighborhood_LCM = calculateLocalCentreOfMass(neighborhoodSheep); //Lambda_t // summing the positions and divide the results per the list size. The list doesn't include the sheep location itself.	
		agent->Lambda_t = neighborhood_LCM;

	}
	// 3. loop over the sheep and check the distance between the sheep and the local centre of mass.

	SheepList SheepOutOfFlockList = SheepList();
	/*std::vector<int> SheepOutOfFlockListRank;
	for (int i = 0; i < env.sheepFlock->size(); i++) {

		if ((agent->Lambda_t.dist((*env.sheepFlock)[i]->position_t) > env.fN))
		{
			SheepOutOfFlockList.push_back((*env.sheepFlock)[i]);
			
		}
	}*/

	std::vector<int> SheepOutOfFlockListRank;
	for (int i = 0; i < neighborhoodSheep.size(); i++) {

		if ((agent->Lambda_t.dist((neighborhoodSheep)[i]->position_t) > env.fN))
		{
			SheepOutOfFlockList.push_back((neighborhoodSheep)[i]);

		}
	}
	return SheepOutOfFlockList;
}

std::vector<int> RankSheepBasedOnDistTo(Vector2f pointP, SheepFlock mySheepList)
{

	std::vector<int> y (mySheepList.size());  //create an list of sheepFlock size to store current indices.

	std::vector<float> sheep_dist;
	// calculate the distance between this sheep and every other sheep
	for (int i = 0; i < mySheepList.size(); i++) {
		//(*env.sheepFlock)[i];
		float dist = pointP.dist((mySheepList)[i]->position_t);
		sheep_dist.push_back(dist);
	}


	std::iota(y.begin(), y.end(), 0);			//fill the list with sequentially increasing values  [first, last)

	//auto comparator = [&sheep_dist](int a, int b) { return sheep_dist[a] < sheep_dist[b]; };  //define the comparator that will be used for sorting : currently 

	std::sort(y.begin(), y.end(), [&sheep_dist](int i1, int i2) {return sheep_dist[i1] < sheep_dist[i2]; });   //sort list y based on comparing distances . as a result, y list will have rank of each sheep based on distance


	return y;
}


std::vector<int> RankSheepBasedOnDistTo(Vector2f pointP, SheepList mySheepList)
{

	std::vector<int> y(mySheepList.size());  //create an list of sheepFlock size to store current indices.

	std::vector<float> sheep_dist;
	// calculate the distance between this sheep and every other sheep
	for (int i = 0; i < mySheepList.size(); i++) {
		//(*env.sheepFlock)[i];
		float dist = pointP.dist((mySheepList)[i]->position_t);
		sheep_dist.push_back(dist);
	}


	//std::iota(y.begin(), y.end(), 0);			//fill the list with sequentially increasing values  [first, last)

	////auto comparator = [&sheep_dist](int a, int b) { return sheep_dist[a] < sheep_dist[b]; };  //define the comparator that will be used for sorting : currently 

	//std::sort(y.begin(), y.end(), [&sheep_dist](int i1, int i2) {return sheep_dist[i1] < sheep_dist[i2]; });   //sort list y based on comparing distances . as a result, y list will have rank of each sheep based on distance

	//auto y2 = sort_indexes(sheep_dist);
	y = sort_indexes(sheep_dist);
	return y;
}

//template <typename T>
//
//std::vector<size_t> sort_indexes(const std::vector<T> &v) {
//
//	// initialize original index locations
//	std::vector<size_t> idx(v.size());
//	iota(idx.begin(), idx.end(), 0);
//
//	// sort indexes based on comparing values in v
//	sort(idx.begin(), idx.end(),
//		[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });
//
//	return idx;
//}

template <typename T>

std::vector<int> sort_indexes(const std::vector<T> &v) {

	// initialize original index locations
	std::vector<int> idx(v.size());
	iota(idx.begin(), idx.end(), 0);

	// sort indexes based on comparing values in v
	sort(idx.begin(), idx.end(),
		[&v](size_t i1, size_t i2) {return v[i1] < v[i2]; });

	return idx;
}

float calc_regulated_force_magnitudeM1(float d1, float minD, float maxD, float ModulationDecayFactor)
		{
		    float maxDist_xAxis = maxD-minD; 

			//float decay_step = 5;
			float decay_step = ModulationDecayFactor;
			
			float modulation_factor = std::exp(-decay_step * d1 / maxDist_xAxis);

		    return modulation_factor;
		}

float calc_regulated_force_magnitudeM2(float d1, float minD, float maxD, int numAgents, float ModulationDecayFactor)
{
	float M1= calc_regulated_force_magnitudeM1(d1, minD, maxD, ModulationDecayFactor);
	//return (M1 / (float)numAgents);
	//return M1;
	return (M1 / (float)std::sqrt(numAgents));
}

SheepList SenseSheepOutOfFlockCentrally(Environment& env, Vector2f GCM)
{
	
	//loop over the sheep and check the distance between the sheep and the local centre of mass.

	SheepList SheepOutOfFlockList = SheepList();

	std::vector<int> SheepOutOfFlockListRank;
	for (int i = 0; i < env.sheepFlock->size(); i++) {
		
		if ((GCM.dist((*env.sheepFlock)[i]->position_t) > env.fN))
		{
			SheepOutOfFlockList.push_back((*env.sheepFlock)[i]);

		}
	}
	return SheepOutOfFlockList;
}