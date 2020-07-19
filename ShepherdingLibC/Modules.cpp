#include "Modules.h"
#include "Agents.h"
#include "Environment.h"
#include <algorithm>
#include <cmath>


void UpdateSheepBehaviors(SheepAgent* sheep, int timestep)
{
	sheep->agentBehaviors.clear();

	sheep->agentBehaviors.push_back(new Jittering(sheep));
	sheep->agentBehaviors.push_back(new AttractionBehavior(sheep));
	sheep->agentBehaviors.push_back(new CollisionAvoidanceFriends(sheep));
	sheep->agentBehaviors.push_back(new CollisionAvoidanceOpponents(sheep));
	sheep->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(sheep));
	sheep->agentBehaviors.push_back(new FollowingPreviousDirectionBehavior(sheep));
}

void UpdateSheepDogBehaviors(SheepDogAgent* sheepDog, int timestep, int mode)
{
	sheepDog->agentBehaviors.clear();
	//this->agentBehaviors.push_back(new Jittering(this));
	if (mode == 0) // if mode = 0 -> single sheepDog
	{
		//temporary disable all behaviors to test the covering behavior
		sheepDog->agentBehaviors.push_back(new Jittering(sheepDog));

		sheepDog->agentBehaviors.push_back(new Driving(sheepDog));
		sheepDog->agentBehaviors.push_back(new Collecting(sheepDog));
		sheepDog->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(sheepDog));

		//Below is an example of using the covering behavior for the first 200 timesteps
		//Environment& env = Environment::getInstance();
		//if (timestep == 1)
		//{
		//	env.openCoveringTask = true;
		//	std::list<Vector2f> points_to_visit = computeCoveringPoints("snakeInteger",5);
		//	//std::list<Vector2f> points_to_visit = computeCoveringPoints("Hilbert",3);
		//	
		//	
		//	env.coveringPoints = points_to_visit;
		//	sheepDog->agentBehaviors.push_back(new Covering(sheepDog));
		//	sheepDog->agentBehaviors.push_back(new Jittering(sheepDog));
		//}
		//else if (timestep < 200)
		//{

		//	sheepDog->agentBehaviors.push_back(new Covering(sheepDog));
		//	sheepDog->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(sheepDog));
		//	sheepDog->agentBehaviors.push_back(new Jittering(sheepDog));

		//}
		//else
		//{
		//	sheepDog->agentBehaviors.push_back(new Driving(sheepDog));
		//	sheepDog->agentBehaviors.push_back(new Collecting(sheepDog));
		//	sheepDog->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(sheepDog));
		//	sheepDog->agentBehaviors.push_back(new Jittering(sheepDog));
		//}

	}
	else //mode=1 -> multi-sheepdog
	{
		sheepDog->agentBehaviors.push_back(new DrivingMultiSheepDogMode(sheepDog));
		sheepDog->agentBehaviors.push_back(new CollectingMultiSheepDogMode(sheepDog));
		sheepDog->agentBehaviors.push_back(new CollisionAvoidanceFriends(sheepDog));
		sheepDog->agentBehaviors.push_back(new CollisionAvoidanceStaticObstacles(sheepDog));
		sheepDog->agentBehaviors.push_back(new Jittering(sheepDog));

	}
}

std::list<Vector2f> computeCoveringPoints(std::string coveringAlgorithm, int parameter)
{
	Environment& env = Environment::getInstance();

	std::list<Vector2f>points;

	if (coveringAlgorithm == "snakeInteger") 
		//the parameter variable for snake covering algorithmn reflects the step size between each two consecutive x,y field location to be visited
	{
		int fieldWidth = env.FieldWidth;
		int fieldHeight = env.FieldHeight;

		for (int j = env.FieldStartY + fieldHeight - 1; j > 1 + env.FieldStartY;  j -= parameter)
		{
			for (int i = env.FieldStartX + fieldWidth - 1; i >= env.FieldStartX + 1;  i -= parameter)
			{
				if (fmod(j, 2) == 1)
				{
					points.push_back(Vector2f(i, j));

				}
				else
				{
					points.push_back(Vector2f(fieldWidth - i + (2 * env.FieldStartX), j));
				}
			}

		}
	}
	else if (coveringAlgorithm == "Hilbert")
		//the parameter variable for Hilbert covering algorithmn reflects the level/order of Hilbert algorithm
		//the lower the number, the less points to be visited, and the larger the distance between these points

	{
		int fieldWidth = env.FieldWidth;
		int fieldHeight = env.FieldHeight;
		//points = hilbert(2);

		std::list<Vector2f> unscaled_covering_points = hilbert(parameter);
		std::vector<float> unscaled_x;
		std::vector<float> unscaled_y;

		std::list<Vector2f>::iterator iter;

		for (iter = unscaled_covering_points.begin(); iter != unscaled_covering_points.end(); iter++)
		{
			unscaled_x.push_back(iter->x);
			unscaled_y.push_back(iter->y);
		}

		// rescaling and shifting to [0, 1]

		// find maximum x value;
		float max_x= unscaled_x[0];
		for (int i = 1; i < unscaled_x.size(); i++)
		{
			if (unscaled_x[i] > max_x)
			{
				max_x = unscaled_x[i];
			}
		}
		float max_y = unscaled_y[0];
		for (int i = 1; i < unscaled_y.size(); i++)
		{
			if (unscaled_y[i] > max_y)
			{
				max_y = unscaled_y[i];
			}
		}

		float xScaling = (float) 0.5 / max_x;
		float yScaling = (float) 0.5 / max_y;

		std::vector<float> x_scaled_0_1;
		std::vector<float> y_scaled_0_1;

		for (int i = 0; i < unscaled_x.size(); i++)
		{
			x_scaled_0_1.push_back( (unscaled_x[i] *xScaling) + 0.5);
			y_scaled_0_1.push_back( (unscaled_y[i] * yScaling) + 0.5);
		}


		// rescaling to [0, fieldWidth], [0, fieldHeight]
	

		for (int i = 0; i < unscaled_x.size(); i++)
		{
			//points.push_back(Vector2f(x_scaled_0_1[i] * fieldWidth, y_scaled_0_1[i] * fieldHeight));
			points.push_back(Vector2f(env.FieldStartX+ (x_scaled_0_1[i] * fieldWidth), env.FieldStartY + (fieldHeight-(y_scaled_0_1[i] * fieldHeight))));

		}
		


	}

	return points;
}

std::list<Vector2f> hilbert(int n)
{
	std::vector<float> x;
	std::vector<float> y;
	std::list<Vector2f> xy_pairs;
	if (n <= 0)
	{
		//x.push_back(0);
		//y.push_back(0);
		Vector2f singlePair = Vector2f();

		xy_pairs.push_back(singlePair);
	}
	else
	{
		std::list<Vector2f> xy_pairs_nested = hilbert(n - 1);
		std::list<Vector2f>::iterator iter;


		for (iter = xy_pairs_nested.begin(); iter != xy_pairs_nested.end(); iter++)
		{
			x.push_back(0.5 * (-0.5 + iter->y));
		}
		for (iter = xy_pairs_nested.begin(); iter != xy_pairs_nested.end(); iter++)
		{
			x.push_back(0.5 * (-0.5 + iter->x));
		}
		for (iter = xy_pairs_nested.begin(); iter != xy_pairs_nested.end(); iter++)
		{
			x.push_back(0.5 * (0.5 + iter->x));
		}
		for (iter = xy_pairs_nested.begin(); iter != xy_pairs_nested.end(); iter++)
		{
			x.push_back(0.5 * (0.5 - iter->y));
		}


		for (iter = xy_pairs_nested.begin(); iter != xy_pairs_nested.end(); iter++)
		{
			y.push_back(0.5 * (-0.5 + iter->x));
		}
		for (iter = xy_pairs_nested.begin(); iter != xy_pairs_nested.end(); iter++)
		{
			y.push_back(0.5 * (0.5 + iter->y));
		}
		for (iter = xy_pairs_nested.begin(); iter != xy_pairs_nested.end(); iter++)
		{
			y.push_back(0.5 * (0.5 + iter->y));
		}
		for (iter = xy_pairs_nested.begin(); iter != xy_pairs_nested.end(); iter++)
		{
			y.push_back(0.5 * (-0.5 - iter->x));
		}



		for (int i = 0; i < x.size(); i++)
		{
			xy_pairs.push_back(Vector2f(x[i], y[i]));
		}
		

	}
	return xy_pairs;
}
