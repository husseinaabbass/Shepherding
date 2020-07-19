// ShepherdingSimC_V1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <string> 
#include"Visualization.h"
#include "CLI.h"
#include "ShepherdingSimC_V1.h"
#include <tchar.h>
#include <comutil.h>
#include <comdef.h>
#include <fstream>

#include <stdio.h>
#include <tchar.h>
#import <msxml6.dll>



Visualization *graphics = nullptr;


int randomNumberSeed = 0;
int screenWidthPixels = 800, screenHeightPixels = 800;
int MaximumNumSteps = 1000;
bool visualizationON = false;
bool CircularPathPlanningON = false;
int R3 = 4;
int R2 = 4;
int DrivingPositionEq = 1;
int CollectingPositionEq = 1;
int SheepNeignborhoodSelection = 1;
int ModulationDecayFactor = 1;
int fNequation = 1;
int ForceRegulated = 1;
bool StallingON = false;
float StallingDistance = 0;
//int CircularPathPlanningRadius = 12;
//int CircularPathPlanningMode = 0; //0  for fixed radius, and 1 for distance to the furthest sheep

int FieldLength = 100;		//Actual Length and Width of Field 
int simScreenWidth = 120;		//Actual Length and Width of window including surrounding the field
int simSpeed = 100; //wait x visualisation step before calling simulation update
int goalRadius = 10;
int WindowMarginSize = 0;
// use 1:veryfast(actual) 10:fast 100:slow speed


int gLocX = 0;
int gLocY = 0;

int sheepInitializationStartingX, sheepInitializationStartingY, sheepInitializationXRange, sheepInitializationYRange;
std::string sheepInitializationPattern;
int sheepDogInitializationStartingX, sheepDogInitializationStartingY, sheepDogInitializationXRange, sheepDogInitializationYRange;


int N=10;					//(1--201)           & Cardinality of Pi
int M=1;					// (1--20)            & Cardinality of B
bool paddockON = false;
int paddockLength = N+10;
int paddockWidth = N+10;
float R_pi_beta=65;			// (65u)			& pi sensing range for beta
float Ra_pi_pi=2;//			// (2u)				& pi collision avoidance range for pi
float Rs_pi_pi = 20;//			// (20u)				& pi sensing range for pi
float R_beta_beta = 10;// 10			// (2u)				& beta sensing range for beta
float R_beta_pi = 65; //									& beta sensing range for pi
int card_Omega_pi_pi =N-1; //maximum N-1
int card_Omega_beta_pi = N ;  //maximum N
float W_pi_pi=2;			// (2)				& pi repulsion strength from pi
float W_beta_beta = 2;
float W_pi_beta=1;		// (1)				& pi repulsion strength from beta
float W_pi_Lambda=1.05;		// (1.05)			& pi attraction strength to Lambda
float W_pi_upsilon=0.5;	// (0.5)			& Strength of pi previous direction
float W_e_pi_i=0.3;		// (0.3)			& Strength of sheep pi_j angular noise
float W_e_beta_j=0.3;		// (0.3)			& Strength of shepherd beta_j angular noise
float S_t_beta_j = 2;		//						&Speed of beta at time t
float eta = 0.05;					//(0.05)			& Probability of moving per time step while grazing
float obstaclesRadius = 1;
float obstaclesDensity = 0;

bool CollisionAvoidanceOpponentsForceON = true;
bool CollisionAvoidanceFriendsForceON = true;
bool AttractionBehaviorForceON = true;
bool CollisionAvoidanceStaticObstaclesForceON = true;
bool JitteringForceON = true;
bool scaleForceVisualization = true;

int main(int argc, char *argv[])
{

	std::string ConfigFile = "../InputFiles/config.xml"; //set the default configuration1;;11 file name
	std::string GraphicFile = "../InputFiles/VisualizationOptions.xml"; //set the default filename
	if (argc>1)
	{
		ConfigFile = argv[1]; //if a new configuration file name is given then update the ConfigFile name
	}
	for (int i = 1; i < argc; i++)
		printf("Argument %d: %s\n", (i + 1), argv[i]);
	
	HRESULT hr = CoInitialize(NULL);
	if (SUCCEEDED(hr))
	{
		
		loadDOMConfiguration(ConfigFile);
		loadDOMGraphics(GraphicFile);
		CoUninitialize();
	}
	int scaleCalc = screenWidthPixels / simScreenWidth;

	int screenWIDTH = simScreenWidth, screenHEIGHT = simScreenWidth;

	int fieldWidth = FieldLength, fieldHeight = FieldLength;
	
	const int size = 1+ (N+M) * 4;  //writingOutput numOfColumns 1 column for time step , then (N+M)*4 : 2 fields for current position, and 2 fields for velocity.
	
	//std::vector<int[size]> output;
//	std::vector<std::list<float>> DataOUT;
	std::ofstream output_file(std::string("./")+ ConfigFile.substr(0, ConfigFile.length()-4)+std::string("_OutPutData.csv"));
	std::ofstream outputHeader_file(std::string("./") + ConfigFile.substr(0, ConfigFile.length() - 4) + std::string("_OutPutDataHeader.csv"));
	std::ofstream outputConfigfile(std::string("./") + ConfigFile.substr(0, ConfigFile.length() - 4) + std::string("_RunConfigurationSaved.txt"));
	std::ofstream outputCompletionTimefile(std::string("./") + ConfigFile.substr(0, ConfigFile.length() - 4) + std::string("_CompletionTimeOnly.txt"));
	std::ofstream StaticObstaclesOutputFile(std::string("./") + ConfigFile.substr(0, ConfigFile.length() - 4) + std::string("_StaticObstaclesOutputFile.csv"));

	WriteOutFiles( outputHeader_file,   outputConfigfile);
	

	if (visualizationON)
	{
		graphics = new Visualization();
		
		graphics->init(randomNumberSeed,std::string("Shepherding Simulation")+ConfigFile.substr(0, ConfigFile.length() - 4), scaleCalc, simSpeed, screenWIDTH, screenHEIGHT, fieldWidth, fieldHeight, N, M, R_pi_beta, Ra_pi_pi, Rs_pi_pi, R_beta_beta, R_beta_pi, W_pi_pi, W_beta_beta, W_pi_beta, W_pi_Lambda, W_pi_upsilon, W_e_pi_i, W_e_beta_j, S_t_beta_j, eta, card_Omega_pi_pi, card_Omega_beta_pi, WindowMarginSize + gLocX, WindowMarginSize + gLocY, paddockLength, paddockWidth, paddockON, CircularPathPlanningON,StallingON, StallingDistance, R2, R3, goalRadius, ForceRegulated, fNequation, DrivingPositionEq, CollectingPositionEq, SheepNeignborhoodSelection, ModulationDecayFactor, sheepInitializationStartingX+ WindowMarginSize, sheepInitializationStartingY+ WindowMarginSize, sheepInitializationXRange, sheepInitializationYRange, sheepInitializationPattern, sheepDogInitializationStartingX+ WindowMarginSize, sheepDogInitializationStartingY+ WindowMarginSize, sheepDogInitializationXRange, sheepDogInitializationYRange, MaximumNumSteps, obstaclesDensity, obstaclesRadius, CollisionAvoidanceOpponentsForceON, CollisionAvoidanceFriendsForceON, AttractionBehaviorForceON, CollisionAvoidanceStaticObstaclesForceON, JitteringForceON, scaleForceVisualization);
		graphics->render();

		WriteObstaclesFiles(StaticObstaclesOutputFile);

		while (graphics->running()) //while running
		{
			// Process events
			graphics->handleEvents();
			graphics->update(output_file, outputCompletionTimefile); //both update and writing
			graphics->render();
			//graphics->WriteDataOUT();
		}
		graphics->clean();
	}
	else
	{

		CLI *cli = nullptr;

		cli = new CLI();
		cli->init(randomNumberSeed,  fieldWidth, fieldHeight, N, M, R_pi_beta, Ra_pi_pi, Rs_pi_pi, R_beta_beta,  R_beta_pi, W_pi_pi, W_beta_beta, W_pi_beta, W_pi_Lambda, W_pi_upsilon, W_e_pi_i, W_e_beta_j, S_t_beta_j, eta, card_Omega_pi_pi, card_Omega_beta_pi, gLocX, gLocY, paddockLength, paddockWidth, paddockON, CircularPathPlanningON, StallingON, StallingDistance, R2, R3, goalRadius, ForceRegulated, fNequation, DrivingPositionEq, CollectingPositionEq, SheepNeignborhoodSelection, ModulationDecayFactor, sheepInitializationStartingX, sheepInitializationStartingY, sheepInitializationXRange, sheepInitializationYRange, sheepInitializationPattern, sheepDogInitializationStartingX, sheepDogInitializationStartingY, sheepDogInitializationXRange, sheepDogInitializationYRange, MaximumNumSteps, obstaclesDensity, obstaclesRadius);
		WriteObstaclesFiles(StaticObstaclesOutputFile);

		while (cli->running()) //while running
		{
			// Process events
			cli->handleEvents();
			cli->update();
			cli->streamOut(output_file, outputCompletionTimefile);
			//DataOUT.push_back(cli->streamOut());
			
		}
		

		//NoVisualizationSimulationCall();
	}
	return 0;

}


void WriteOutFiles(std::ofstream & outputHeader_file, std::ofstream&  outputConfigfile)
{
	//write config out

	//outputConfigfile << "Visualisation : " << visualizationON ? "true" : "false" << std::endl;
	outputConfigfile << "Random Numbers Seed : " << randomNumberSeed << std::endl;
	outputConfigfile << "Visualisation : " << visualizationON << std::endl;
	outputConfigfile << "Simulation Speed: " << simSpeed << std::endl;
	outputConfigfile << "ScreenWidth in Pixels: " << screenWidthPixels << std::endl;
	outputConfigfile << "Screen Height in Pixels: " << screenHeightPixels << std::endl;
	outputConfigfile << "Field Length and Width: " << FieldLength << std::endl;
	outputConfigfile << "Goal LocationX: " << gLocX << std::endl;
	outputConfigfile << "Goal LocationT: " << gLocY << std::endl;
	//outputConfigfile << "Paddock On : " << paddockON ? "true" : "false" << std::endl;
	outputConfigfile << "Paddock On : " << paddockON  << std::endl;
	outputConfigfile << "Paddock Length: " << paddockLength << std::endl;
	outputConfigfile << "paddock Width: " << paddockWidth << std::endl;
	outputConfigfile << "Goal Radius: " << goalRadius << std::endl;
	outputConfigfile << "N: " << N << std::endl;
	outputConfigfile << "M: " << M << std::endl;
	outputConfigfile << "R_pi_beta: " << R_pi_beta << std::endl;
	outputConfigfile << "Ra_pi_pi: " << Ra_pi_pi << std::endl;
	outputConfigfile << "Rs_pi_pi: " << Rs_pi_pi << std::endl;
	outputConfigfile << "card_Omega_pi_pi: " << card_Omega_pi_pi << std::endl;
	outputConfigfile << "card_Omega_beta_pi: " << card_Omega_beta_pi << std::endl;
	outputConfigfile << "W_pi_pi: " << W_pi_pi << std::endl;
	outputConfigfile << "W_pi_beta: " << W_pi_beta << std::endl;
	outputConfigfile << "W_pi_Lambda: " << W_pi_Lambda << std::endl;
	outputConfigfile << "W_pi_upsilon: " << W_pi_upsilon << std::endl;
	outputConfigfile << "W_e_pi_i: " << W_e_pi_i << std::endl;
	outputConfigfile << "W_e_beta_j: " << W_e_beta_j << std::endl;
	outputConfigfile << "S_t_beta_j: " << S_t_beta_j << std::endl;
	outputConfigfile << "eta: " << eta << std::endl;
	outputConfigfile << "R_beta_beta: " << R_beta_beta << std::endl;
	outputConfigfile << "R_beta_pi: " << R_beta_pi << std::endl;
	outputConfigfile << "W_beta_beta: " << W_beta_beta << std::endl;
	//outputConfigfile << "Circular Path Planning On : " << circularPathPlanningON ? "true" : "false" << std::endl;
	outputConfigfile << "DrivingPositionEq"<< DrivingPositionEq << std::endl;
	outputConfigfile << "CollectingPositionEq"<< CollectingPositionEq << std::endl;
	outputConfigfile << "fNequation" << fNequation << std::endl;
	outputConfigfile << "Circular Path Planning On : " << CircularPathPlanningON << std::endl;
	outputConfigfile << "StallingON : " << StallingON << std::endl;
	outputConfigfile << "StallingDistance : " << StallingDistance << std::endl;
	outputConfigfile << "ForceRegulated" << ForceRegulated << std::endl;
	outputConfigfile << "SheepNeignborhoodSelection"<< SheepNeignborhoodSelection << std::endl;
	outputConfigfile << "ModulationDecayFactor"<< ModulationDecayFactor << std::endl;
	outputConfigfile << "R2 : " << R2 << std::endl;
	outputConfigfile << "R3 : " << R3 << std::endl;
	outputConfigfile << "sheepInitializationStartingX: " << sheepInitializationStartingX << std::endl;
	outputConfigfile << "sheepInitializationStartingX: " << sheepInitializationStartingX << std::endl;
	outputConfigfile << "sheepInitializationXRange: " << sheepInitializationXRange << std::endl;
	outputConfigfile << "sheepInitializationYRange: " << sheepInitializationYRange << std::endl;
	outputConfigfile << "sheepInitializationPattern: " << sheepInitializationPattern << std::endl;
	outputConfigfile << "sheepDogInitializationStartingX: " << sheepDogInitializationStartingX << std::endl;
	outputConfigfile << "sheepDogInitializationStartingY: " << sheepDogInitializationStartingX << std::endl;
	outputConfigfile << "sheepDogInitializationXRange: " << sheepDogInitializationXRange << std::endl;
	outputConfigfile << "sheepDogInitializationYRange: " << sheepDogInitializationYRange << std::endl;
	outputConfigfile << "ObstaclesDensity: " << obstaclesDensity << std::endl;
	outputConfigfile << "ObstaclesRadius: " << obstaclesRadius << std::endl;
	

	outputHeader_file << "TimeStep,";

	for (int i = 0; i < M; i++)
	{
		outputHeader_file << "SheepDogID,";
		outputHeader_file << "SheepDogPositionX,";
		outputHeader_file << "SheepDogPositionY,";
		outputHeader_file << "SheepDogPositionVelocityX,";
		outputHeader_file << "SheepDogPositionVelocityY,";
		outputHeader_file << "SheepDogCurrentMode,";
		outputHeader_file << "Role,";
	}

	for (int i = 0; i < N; i++)
	{
		outputHeader_file << "SheepID,";
		outputHeader_file << "SheepPositionX,";
		outputHeader_file << "SheepPositionY,";
		outputHeader_file << "SheepPositionVelocityX,";
		outputHeader_file << "SheepPositionVelocityY,";
		outputHeader_file << "Sheep_F_pi_i_beta_j_X,";
		outputHeader_file << "Sheep_F_pi_i_beta_j_Y,";
		outputHeader_file << "Sheep_F_pi_i_Lambda_X,";
		outputHeader_file << "Sheep_F_pi_i_Lambda_Y,";
		outputHeader_file << "Sheep_F_pi_i_pi_i_X,";
		outputHeader_file << "Sheep_F_pi_i_pi_i_Y,";

		
	}

	

}
void WriteObstaclesFiles(std::ofstream& ObstaclesOutputFile)
{
	Environment& env = Environment::getInstance();
	for (int i = 0; i < env.terrain.staticObstacles->size(); i++) {

		ObstaclesOutputFile << (*env.terrain.staticObstacles)[i]->position_t.x << ",";
		ObstaclesOutputFile << (*env.terrain.staticObstacles)[i]->position_t.y << ",";
		ObstaclesOutputFile << (*env.terrain.staticObstacles)[i]->radius << std::endl;


	}
}

// Helper function to create a VT_BSTR variant from a null terminated string. 
HRESULT VariantFromString(PCWSTR wszValue, VARIANT &Variant)
{
	HRESULT hr = S_OK;
	BSTR bstr = SysAllocString(wszValue);
	CHK_ALLOC(bstr);

	V_VT(&Variant) = VT_BSTR;
	V_BSTR(&Variant) = bstr;

CleanUp:
	return hr;
}

// Helper function to create a DOM instance. 
HRESULT CreateAndInitDOM(IXMLDOMDocument **ppDoc)
{
	HRESULT hr = CoCreateInstance(__uuidof(MSXML2::DOMDocument60), NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(ppDoc));

	if (SUCCEEDED(hr))
	{
		// these methods should not fail so don't inspect result
		(*ppDoc)->put_async(VARIANT_FALSE);
		(*ppDoc)->put_validateOnParse(VARIANT_FALSE);
		(*ppDoc)->put_resolveExternals(VARIANT_FALSE);
	}
	return hr;
}

HRESULT ReportParseError(IXMLDOMDocument *pDoc, char *szDesc)
{
	HRESULT hr = S_OK;
	HRESULT hrRet = E_FAIL; // Default error code if failed to get from parse error.
	IXMLDOMParseError *pXMLErr = NULL;
	BSTR bstrReason = NULL;

	CHK_HR(pDoc->get_parseError(&pXMLErr));
	CHK_HR(pXMLErr->get_errorCode(&hrRet));
	CHK_HR(pXMLErr->get_reason(&bstrReason));
	printf("%s\n%S\n", szDesc, bstrReason);

CleanUp:
	SAFE_RELEASE(pXMLErr);
	SysFreeString(bstrReason);
	return hrRet;
}

void loadDOMConfiguration(std::string filename)
{
	HRESULT hr = S_OK;
	IXMLDOMDocument *pXMLDom = NULL;
	IXMLDOMParseError *pXMLErr = NULL;

	BSTR bstrXML = NULL;
	BSTR bstrErr = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;
	VariantInit(&varFileName);

	CHK_HR(CreateAndInitDOM(&pXMLDom));

	// XML file name to load

	CHK_HR(VariantFromString(SysAllocString(std::wstring(filename.begin(), filename.end()).c_str()), varFileName));

	//	CHK_HR(VariantFromString(inputFileName, varFileName));

	CHK_HR(pXMLDom->load(varFileName, &varStatus));
	if (varStatus == VARIANT_TRUE)
	{
		CHK_HR(pXMLDom->get_xml(&bstrXML));
		printf("XML was successfully loaded\n");
		BSTR bstrNodeName = NULL;
		BSTR bstrNodeValue = NULL;
		IXMLDOMNode *pNode = NULL;

		// Query a node-set.
		BSTR bstrQuery2 = NULL;
		IXMLDOMNodeList *pNodes = NULL;

		//Reading Visualisation configuration
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[1]/*"), &pNodes));
		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		randomNumberSeed = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);

		//Reading Visualisation configuration
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[2]/*"), &pNodes));
		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));

		if (0 == wcscmp(bstrNodeValue, L"1")) //A zero value indicates that both are considered equal.
	//		if (bstrNodeValue == SysAllocString(L"1"))
		{
			visualizationON = true;
		}
		else
		{
			visualizationON = false;

		}

		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);

		
		//Reading Field Configuration
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[3]/*"), &pNodes));
		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		FieldLength = _wtoi(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(1, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		WindowMarginSize = _wtoi(bstrNodeValue);
		simScreenWidth = FieldLength + 2 * WindowMarginSize;
		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);


		//Reading Goal Location
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[4]/*"), &pNodes));
		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		gLocX = _wtoi(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(1, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);

		gLocY = _wtoi(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);


		//Reading "Paddock Dimension"
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[5]/*"), &pNodes));
		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		if (0 == wcscmp(bstrNodeValue, L"1")) //A zero value indicates that both are considered equal.
//			if (bstrNodeValue == SysAllocString(L"1"))
		{
			paddockON = true;
		}
		else
		{
			paddockON = false;
		}
		SysFreeString(bstrNodeValue);



		CHK_HR(pNodes->get_item(1, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		goalRadius = _wtoi(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(2, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		paddockLength = _wtoi(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(3, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		paddockWidth = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);


		//Reading "Shepherding Model Configuration""
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[6]/*"), &pNodes));

		//Reading "Driving Equation Selection"
		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		DrivingPositionEq = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		//Reading "Collecting Equation Selection"

		CHK_HR(pNodes->get_item(1, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		CollectingPositionEq = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		//Reading "fNequation"

		CHK_HR(pNodes->get_item(2, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		fNequation = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		//Reading "StallingON"

		CHK_HR(pNodes->get_item(3, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		if (0 == wcscmp(bstrNodeValue, L"1")) //A zero value indicates that both are considered equal.
//			if (bstrNodeValue == SysAllocString(L"1"))
		{
			StallingON = true;
		}
		else
		{
			StallingON = false;
		}
		SysFreeString(bstrNodeValue);

		//Reading "StallingDistance"

		CHK_HR(pNodes->get_item(4, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		StallingDistance = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		//Reading Circular Path Planning Configuration
		CHK_HR(pNodes->get_item(5, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));

		if (0 == wcscmp(bstrNodeValue, L"1")) //A zero value indicates that both are considered equal.
		{

			CircularPathPlanningON = true;
		}
		else
		{
			CircularPathPlanningON = false;
		}

		SysFreeString(bstrNodeValue);

		//Reading SheepNeignborhoodSelection
		CHK_HR(pNodes->get_item(6, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		SheepNeignborhoodSelection = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		//Reading R3
		CHK_HR(pNodes->get_item(7, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		R3 = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		//Reading R2
		CHK_HR(pNodes->get_item(8, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		R2 = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		

		//Reading ForceRegulated
		CHK_HR(pNodes->get_item(9, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		ForceRegulated = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		//Reading ModulationDecayFactor
		CHK_HR(pNodes->get_item(10, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		ModulationDecayFactor = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);

		//Reading "Shepherding Parameters"
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[7]/*"), &pNodes));
		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		N = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(1, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		M = _wtoi(bstrNodeValue);

		CHK_HR(pNodes->get_item(2, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		R_pi_beta = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(3, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		Ra_pi_pi = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(4, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//printf("\t%S\n", bstrNodeValue);
		Rs_pi_pi = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);


		CHK_HR(pNodes->get_item(5, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		card_Omega_pi_pi = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(6, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		card_Omega_beta_pi = _wtoi(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(7, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		W_pi_pi = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(8, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		W_pi_beta = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(9, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		W_pi_Lambda = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(10, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		W_pi_upsilon = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(11, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		W_e_pi_i = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(12, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		W_e_beta_j = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(13, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		S_t_beta_j = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(14, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		eta = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(15, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		R_beta_beta = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(16, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		R_beta_pi = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		CHK_HR(pNodes->get_item(17, &pNode));
		CHK_HR(pNode->get_text(&bstrNodeValue));
		W_beta_beta = std::stof(bstrNodeValue);
		SysFreeString(bstrNodeValue);

		

		SAFE_RELEASE(pNode);

		

		/*SysFreeString(bstrNodeValue);
		
		CHK_HR(pNodes->get_item(2, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		CircularPathPlanningRadius= _wtoi(bstrNodeValue);
		SAFE_RELEASE(pNode);*/

		//Reading Sheep Initialization
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[8]/*"), &pNodes));

		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		sheepInitializationStartingX = _wtoi(bstrNodeValue);



		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(1, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		sheepInitializationStartingY = _wtoi(bstrNodeValue);


		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(2, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		sheepInitializationXRange = _wtoi(bstrNodeValue);


		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(3, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		sheepInitializationYRange = _wtoi(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(4, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		//sheepInitializationPattern = bstrNodeValue.
		std::wstring SheepInitializationPattern = bstrNodeValue;
		sheepInitializationPattern = std::string(SheepInitializationPattern.begin(), SheepInitializationPattern.end());
		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);

		//Reading SheepDog Initialization
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[9]/*"), &pNodes));

		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		sheepDogInitializationStartingX = _wtoi(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(1, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		sheepDogInitializationStartingY = _wtoi(bstrNodeValue);


		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(2, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		sheepDogInitializationXRange = _wtoi(bstrNodeValue);


		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(3, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		sheepDogInitializationYRange = _wtoi(bstrNodeValue);


		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);

		//Reading Maximum Number of Steps
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[10]/*"), &pNodes));

		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		MaximumNumSteps = _wtoi(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);

		//Reading Obstacles
		CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[11]/*"), &pNodes));
		CHK_HR(pNodes->get_item(0, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		obstaclesDensity = std::stof(bstrNodeValue);


		SysFreeString(bstrNodeValue);
		CHK_HR(pNodes->get_item(1, &pNode));
		CHK_HR(pNode->get_nodeName(&bstrNodeName));
		SysFreeString(bstrNodeName);
		CHK_HR(pNode->get_text(&bstrNodeValue));
		obstaclesRadius = std::stof(bstrNodeValue);

		SysFreeString(bstrNodeValue);
		SAFE_RELEASE(pNode);


		printf("Random Numbers Speed: %d\n", randomNumberSeed);
		printf("Visualisation : %s\n", visualizationON ? "true" : "false");
		printf("Simulation Speed: %d\n", simSpeed);
		printf("ScreenWidth in Pixels: %d\n", screenWidthPixels);
		printf("Screen Height in Pixels: %d\n", screenHeightPixels);
		printf("Field Length and Width: %d\n", FieldLength);
		printf("Window Margin Size: %d\n", WindowMarginSize);
		printf("Goal LocationX: %d\n", gLocX);
		printf("Goal LocationT: %d\n", gLocY);
		printf("Paddock On : %s\n", paddockON ? "true" : "false");
		if (paddockON)
		{
			printf("Paddock Length: %d\n", paddockLength);
			printf("paddock Width: %d\n", paddockWidth);
		}
		else
		{
			printf("Goal Radius: %d\n", goalRadius);

		}


		printf("N: %d\n", N);
		printf("M: %d\n", M);
		printf("R_pi_beta: %.2f\n", R_pi_beta);
		printf("Ra_pi_pi: %.2f\n", Ra_pi_pi);
		printf("Rs_pi_pi: %.2f\n", Rs_pi_pi);
		printf("card_Omega_pi_pi: %d\n", card_Omega_pi_pi);
		printf("card_Omega_beta_pi: %d\n", card_Omega_beta_pi);
		printf("W_pi_pi: %.2f\n", W_pi_pi);
		printf("W_pi_beta: %.2f\n", W_pi_beta);
		printf("W_pi_Lambda: %.2f\n", W_pi_Lambda);
		printf("W_pi_upsilon: %.2f\n", W_pi_upsilon);
		printf("W_e_pi_i: %.2f\n", W_e_pi_i);
		printf("W_e_beta_j: %.2f\n", W_e_beta_j);
		printf("S_t_beta_j: %.2f\n", S_t_beta_j);
		printf("eta: %.2f\n", eta);
		printf("R_beta_beta: %.2f\n", R_beta_beta);
		printf("R_beta_pi: %.2f\n", R_beta_pi);
		printf("W_beta_beta: %.2f\n", W_beta_beta);
		printf("DrivingPositionEq: %d\n",  DrivingPositionEq);
		printf("CollectingPositionEq: %d\n", CollectingPositionEq);
		printf("fNequation: %d\n", fNequation);;
		printf("ForceRegulated: %d\n", ForceRegulated);
		printf("SheepNeignborhoodSelection: %d\n", SheepNeignborhoodSelection);
		printf("ModulationDecayFactor: %d\n", ModulationDecayFactor);
		printf("Circular Path Planning On : %s\n", CircularPathPlanningON ? "true" : "false");
		printf("StallingON : %s\n", StallingON ? "true" : "false");
		printf("StallingDistance : %.2f\n", StallingDistance);
		printf("R2 : %d\n", R2 );
		printf("R3 : %d\n", R3);
		printf("Sheep Initialization %d ,%d, %d, %d, %s\n", sheepInitializationStartingX, sheepInitializationStartingY, sheepInitializationXRange, sheepInitializationYRange, sheepInitializationPattern.c_str());
		printf("SheepDog Initialization %d ,%d, %d, %d \n", sheepDogInitializationStartingX, sheepDogInitializationStartingY, sheepDogInitializationXRange, sheepDogInitializationYRange);



		//	}



	}
	else
	{
		// Failed to load xml, get last parsing error
		CHK_HR(pXMLDom->get_parseError(&pXMLErr));
		CHK_HR(pXMLErr->get_reason(&bstrErr));
		printf("Failed to load DOM from config.xml. %S\n", bstrErr);
	}

CleanUp:
	SAFE_RELEASE(pXMLDom);
	SAFE_RELEASE(pXMLErr);
	SysFreeString(bstrXML);
	SysFreeString(bstrErr);
	VariantClear(&varFileName);
}

void loadDOMGraphics(std::string filename)
{
	HRESULT hr = S_OK;
	IXMLDOMDocument* pXMLDom = NULL;
	IXMLDOMParseError* pXMLErr = NULL;

	BSTR bstrXML = NULL;
	BSTR bstrErr = NULL;
	VARIANT_BOOL varStatus;
	VARIANT varFileName;
	VariantInit(&varFileName);

	CHK_HR(CreateAndInitDOM(&pXMLDom));

	// XML file name to load

	CHK_HR(VariantFromString(SysAllocString(std::wstring(filename.begin(), filename.end()).c_str()), varFileName));

	//	CHK_HR(VariantFromString(inputFileName, varFileName));

	CHK_HR(pXMLDom->load(varFileName, &varStatus));
	if (varStatus == VARIANT_TRUE)
	{
		CHK_HR(pXMLDom->get_xml(&bstrXML));
		printf("XML was successfully loaded\n");
		BSTR bstrNodeName = NULL;
		BSTR bstrNodeValue = NULL;
		IXMLDOMNode* pNode = NULL;

		// Query a node-set.
		BSTR bstrQuery2 = NULL;
		IXMLDOMNodeList* pNodes = NULL;



	//Reading simSpeed
	CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[1]/*"), &pNodes));
	CHK_HR(pNodes->get_item(0, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));
	simSpeed = _wtoi(bstrNodeValue);
	SysFreeString(bstrNodeValue);
	SAFE_RELEASE(pNode);

	//Reading Screen Configuration
	CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[2]/*"), &pNodes));
	CHK_HR(pNodes->get_item(0, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));
	//printf("\t%S\n", bstrNodeValue);
	screenWidthPixels = _wtoi(bstrNodeValue);
	SysFreeString(bstrNodeValue);
	CHK_HR(pNodes->get_item(1, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));
	//printf("\t%S\n", bstrNodeValue);
	screenHeightPixels = _wtoi(bstrNodeValue);
	SysFreeString(bstrNodeValue);
	SAFE_RELEASE(pNode);


	//Reading Forces Visualization Configuration
	CHK_HR(pXMLDom->selectNodes(SysAllocString(L"//config[3]/*"), &pNodes));
	CHK_HR(pNodes->get_item(0, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));
	//printf("\t%S\n", bstrNodeValue);
	if (_wtoi(bstrNodeValue) == 1)
	{
		CollisionAvoidanceOpponentsForceON = true;
	}
	else
	{
		CollisionAvoidanceOpponentsForceON = false;
	}
	SysFreeString(bstrNodeValue);
	CHK_HR(pNodes->get_item(1, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));

	if (_wtoi(bstrNodeValue) == 1)
	{
		CollisionAvoidanceFriendsForceON = true;
	}
	else
	{
		CollisionAvoidanceFriendsForceON = false;
	}

	SysFreeString(bstrNodeValue);
	CHK_HR(pNodes->get_item(2, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));

	if (_wtoi(bstrNodeValue) == 1)
	{
		AttractionBehaviorForceON = true;
	}
	else
	{
		AttractionBehaviorForceON = false;
	}

	SysFreeString(bstrNodeValue);
	CHK_HR(pNodes->get_item(3, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));

	if (_wtoi(bstrNodeValue) == 1)
	{
		CollisionAvoidanceStaticObstaclesForceON = true;
	}
	else
	{
		CollisionAvoidanceStaticObstaclesForceON = false;
	}

	SysFreeString(bstrNodeValue);
	CHK_HR(pNodes->get_item(4, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));

	if (_wtoi(bstrNodeValue) == 1)
	{
		JitteringForceON = true;
	}
	else
	{
		JitteringForceON = false;
	}


	SysFreeString(bstrNodeValue);
	CHK_HR(pNodes->get_item(5, &pNode));
	CHK_HR(pNode->get_nodeName(&bstrNodeName));
	SysFreeString(bstrNodeName);
	CHK_HR(pNode->get_text(&bstrNodeValue));

	if (_wtoi(bstrNodeValue) == 1)
	{
		scaleForceVisualization = true;
	}
	else
	{
		scaleForceVisualization = false;
	}

	SysFreeString(bstrNodeValue);
	SAFE_RELEASE(pNode);


	}
	else
	{
		// Failed to load xml, get last parsing error
		CHK_HR(pXMLDom->get_parseError(&pXMLErr));
		CHK_HR(pXMLErr->get_reason(&bstrErr));
		printf("Failed to load DOM from config.xml. %S\n", bstrErr);
	}

CleanUp:
	SAFE_RELEASE(pXMLDom);
	SAFE_RELEASE(pXMLErr);
	SysFreeString(bstrXML);
	SysFreeString(bstrErr);
	VariantClear(&varFileName);
}

