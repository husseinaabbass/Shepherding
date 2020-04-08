#include <SDL.h>
#include "pch.h"
#include "Visualization.h"
#include"Flock.h"
#include <SDL_image.h>
#include <assert.h>     /* assert */

//#include "Agents.h"
#include "Sim.h"
/* Visualization class
* Holds all information dealing with graphics for the Sim
*/

int screenWIDTH, screenHEIGHT;
int maximumNumSteps_v;
int fieldWIDTH, fieldHEIGHT;
int goalLOCX, goalLOCY;
int PaddockLength, PaddockWidth;
float imageScale;
int arrowimageScale;
int scale;
int simulationSpeed;
int visualizationClock;
bool PaddockOn;
int GoalRadius;
SDL_Surface * arrowOrange, * arrowGreen, * arrowBlack, * arrowBlue, *arrowRed, * arrowBrown , *shepherdIcon, *goalIcon , *obstacleIcon;
SDL_Texture * arrowTextureOrange, *arrowTextureGreen, *arrowTextureBlack, *arrowTextureBlue, *arrowTextureRed, * arrowTextureBrown, *shepherdIconTexture, *goalIconTexture, *obstacleIconTexture;
TTF_Font* font, *font_small;
std::string ConfigFileName;
//Flock* flock;
//Environment* env=new Environment();
Simulation* sim;
//Environment& env = Environment::getInstance();
bool CollisionAvoidanceOpponentsForceOn = true;
bool CollisionAvoidanceFriendsForceOn = true;
bool AttractionBehaviorForceOn = true;
bool CollisionAvoidanceStaticObstaclesForceOn = true;
bool JitteringForceOn = true;
bool ScaleForceVisualization = true;
void Visualization::init(int randomNumberSeed, std::string title, int inScale, int simSpeed, int screenWidth, int screenHeight, int fieldWidth, int fieldHeight, int N, int M, float R_pi_beta, float Ra_pi_pi, float Rs_pi_pi, float R_beta_beta, float W_pi_pi, float W_beta_beta, float W_pi_beta, float W_pi_Lambda, float W_pi_upsilon, float W_e_pi_i, float W_e_beta_j, float S_t_beta_j, float eta, int card_Omega_pi_pi, int card_Omega_beta_pi, int goalLocX, int goalLocY, int paddockLENGTH, int paddockWIDTH, bool paddockON, bool circularPathPlanningON, bool StallingON, float StallingDistance, int R2, int R3, int goalRadius, int ForceRegulated, int fNequation, int DrivingPositionEq, int CollectingPositionEq, int SheepNeignborhoodSelection, int ModulationDecayFactor, int sheepInitializationStartingX, int sheepInitializationStartingY, int sheepInitializationXRange, int sheepInitializationYRange, std::string sheepInitializationPattern, int sheepDogInitializationStartingX, int sheepDogInitializationStartingY, int sheepDogInitializationXRange, int sheepDogInitializationYRange, int MaximumNumSteps, float obstaclesDensity, float obstaclesRadius, bool CollisionAvoidanceOpponentsForceON, bool CollisionAvoidanceFriendsForceON, bool AttractionBehaviorForceON, bool CollisionAvoidanceStaticObstaclesForceON, bool JitteringForceON, bool scaleForceVisualization)
{
	scale = inScale;
	maximumNumSteps_v = MaximumNumSteps;
	simulationSpeed = simSpeed;
	imageScale = scale*0.5;
	arrowimageScale = scale / 5;
	visualizationClock = 0;
	PaddockLength = paddockLENGTH;
	PaddockWidth = paddockWIDTH;
	PaddockOn = paddockON;
	GoalRadius = goalRadius;
	Environment& env = Environment::getInstance();
	
	CollisionAvoidanceOpponentsForceOn = CollisionAvoidanceOpponentsForceON;
	CollisionAvoidanceFriendsForceOn = CollisionAvoidanceFriendsForceON;
	AttractionBehaviorForceOn = AttractionBehaviorForceON;
	CollisionAvoidanceStaticObstaclesForceOn = CollisionAvoidanceStaticObstaclesForceON;
	JitteringForceOn = JitteringForceON;
	ScaleForceVisualization = scaleForceVisualization;
	//SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	screenWIDTH = screenWidth;
	screenHEIGHT = screenHeight;
	fieldWIDTH = fieldWidth;
	fieldHEIGHT = fieldHeight;
	this->fieldStartX = (screenWIDTH - fieldWIDTH) / 2;
	this->fieldStartY = (screenHEIGHT - fieldHEIGHT) / 2;
	goalLOCX = goalLocX;
	goalLOCY = goalLocY;
	
	sim = new Simulation();
	sim->init(randomNumberSeed, N, M, fieldStartX, fieldStartY, fieldWIDTH, fieldHEIGHT,  R_pi_beta,  Ra_pi_pi, Rs_pi_pi, R_beta_beta,  W_pi_pi, W_beta_beta,  W_pi_beta,  W_pi_Lambda,  W_pi_upsilon,  W_e_pi_i,  W_e_beta_j,S_t_beta_j, eta,card_Omega_pi_pi, card_Omega_beta_pi, goalLocX, goalLocY, PaddockLength, PaddockWidth,paddockON, circularPathPlanningON,  StallingON,  StallingDistance, R2, R3,  GoalRadius, ForceRegulated, fNequation,  DrivingPositionEq,  CollectingPositionEq,  SheepNeignborhoodSelection,  ModulationDecayFactor, sheepInitializationStartingX, sheepInitializationStartingY, sheepInitializationXRange, sheepInitializationYRange, sheepInitializationPattern, sheepDogInitializationStartingX, sheepDogInitializationStartingY, sheepDogInitializationXRange, sheepDogInitializationYRange, obstaclesDensity, obstaclesRadius);
	
	ConfigFileName = title.substr(23, ConfigFileName.length());

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		
		/*****************************************************************************************************/
		// The following code to show the simulation screen on a second monitor// If not required can be replaced by :
		//window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth*scale, screenHeight*scale, SDL_WINDOW_ALLOW_HIGHDPI);
		/*****************************************************************************************************/

		// enumerate displays
		int displays = SDL_GetNumVideoDisplays();
		//assert(displays > 1);  // assume we have secondary monitor

		// get display bounds for all displays
		std::vector< SDL_Rect > displayBounds;
		for (int i = 0; i < displays; i++) {
			displayBounds.push_back(SDL_Rect());
			SDL_GetDisplayBounds(i, &displayBounds.back());
		}
		int screen_centred_start_x;
		int screen_centred_start_y;

		if (displayBounds.size() > 1) //if more than display, select the second monitor, otherwise, use the first monitor
		{
			screen_centred_start_x= displayBounds[1].x + ((displayBounds[0]).w - screenWidth * scale) / 2;
			screen_centred_start_y= displayBounds[1].y+((displayBounds[0]).h - screenHeight * scale) / 2;
		}
		else //otherwise, use the first monitor
		{
			screen_centred_start_x= displayBounds[0].x+((displayBounds[0]).w - screenWidth * scale) / 2;
			screen_centred_start_y= displayBounds[0].y+((displayBounds[0]).h - screenHeight * scale) / 2;

		}

		//Create window
		// so now x and y are on secondary display
		window = SDL_CreateWindow(title.c_str(), screen_centred_start_x, screen_centred_start_y , screenWidth*scale, screenHeight*scale, SDL_WINDOW_ALLOW_HIGHDPI);

		/*****************************************************************************************************/
	

		//window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth*scale, screenHeight*scale, SDL_WINDOW_ALLOW_HIGHDPI);



		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Create renderer for window
			//gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
			}
			else
			{

				//Initialise renderer color
				//SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
				//background = SDL_LoadBMP("background.bmp");
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); //White color
				screen = SDL_CreateRGBSurface(0, screenWidth*scale, screenHeight*scale, 32, 255, 255, 255, 255);
				texture = SDL_CreateTextureFromSurface(gRenderer, screen);

				int imgFlags = IMG_INIT_JPG;
				bool fff = IMG_Init(imgFlags);

				if (IMG_Init(imgFlags) & imgFlags)
				{

					arrowOrange = IMG_Load("..\\InputFiles\\OrangeArrow.png");
					arrowTextureOrange = SDL_CreateTextureFromSurface(gRenderer, arrowOrange);
					arrowGreen = IMG_Load("..\\InputFiles\\GreenArrow.png");
					arrowTextureGreen = SDL_CreateTextureFromSurface(gRenderer, arrowGreen);
					arrowBlack = IMG_Load("..\\InputFiles\\BlackArrow.png");
					arrowTextureBlack = SDL_CreateTextureFromSurface(gRenderer, arrowBlack);
					arrowBlue = IMG_Load("..\\InputFiles\\BlueArrow.png");
					arrowTextureBlue = SDL_CreateTextureFromSurface(gRenderer, arrowBlue);
					arrowRed = IMG_Load("..\\InputFiles\\RedArrow.png");
					arrowTextureRed = SDL_CreateTextureFromSurface(gRenderer, arrowRed);
					arrowBrown = IMG_Load("..\\InputFiles\\BrownArrow.png");
					arrowTextureBrown = SDL_CreateTextureFromSurface(gRenderer, arrowBrown);
					shepherdIcon= IMG_Load("..\\InputFiles\\shepherd_icon.png");
					shepherdIconTexture = SDL_CreateTextureFromSurface(gRenderer, shepherdIcon);
					goalIcon = IMG_Load("..\\InputFiles\\goal_icon.png");
					goalIconTexture = SDL_CreateTextureFromSurface(gRenderer, goalIcon);
					obstacleIcon = IMG_Load("..\\InputFiles\\BrownCircle.png");
					obstacleIconTexture = SDL_CreateTextureFromSurface(gRenderer, obstacleIcon);


				}
				else
				{
					printf("SDL_image could not initialise! SDL_image Error: %s\n", IMG_GetError());

				}
			}

		}
		//return false;
		//screen = SDL_GetWindowSurface(window);
		//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); //White color

		//renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		font = TTF_OpenFont("..\\InputFiles\\FreeSans.ttf", 20); //this opens a font style and sets a size
		font_small = TTF_OpenFont("..\\InputFiles\\FreeSans.ttf", 10);
		if (!font) {
			printf("TTF_OpenFont: %s\n", TTF_GetError());
			// handle error
		}

		//startTime = SDL_GetTicks();

		//return true;
		Visualization::isRunning = true;
	}
	else
	{
		Visualization::isRunning = false;
	}
}

void Visualization::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
		{
			isRunning = false;
		}
	}
}

void Visualization::update(std::ofstream & outfile, std::ofstream & outputCompletionTimefile)
{
	bool statusBeforeUpdate = sim->goalFound;
	if (visualizationClock%simulationSpeed == 0)
	{
		sim->update();
		if (!statusBeforeUpdate)
		{
			streamOut(outfile, outputCompletionTimefile);
		}
	}
	visualizationClock++;

	
}

void Visualization::render()
{
	//currentTime = (int)(Visualization::Time());

	//	// Clear screen with white
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); //White color
	SDL_RenderClear(gRenderer);

	//	
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0); // Black color
	
	//	// Draw a wired rectangle to represent the field
	//SDL_Rect rect2 = { fieldStartX*scale, fieldStartY*scale, fieldWIDTH*scale, fieldHEIGHT*scale };
	//SDL_RenderDrawRect(gRenderer, &rect2);

	SDL_RenderSetLogicalSize(gRenderer, screenWIDTH*scale, screenHEIGHT*scale);
	
	// Draw Goal 
	//if shown centred around PG(0,0)


	if (PaddockOn)
	{
		SDL_Rect GoalRect = { goalLOCX* scale - (4 * scale) , goalLOCY* scale - (4 * scale) ,8 * scale , 8 * scale };
		 SDL_RenderCopyEx(gRenderer, goalIconTexture, NULL, &GoalRect, 0, NULL, SDL_FLIP_NONE);
	}
	else
	{
		SDL_Rect	 GoalRect = { goalLOCX* scale - (GoalRadius * scale) , goalLOCY* scale - (GoalRadius * scale) ,GoalRadius *2 * scale , GoalRadius *2 * scale };
		 SDL_RenderCopyEx(gRenderer, goalIconTexture, NULL, &GoalRect, 0, NULL, SDL_FLIP_NONE);
	}
	
	//	SDL_RenderCopyEx(gRenderer, goalIconTexture, NULL, &GoalRect, 0, NULL, SDL_FLIP_NONE);
	//if centred inside the paddoc
	//SDL_Rect GoalRect = { (goalLOCX+ paddockWidth /2)* scale - (4 * scale) , (goalLOCY+paddockLength/2)* scale - (4 * scale) ,8 * scale , 8 * scale };

	SDL_SetRenderDrawColor(gRenderer, 11, 255, 49, 50); // green color
	const SDL_Rect fieldRect = { fieldStartX* scale  , fieldStartY* scale  ,fieldWIDTH * scale , fieldHEIGHT * scale };
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

	SDL_RenderFillRect(gRenderer,  &fieldRect);

	

	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0); // Black color

	// Draw paddock 3 side shape
	
	if (PaddockOn)
	{
		SDL_RenderDrawLine(gRenderer, (goalLOCX - PaddockWidth / 2)* scale, (goalLOCY - PaddockLength / 2)* scale, (goalLOCX - (PaddockWidth / 2) + PaddockWidth)*scale, (goalLOCY - PaddockLength / 2)* scale);
		SDL_RenderDrawLine(gRenderer, (goalLOCX - PaddockWidth / 2)* scale, (goalLOCY - PaddockLength / 2)* scale, (goalLOCX - (PaddockWidth / 2))*scale, (goalLOCY - PaddockLength / 2 + PaddockLength)* scale);
		SDL_RenderDrawLine(gRenderer, (goalLOCX - PaddockWidth / 2)* scale, (goalLOCY - PaddockLength / 2 + PaddockLength)* scale, (goalLOCX - (PaddockWidth / 2) + PaddockWidth)*scale, (goalLOCY - PaddockLength / 2 + PaddockLength)* scale);
	}

	DrawFlock();
	DrawObstacles();
	

	SDL_Color Red = { 255, 0, 0 };  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font, std::to_string(sim->timestep).c_str(), Red); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage); //now you can convert it into a texture

	//SDL_Rect Message_rect = { screenWIDTH - ((screenWIDTH - fieldWIDTH)) / 2 , 75, surfaceMessage->w ,surfaceMessage->h };
	SDL_Rect Message_rect = { fieldWIDTH*scale+(screenWIDTH*scale - fieldWIDTH*scale)/2-10 , 10, surfaceMessage->w ,surfaceMessage->h };



	SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect); //
	// Create an empty RGB surface that will be used to create the screenshot bmp file


	if (sim->timestep==0)
	{
		SDL_Surface* pScreenShot = SDL_GetWindowSurface(window);

		//SDL_Surface* pScreenShot = SDL_CreateRGBSurface(0, screenWIDTH*scale, screenHEIGHT*scale, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);

		// Read the pixels from the current render target and save them onto the surface
		SDL_RenderReadPixels(gRenderer, NULL, SDL_GetWindowPixelFormat(window), pScreenShot->pixels, pScreenShot->pitch);

		// Create the bmp screenshot file
		SDL_SaveBMP(pScreenShot, (ConfigFileName+std::string("_screenShot_t0.bmp")).c_str());
		// Destroy the screenshot surface
		SDL_FreeSurface(pScreenShot);
	}

	SDL_SetRenderTarget(gRenderer, NULL);

	// Show what was drawn
	SDL_RenderPresent(gRenderer);
	SDL_DestroyTexture(Message);

}





void Visualization::clean()
{
	// Release resources



	TTF_Quit();
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(window);
	window = NULL;
	SDL_Quit();
}

bool Visualization::running()
{
	return isRunning;
}


Visualization::Visualization() {}




Visualization::~Visualization() {
	//	SDL_DestroyWindow(window);
	clean();

}


//double Visualization::Time()
//{
//	return (double)(SDL_GetTicks() - startTime);
//}

//void Visualization::DrawPoint(int pointLocationx, int pointLocationy, int pointSize, Uint8  r,	Uint8 g,	Uint8  b)
//{
//	
//		SDL_SetRenderDrawColor(gRenderer, r, g, b, 255); // 
//
//		SDL_Rect pointLoc = { pointLocationx*scale - (pointSize / 2) ,pointLocationy*scale - (pointSize / 2) ,pointSize ,pointSize };
//
//		SDL_RenderDrawPoint(gRenderer, pointLocationx*scale, pointLocationy*scale);
//		SDL_RenderFillRect(gRenderer, &pointLoc);
//	
//}

void Visualization::DrawPoint(float pointLocationx, float pointLocationy, float pointSize, Uint8  r, Uint8 g, Uint8  b)
{

	SDL_SetRenderDrawColor(gRenderer, r, g, b, 255); // 

	SDL_Rect pointLoc = { pointLocationx*scale - (pointSize / 2) ,pointLocationy*scale - (pointSize / 2) ,pointSize ,pointSize };

	SDL_RenderDrawPoint(gRenderer, pointLocationx*scale, pointLocationy*scale);
	SDL_RenderFillRect(gRenderer, &pointLoc);

}

void Visualization::DrawForce(float x, float y, Vector2f force, SDL_Texture * arrowTexture, int arrowimageScale)
{
	float theta_rad = atan2(force.y, force.x);
	float theta_deg = (theta_rad / M_PI * 180) + (theta_rad > 0 ? 0 : 360);
	float forceMagnitude = 1;
	if (ScaleForceVisualization)
	{
		forceMagnitude = force.length();
	}
	

	

	if (theta_deg > 270)
	{
		SDL_Rect arrowRect = { x*scale     , y*scale - 1.5	*imageScale, arrowimageScale *forceMagnitude, arrowimageScale*forceMagnitude };
		SDL_RenderCopyEx(gRenderer, arrowTexture, NULL, &arrowRect, theta_deg, NULL, SDL_FLIP_NONE);

	}
	else if (theta_deg > 180)
	{
		SDL_Rect arrowRect = { x*scale - 1.5*imageScale   ,y*scale -2*imageScale    , arrowimageScale *forceMagnitude, arrowimageScale*forceMagnitude };
		SDL_RenderCopyEx(gRenderer, arrowTexture, NULL, &arrowRect, theta_deg, NULL, SDL_FLIP_NONE);


	}
	else if (theta_deg > 90)
	{
		SDL_Rect arrowRect = { x*scale - imageScale   ,y*scale + (imageScale / 2) , arrowimageScale *forceMagnitude, arrowimageScale*forceMagnitude };
		SDL_RenderCopyEx(gRenderer, arrowTexture, NULL, &arrowRect, theta_deg, NULL, SDL_FLIP_NONE);


	}
	else if (theta_deg > 0)
	{
		SDL_Rect arrowRect = { x*scale + (imageScale / 2)    ,y*scale + (imageScale / 2)   , arrowimageScale*forceMagnitude , arrowimageScale*forceMagnitude };
		SDL_RenderCopyEx(gRenderer, arrowTexture, NULL, &arrowRect, theta_deg, NULL, SDL_FLIP_NONE);

	}

	
}

void Visualization::DrawText(std::string stringText, int x, int y, TTF_Font* font1, std::string pos)
{
	//Print the force atan degree
	SDL_Color Red = { 255, 0, 0 };
	const char* text = stringText.c_str();

	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(font1, text, Red); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

	SDL_Texture* Message = SDL_CreateTextureFromSurface(gRenderer, surfaceMessage); //now you can convert it into a texture


	SDL_Rect Message_rect;
	if (pos == "right")
	{
		Message_rect = { x*scale + 10 , y*scale, surfaceMessage->w ,surfaceMessage->h };
	}
	else if (pos == "left")
	{
		Message_rect = { x*scale - 10 , y*scale, surfaceMessage->w ,surfaceMessage->h };
	}
	else if (pos == "up")
	{
		Message_rect = { x*scale  , y*scale - 10, surfaceMessage->w ,surfaceMessage->h };
	}
	else if (pos == "down")
	{
		Message_rect = { x*scale  , y*scale + 10, surfaceMessage->w ,surfaceMessage->h };
	}




	SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect); //
	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);


}

void Visualization::DrawFlock()
{
	//SDL_Texture *DrawingTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, screenWIDTH, screenHEIGHT);

	Environment& env = Environment::getInstance();

	//SDL_SetRenderTarget(renderer, DrawingTexture);
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); //White color
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_NONE);


	for (int i = 0; i < env.sheepFlock->size(); i++) {

		//Draw the sheepAgent itself
		DrawPoint((*env.sheepFlock)[i]->position_t.x, (*env.sheepFlock)[i]->position_t.y, imageScale, 0, 0, 255);

		//Draw the forces
		int arrowimageScale = 10;
		if (AttractionBehaviorForceOn)
		{
			DrawForce((*env.sheepFlock)[i]->position_t.x, (*env.sheepFlock)[i]->position_t.y, (*env.sheepFlock)[i]->get_F_pi_i_Lambda_t(), arrowTextureGreen, arrowimageScale);
		}
		if (CollisionAvoidanceOpponentsForceOn)
		{
			DrawForce((*env.sheepFlock)[i]->position_t.x, (*env.sheepFlock)[i]->position_t.y, (*env.sheepFlock)[i]->get_F_pi_i_beta_j_t(), arrowTextureBlack, arrowimageScale);
		}
		if (CollisionAvoidanceFriendsForceOn)
		{
			DrawForce((*env.sheepFlock)[i]->position_t.x, (*env.sheepFlock)[i]->position_t.y, (*env.sheepFlock)[i]->get_F_pi_i_pi_k_t(), arrowTextureOrange, arrowimageScale);
		}
		if (JitteringForceOn)
		{
			DrawForce((*env.sheepFlock)[i]->position_t.x, (*env.sheepFlock)[i]->position_t.y, (*env.sheepFlock)[i]->get_F_pi_i_E_t(), arrowTextureBlue, arrowimageScale);
		}
		if (CollisionAvoidanceStaticObstaclesForceOn)
		{
			DrawForce((*env.sheepFlock)[i]->position_t.x, (*env.sheepFlock)[i]->position_t.y, (*env.sheepFlock)[i]->F_obst_t, arrowTextureBrown, arrowimageScale);

		}
		//Extra information on sheepDog forces to check implementation.
		//DrawPoint((*env.sheepFlock)[i]->Lambda_t.x, (*env.sheepFlock)[i]->Lambda_t.y, imageScale / 2, 0, 255, 0);
		DrawText(std::to_string((*env.sheepFlock)[i]->agentID), (int)(*env.sheepFlock)[i]->position_t.x, (int)(*env.sheepFlock)[i]->position_t.y, font_small, "right");

	}


	////draw local centre of mass of each sheep

	/*for (int i = 0; i < env.sheepFlock->size(); i++) {

		DrawPoint((*env.sheepFlock)[i]->Lambda_t.x, (*env.sheepFlock)[i]->Lambda_t.y, imageScale, 0, 255, 0);
	}*/

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); //White color

	for (int i = 0; i < env.sheepDogFlock->size(); i++) {

		//if the function uses original SDL method scale the input before sending it. If a function that is implemented within this code, No need to scale. It will be scaled within the called function.
		//DrawPoint, DrawForce, DrawText are implemented in-house. No need to scale the inputs.


		//Draw the sheepDogAgent itself
		//SDL_Rect arrowRect = { (*env.sheepDogFlock)[i]->position_t.x*scale - (2*imageScale) ,(*env.sheepDogFlock)[i]->position_t.y*scale - (2*imageScale) ,4 * imageScale ,4 * imageScale };
		SDL_Rect arrowRect = { (*env.sheepDogFlock)[i]->position_t.x * scale - (1 * imageScale) ,(*env.sheepDogFlock)[i]->position_t.y * scale - (1 * imageScale) ,2 * imageScale ,2 * imageScale };
		SDL_RenderCopyEx(gRenderer, shepherdIconTexture, NULL, &arrowRect, 0, NULL, SDL_FLIP_NONE);
		DrawText(std::to_string((*env.sheepDogFlock)[i]->agentID), (int)(*env.sheepDogFlock)[i]->position_t.x, (int)(*env.sheepDogFlock)[i]->position_t.y, font, "right");

		//Draw the forces
		Vector2f temp1 = (*env.sheepDogFlock)[i]->get_F_beta_j_c_t();
		Vector2f temp2 = (*env.sheepDogFlock)[i]->get_F_beta_j_d_t();
		DrawForce((*env.sheepDogFlock)[i]->position_t.x, (*env.sheepDogFlock)[i]->position_t.y, (*env.sheepDogFlock)[i]->get_F_beta_j_d_t(), arrowTextureRed, arrowimageScale);
		DrawForce((*env.sheepDogFlock)[i]->position_t.x, (*env.sheepDogFlock)[i]->position_t.y, (*env.sheepDogFlock)[i]->get_F_beta_j_c_t(), arrowTextureBlue, arrowimageScale);
		DrawForce((*env.sheepDogFlock)[i]->position_t.x, (*env.sheepDogFlock)[i]->position_t.y, (*env.sheepDogFlock)[i]->get_F_beta_i_beta_k_t(), arrowTextureBlack, arrowimageScale);

		//Extra information on sheepDog forces to check implementation.
		DrawPoint((*env.sheepDogFlock)[i]->Lambda_t.x, (*env.sheepDogFlock)[i]->Lambda_t.y, imageScale, 0, 255, 0);
		if (env.M == 1)
		{
			DrawText("SheepDog LCM " + std::to_string((*env.sheepDogFlock)[i]->agentID), (int)(*env.sheepDogFlock)[i]->Lambda_t.x, (int)(*env.sheepDogFlock)[i]->Lambda_t.y, font_small, "right");
		}
		if (env.M > 1)
		{
			DrawText("SheepDog GCM ", (int)(*env.sheepDogFlock)[i]->Lambda_t.x, (int)(*env.sheepDogFlock)[i]->Lambda_t.y, font_small, "right");
		}

		if ((*env.sheepDogFlock)[i]->get_F_beta_j_d_t().x != 0)
		{
			DrawPoint((*env.sheepDogFlock)[i]->get_P_beta_j_d_t().x, (*env.sheepDogFlock)[i]->get_P_beta_j_d_t().y, imageScale, 0, 0, 0);
			DrawText("Driving Position " + std::to_string((*env.sheepDogFlock)[i]->agentID), (int)(*env.sheepDogFlock)[i]->get_P_beta_j_d_t().x, (int)(*env.sheepDogFlock)[i]->get_P_beta_j_d_t().y, font_small, "right");
			std::string supportingInfo = (*env.sheepDogFlock)[i]->LoggingSupportingInformation;
			std::string role = supportingInfo.substr(supportingInfo.find(":") + 1);
			DrawText(std::string("Driving ")+ role, (int)(*env.sheepDogFlock)[i]->position_t.x, (int)(*env.sheepDogFlock)[i]->position_t.y, font_small, "down");

		}
		if ((*env.sheepDogFlock)[i]->get_F_beta_j_c_t().x != 0)
		{
			DrawPoint((*env.sheepDogFlock)[i]->get_P_beta_j_c_t().x, (*env.sheepDogFlock)[i]->get_P_beta_j_c_t().y, imageScale, 0, 0, 0);
			DrawText("Collecting Position SheepDog " + std::to_string((*env.sheepDogFlock)[i]->agentID), (int)(*env.sheepDogFlock)[i]->get_P_beta_j_c_t().x, (int)(*env.sheepDogFlock)[i]->get_P_beta_j_c_t().y, font_small, "right");
			std::string supportingInfo = (*env.sheepDogFlock)[i]->LoggingSupportingInformation;
			std::string toBeCollectedSheepID = supportingInfo.substr(supportingInfo.find(":")+1);
			DrawText(std::string("Collect Sheep ")+toBeCollectedSheepID, (int)(*env.sheepDogFlock)[i]->position_t.x, (int)(*env.sheepDogFlock)[i]->position_t.y, font_small, "down");
		}


	}









}

void Visualization::DrawObstacles()
{
	Environment& env = Environment::getInstance();

	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255); //White color
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_NONE);

	for (int i = 0; i < env.terrain.staticObstacles->size(); i++) {

		//Draw the obstacles 
		//DrawPoint((*env.terrain.staticObstacles)[i]->position_t.x, (*env.terrain.staticObstacles)[i]->position_t.y, imageScale, 130, 150, 120);
		SDL_Rect arrowRect = { (*env.terrain.staticObstacles)[i]->position_t.x * scale - ( 0.5*imageScale) ,(*env.terrain.staticObstacles)[i]->position_t.y * scale - (0.5 * imageScale) , imageScale , imageScale };
		SDL_RenderCopyEx(gRenderer, obstacleIconTexture, NULL, &arrowRect, 0, NULL, SDL_FLIP_NONE);


	}
}


void Visualization::streamOut(std::ofstream & outfile, std::ofstream & outputCompletionTimefile)
{
	Environment& env = Environment::getInstance();
			//std::list<float> newRow;
		outfile << sim->timestep << ",";

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
			outfile<< (*env.sheepFlock)[i]->get_F_pi_i_beta_j_t().x << ",";
			outfile << (*env.sheepFlock)[i]->get_F_pi_i_beta_j_t().y << ",";
			outfile << (*env.sheepFlock)[i]->get_F_pi_i_Lambda_t().x << ",";
			outfile << (*env.sheepFlock)[i]->get_F_pi_i_Lambda_t().y << ",";
			outfile << (*env.sheepFlock)[i]->get_F_pi_i_pi_k_t().x << ",";
			outfile << (*env.sheepFlock)[i]->get_F_pi_i_pi_k_t().y << ",";


		}
		outfile << std::endl;
		if (sim->goalFound == true)
		{			
			std::cout << "Task completed. All sheep are at goal" << std::endl;
			//outputCompletionTimefile << sim->timestep << std::endl;
			outputCompletionTimefile << sim->timestep << ",1," << std::endl;

		}
		else if (sim->timestep >= maximumNumSteps_v)
		{
			isRunning = false;
			std::cout << "Task Not completed, Time exceeded, and simulation will be terminated off" << std::endl;
			//outputCompletionTimefile << sim->timestep << std::endl;
		//	outputCompletionTimefile <<"Not completed within time"<< std::endl;

			int NsheepAtGoal = 0;
			for (int i = 0; i < env.sheepFlock->size(); i++) {
				if ((*env.sheepFlock)[i]->position_t.dist(env.PG) <= GoalRadius)
				{
					NsheepAtGoal++;
				}
			}

			outputCompletionTimefile << sim->timestep << "," << (float)NsheepAtGoal / (float)env.N << std::endl;



		}
	//return newRow;

}