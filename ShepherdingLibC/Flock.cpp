#include"Flock.h"
#include "stdafx.h"
#include "Environment.h"
#include <random>
#include <math.h>
#include <string.h>
#include "Utilities.h"




//// <summary>
/// Initializes a new instance of the <see cref="SheepFlock"/> class.
/// </summary>
/// <param name="numSheepList">The number sheep list.</param>
/// <param name="xMin">The x minimum.</param>
/// <param name="xMax">The x maximum.</param>
/// <param name="yMin">The y minimum.</param>
/// <param name="yMax">The y maximum.</param>
/// <param name="startingID">Sheep starting identifier.</param>
/// <param name="pattern">Sheep distribution pattern P1 to P6.</param>
SheepFlock::SheepFlock(std::mt19937 generator, int numSheepList, float xMin, float xMax, float yMin, float yMax, int startingID, std::string pattern)
{
	
	std::string patternSubstring = pattern.substr(1, pattern.length());
	int patternID = std::stoi(patternSubstring);
	
	
	std::vector<vector<float>> allRs;
	//!> divide the x range into 5 regions, and the y range into 5 regions


	float xSpacing = (xMax - xMin) / 5;
	float ySpacing = (yMax - yMin) / 5;
		for (int j = 0; j < 5; j++)
			for (int i = 0; i < 5; i++) {
		{
			float Ri_xStart = xMin + i * xSpacing;
			float Ri_yStart = yMin + j * ySpacing;
			vector<float> Ri = { Ri_xStart ,  Ri_xStart +  xSpacing, Ri_yStart, Ri_yStart + ySpacing }; //ordered as xmin, xmax, ymin, ymax
			allRs.push_back(Ri);
		}
	}
		//!> Pick up the required squares to make the desired pattern
		//!> ---------------------
		//!> | 0 | 1 | 2 | 3 | 4 | 
		//!> ---------------------
		//!> | 5 | 6 | 7 | 8 | 9 |
		//!> ---------------------
		//!> | 10| 11| 12| 13| 14|
		//!> ---------------------
		//!> | 15| 16| 17| 18| 19| 
		//!> ---------------------
		//!> | 20| 21| 22| 23| 24| 
		//!> ---------------------
	std::vector<vector<float>> thisPatternRs;
	
	switch (patternID)
	{
	case 1: 
		//Pattern(P1)// all squares to be selected
		for (int i = 0; i < allRs.size(); i++)
		{
			thisPatternRs.push_back(allRs[i]);
		}
		break;

	case 2:
		
		//Pattern(P2)// condensed at middle top location
		thisPatternRs.push_back(allRs[1]);
		thisPatternRs.push_back(allRs[2]);
		thisPatternRs.push_back(allRs[3]);
		thisPatternRs.push_back(allRs[6]);
		thisPatternRs.push_back(allRs[7]);
		thisPatternRs.push_back(allRs[8]);

		break;

	case 3: 


		//Pattern(P3)// spaced at top  rows.
		thisPatternRs.push_back(allRs[1]);
		thisPatternRs.push_back(allRs[3]);
		thisPatternRs.push_back(allRs[10]);
		thisPatternRs.push_back(allRs[12]);
		thisPatternRs.push_back(allRs[14]);
		break;

	case 4:

		
		//Pattern(P4)// Wide Arrow pointing down.
		thisPatternRs.push_back(allRs[0]);
		thisPatternRs.push_back(allRs[4]);
		thisPatternRs.push_back(allRs[10]);
		thisPatternRs.push_back(allRs[14]);
		thisPatternRs.push_back(allRs[22]);

		break;
	case 5:


		//Pattern(P5)// Wide Arrow pointing up.
		thisPatternRs.push_back(allRs[2]);
		thisPatternRs.push_back(allRs[10]);
		thisPatternRs.push_back(allRs[14]);
		thisPatternRs.push_back(allRs[20]);
		thisPatternRs.push_back(allRs[24]);

		break;

	case 6:
	

			//Pattern(P6)// Corners only.
		thisPatternRs.push_back(allRs[0]);
		thisPatternRs.push_back(allRs[4]);
		thisPatternRs.push_back(allRs[20]);
		thisPatternRs.push_back(allRs[24]);

		break;
	/*
	default: printf("Choice other than 1, 2 and 3");
		break;*/
	}
	
	//std::random_device rd;     // only used once to initialise (seed) engine
	//std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<int> uni(0, thisPatternRs.size()-1); // guaranteed unbiased

	

	this->numSheepList = numSheepList;

	for (int i = 0; i < numSheepList; i++)
	{
		auto random_integer = uni(generator);
		std::vector<float> selectedInitializationArea = thisPatternRs[random_integer];
		//SheepAgent* sheep = new SheepAgent(xMin, xMax, yMin, yMax, i + startingID);
		std::uniform_real_distribution<float>  distribution1(selectedInitializationArea[0], selectedInitializationArea[1]);
		float x1 = distribution1(generator);
		std::uniform_real_distribution<float>  distribution2(selectedInitializationArea[2], selectedInitializationArea[3]);
		float y1 = distribution2(generator);

		//SheepAgent* sheep = new SheepAgent( generator, selectedInitializationArea[0], selectedInitializationArea[1], selectedInitializationArea[2], selectedInitializationArea[3], i + startingID);
		SheepAgent* sheep = new SheepAgent(x1,y1, i + startingID);

		this->push_back(sheep);
	}

}

void SheepFlock::CalcNewLoc()
{
	std::vector<SheepAgent*>::iterator sheepIter;
	for (sheepIter = this->begin(); sheepIter != this->end(); ++sheepIter) {
		(*sheepIter)->calculateSheepPositiont1();
	}
	//for (int i = 0; i < env.sheepFlock->size(); i++) {
	//	(*env.sheepFlock)[i]->calculateSheepPositiont1();
	//
	//}

}

void SheepFlock::Move()
{
	std::vector<SheepAgent*>::iterator sheepIter;
	for (sheepIter = this->begin(); sheepIter != this->end(); ++sheepIter) {
		(*sheepIter)->position_t.x = (*sheepIter)->position_t1.x;
		(*sheepIter)->position_t.y = (*sheepIter)->position_t1.y;
	}

}



///// <summary>
/// Initializes a new instance of the <see cref="SheepDogFlock"/> class.
/// </summary>
/// <param name="numSheepDogsList">The number sheep dogs list.</param>
/// <param name="xMin">The x minimum.</param>
/// <param name="xMax">The x maximum.</param>
/// <param name="yMin">The y minimum.</param>
/// <param name="yMax">The y maximum.</param>
/// <param name="startingID">The starting identifier.</param>
/// <param name="sheepDogAgentSpeed">The sheep dog agent speed.</param>
SheepDogFlock::SheepDogFlock(std::mt19937 generator,int numSheepDogsList, float xMin, float xMax, float yMin, float yMax, int startingID, float sheepDogAgentSpeed)
{
	this->numSheepDogsList = numSheepDogsList;
	//for sheep dog formation	
	//	Dog Id	Loc		Div % 2				Mod % 2			RefDogName		Direction derived based on Mod % 2			name derived based on location		RefDogIDdrived		RefDogID
	//					FLOOR(A4 / 2)		MOD(A4,2)						IF(Mod % 2 == 0, "L", "R")					CONCAT("C", Direction, Div % 2)			DogID-2
	//	1		C		0					1					-
	//	2		CL		1					0					C					L												CL1							fixed 1				1 //cannot be derived using the equation
	//	3		CR		1					1					C					R												CR1								1				1
	//	4		CL2		2					0					CL					L												CL2								2				2
	//	5		CR2		2					1					CR					R												CR2								3				3
	//	6		CL3		3					0					CL2					L												CL3								4				4
	//	7		CR3		3					1					CR2					R												CR3								5				5
	//	8		CL4		4					0					CL3					L												CL4								6				6
	//	9		CR4		4					1					CR3					R												CR4								7				7

	//RefDogID = DogID-2 for all dogid>2
	//Direction from the RefDogID = IF(Mod(DogID,2) == 0, "L", "R")	 for all dogid >1
	//name derived based on location CONCAT("C", Direction, Div % 2) for all dogid >1

	Environment& env = Environment::getInstance();
	int mode = 0;  // initially assume single sheepDog
	if (env.M > 1) // If more than one sheepDog, then operate in multi-sheepdog Mode
		mode = 1;
	std::uniform_real_distribution<float> distribution1(xMin, xMax);
	std::uniform_real_distribution<float>  distribution2(yMin, yMax);

	for (int i = 0; i < numSheepDogsList; i++)
	{
		int thisSheepDogID = i + startingID;
		//std::uniform_int_distribution<int> distribution1(xMin, xMax);
		float x1 = distribution1(generator);
		//std::uniform_int_distribution<int> distribution2(yMin, yMax);
		float y1 = distribution2(generator);

		//SheepDogAgent* sheepDog = new SheepDogAgent( generator, xMin, xMax, yMin, yMax, thisSheepDogID, sheepDogAgentSpeed, mode);
		SheepDogAgent* sheepDog = new SheepDogAgent(x1, y1, thisSheepDogID, sheepDogAgentSpeed, mode);

		this->push_back(sheepDog);

		SheepDogRosterDatarow RosterRow;
		RosterRow.dogID = thisSheepDogID;
		RosterRow.dogAssignedTask = "Driving";
		env.SheepDogRoster.push_back(RosterRow);
		
		if (thisSheepDogID == 1) //Central Sheep C
		{
			expectedDrivingKnowledgePerSheepdog row;
			row.dogID= thisSheepDogID;
			row.dogName="C";
			//row.goalLoc=env.PG;
			row.GCM=Vector2f();
			//row.furthestSheepID = -1;
			row.dogCurrentLocation = sheepDog->position_t;
			env.sheepdogsSharedDrivingKnowledge.push_back(row);

		}
		else if(thisSheepDogID == 2) 
		{
			expectedDrivingKnowledgePerSheepdog row;
			row.dogID = thisSheepDogID;
			row.dogName = "CL";
			row.RefDogID=1;
			//row.furthestSheepID = -1;
			row.dogLocationRelevant2RefDog="L";
			//row.goalLoc = env.PG;
			row.GCM = Vector2f();
			row.dogCurrentLocation = sheepDog->position_t;
			env.sheepdogsSharedDrivingKnowledge.push_back(row);
		}
		else
		{
			expectedDrivingKnowledgePerSheepdog row;
			row.dogID = thisSheepDogID;

			row.RefDogID = row.dogID - 2;//RefDogID = DogID-2 for all dogid>2
			//row.dogID = thisSheepDogID;
			//row.furthestSheepID = -1;
			if (std::fmodf(row.dogID, 2) == 0)//Direction from the RefDogID is IF(Mod(DogID,2) == 0, "L", "R")	 for all dogid >1
			{
				row.dogLocationRelevant2RefDog = "L";
			}
			else if (std::fmodf(row.dogID, 2) == 1) 
			{

				row.dogLocationRelevant2RefDog = "R" ;
			}
			row.dogName = std::string("C")+ row.dogLocationRelevant2RefDog + std::to_string(std::floor(row.dogID/2)) ;			//name derived based on location CONCAT("C", Direction, Div % 2) for all dogid >1
			//row.goalLoc = env.PG;
			row.dogCurrentLocation = sheepDog->position_t;

			row.GCM = Vector2f();
			env.sheepdogsSharedDrivingKnowledge.push_back(row);
		}
	}
	//int selectedSheepID = env.M + 1;
	//int numSheepPerSheepDog = std::floor(env.N / env.M); //Div
	//int numSheepPerSheepDogRem = (env.N % env.M); //Mod;
	//for (int i = 0; i < numSheepDogsList; i++)
	//{			vector<int> sheepsToBeAssigned =  vector<int>();

	//	int thisSheepDogID = i + startingID;
	//	if (thisSheepDogID <= numSheepPerSheepDogRem) //assign numSheepPerSheepDog+1
	//	{
	//		for (int j = 0; j < numSheepPerSheepDog + 1; j++)
	//		{
	//			sheepsToBeAssigned.push_back(selectedSheepID);
	//			selectedSheepID++;

	//		}
	//	} 
	//	else // assign numSheepPerSheepDog
	//	{
	//		for (int j = 0; j < numSheepPerSheepDog + 1; j++)
	//		{
	//			sheepsToBeAssigned.push_back(selectedSheepID);
	//			selectedSheepID++;
	//		}
	//	}

		//env.conflictResolution.push_back(sheepsToBeAssigned);

	
	//}

}

void SheepDogFlock::CalcNewLoc()
{
	//before we calculate the next position location, we need to update the shared information among the sheepdogs. 

	//For now, as we don't have communication, we calculate the required information centrally. we need to update the table with the sheepdog locations, the current GCM, and the current furthest sheepdog.
	
	Environment& env = Environment::getInstance();

	Vector2f GCM = calculateGloablCentreOfMass(env.sheepFlock);
	int furthestSheepFromGCM_ID=-1;
	SheepList sheepOutOfFlock = SenseSheepOutOfFlockCentrally( env,  GCM);
	
	int firstSheepDogNotCollectingID = 1;
	env.sheepdogsSharedCollectingKnowledge.clear();
	env.SheepDogRoster.clear();
	env.sheepdogsSharedDrivingKnowledge.clear();

	if (sheepOutOfFlock.size() > 0) //if this list is not empty, then find the furthest sheep from the group.
	{
		int i = 0;
		while ((i < env.sheepDogFlock->size()) && (sheepOutOfFlock.size() > 0))
		{
			expectedCollectingKnowledgePerSheepdog sheepdogsSharedCollectingKnowledge_DataRow;
			std::vector<int> y = RankSheepBasedOnDistTo((*env.sheepDogFlock)[i]->position_t, sheepOutOfFlock);
			sheepdogsSharedCollectingKnowledge_DataRow.AssignedSheepID= sheepOutOfFlock[y[0]]->agentID;
			sheepdogsSharedCollectingKnowledge_DataRow.AssignedSheepLoc=sheepOutOfFlock[y[0]]->position_t;
			sheepdogsSharedCollectingKnowledge_DataRow.dogID = (*env.sheepDogFlock)[i]->agentID;
			sheepdogsSharedCollectingKnowledge_DataRow.GCM = GCM;
			sheepOutOfFlock.erase(sheepOutOfFlock.begin() + y[0]);
			firstSheepDogNotCollectingID++;
			env.sheepdogsSharedCollectingKnowledge.push_back(sheepdogsSharedCollectingKnowledge_DataRow);
			SheepDogRosterDatarow RosterRow;
			RosterRow.dogID = (*env.sheepDogFlock)[i]->agentID;
			RosterRow.dogAssignedTask = "Collecting";
			env.SheepDogRoster.push_back(RosterRow);	
			i++;
		}
	}
	//AllSheepDog that are not collecting will be assigned a driving role.

	for (int i = firstSheepDogNotCollectingID - 1; i < env.sheepDogFlock->size(); i++)
	{
		SheepDogRosterDatarow RosterRow;
		RosterRow.dogID = (*env.sheepDogFlock)[i]->agentID;
		RosterRow.dogAssignedTask = "Driving";
		env.SheepDogRoster.push_back(RosterRow);

		if (firstSheepDogNotCollectingID-i == 1) //Central Sheep C
		{
			expectedDrivingKnowledgePerSheepdog row;
			row.dogID = i+1;
			row.dogName = "C";
			row.GCM = GCM;
			row.dogCurrentLocation = (*env.sheepDogFlock)[i]->position_t;

			env.sheepdogsSharedDrivingKnowledge.push_back(row);

		}
		else if (firstSheepDogNotCollectingID - i == 0)
		{
			expectedDrivingKnowledgePerSheepdog row;
			row.dogID = i+1;
			row.dogName = "CL1";
			row.RefDogID = firstSheepDogNotCollectingID;
			row.dogLocationRelevant2RefDog = "L";
			row.dogCurrentLocation = (*env.sheepDogFlock)[i]->position_t;

			row.GCM = GCM;
			env.sheepdogsSharedDrivingKnowledge.push_back(row);
		}
		else
		{
			expectedDrivingKnowledgePerSheepdog row;
			row.dogID = i+1;

			row.RefDogID = row.dogID - 2;//RefDogID = DogID-2 for all dogid>2

			if (std::fmodf(row.dogID, 2) == 0)//Direction from the RefDogID is IF(Mod(DogID,2) == 0, "L", "R")	 for all dogid >1
			{
				row.dogLocationRelevant2RefDog = "L";
			}
			else if (std::fmodf(row.dogID, 2) == 1)
			{

				row.dogLocationRelevant2RefDog = "R";
			}
			row.dogName = std::string("C") + row.dogLocationRelevant2RefDog + std::to_string(int(std::floor(row.dogID / 2)));			//name derived based on location CONCAT("C", Direction, Div % 2) for all dogid >1
			row.dogCurrentLocation = (*env.sheepDogFlock)[i]->position_t;

			row.GCM = GCM;
			env.sheepdogsSharedDrivingKnowledge.push_back(row);
		}
	}
	//std::vector<expectedCollectingKnowledgePerSheepdog> sheepdogsSharedKnowledge = env.sheepdogsSharedKnowledge;

	//for (KnowledgePerSheepdog = (env.sheepdogsSharedKnowledge).begin(); KnowledgePerSheepdog != (env.sheepdogsSharedKnowledge).end(); ++KnowledgePerSheepdog) {
	//	KnowledgePerSheepdog->GCM = GCM;
	//	KnowledgePerSheepdog->dogCurrentLocation = (*env.sheepDogFlock)[KnowledgePerSheepdog->dogID - 1]->position_t; //DogIDs start from 1 while the vector index starts from zero. Therefore, we access the corresponding dog, and retrieve its position and make it available to all other dogs.
	//	KnowledgePerSheepdog->furthestSheepID = furthestSheepFromGCM_ID;
	//}


	// this is where we call the calculate next position location
	std::vector<SheepDogAgent*>::iterator sheepDogIter;
	for (sheepDogIter = this->begin(); sheepDogIter != this->end(); ++sheepDogIter) {
		(*sheepDogIter)->calculateSheepDogPositiont1();
	}


}



void SheepDogFlock::Move()
{
	

	

	std::vector<SheepDogAgent*>::iterator sheepDogIter;
	for (sheepDogIter = this->begin(); sheepDogIter != this->end(); ++sheepDogIter) {
		(*sheepDogIter)->position_t.x = (*sheepDogIter)->position_t1.x;
		(*sheepDogIter)->position_t.y = (*sheepDogIter)->position_t1.y;
	}
}





//
//Flock::Flock()
//{
//	this->numSheepList = 1;
//	this->numSheepDogsList = 1;
//
//	SheepAgent* sheep = new SheepAgent(0, 0, 100, 100,1);
//	SheepDogAgent* sheepDog = new SheepDogAgent(0, 0, 100, 100,2);
//
//	this->sheepList.push_back(sheep);
//	this->sheepDogsList.push_back(sheepDog);
//
//}
//
//
//Flock::Flock(int numSheepList, int numSheepDogsList, int xMin, int xMax, int yMin, int yMax)
//{
//	this->numSheepList = numSheepList;
//	this->numSheepDogsList = numSheepDogsList;
//
//	for (int i = 0; i < numSheepList; i++)
//	{
//		SheepAgent* sheep = new SheepAgent(xMin, xMax, yMin, yMax,i+1);
//		this->sheepList.push_back(sheep);
//	}
//	for (int i = 0; i < numSheepDogsList; i++)
//	{
//		SheepDogAgent* sheepDog = new SheepDogAgent(xMin, xMax, yMin, yMax,i+1+ numSheepList);
//		this->sheepDogsList.push_back(sheepDog);
//	}
//
//
//}

//void Flock::updateLoc()
//{
//	//std::list<SheepAgent*>::iterator sheepIter;
//	for (int i = 0; i < sheepList.size(); i++)
//	{
//		sheepList[i]->calculateSheepPositiont1();
//		//sheepList[i]->position_t.x = sheepList[i]->position_t1.x;
//		//sheepList[i]->position_t.y = sheepList[i]->position_t1.y;
//
//	}
//	for (int i = 0; i < sheepDogsList.size(); i++)
//	{
//		sheepDogsList[i]->calculateSheepDogPositiont1();
//		//sheepDogsList[i]->position_t.x = sheepDogsList[i]->position_t1.x;
//		//sheepDogsList[i]->position_t.y = sheepDogsList[i]->position_t1.y;
//
//	}
//	for (int i = 0; i < sheepDogsList.size(); i++)
//	{
//		sheepDogsList[i]->position_t.x = sheepDogsList[i]->position_t1.x;
//		sheepDogsList[i]->position_t.y = sheepDogsList[i]->position_t1.y;
//
//	}
//
//	for (int i = 0; i < sheepList.size(); i++)
//	{
//		sheepList[i]->position_t.x = sheepList[i]->position_t1.x;
//		sheepList[i]->position_t.y = sheepList[i]->position_t1.y;
//	}
//
//
//}