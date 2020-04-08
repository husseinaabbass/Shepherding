#include "stdafx.h"
#include "Terrain.h"



StaticObstaclesList::StaticObstaclesList(std::mt19937 generator, float density, float radius, float xMin, float xMax, float yMin, float yMax)
{
	int h = yMax - yMin;
	int w = xMax - xMin;
	int numberOfPoints = h * w;
	int numberOfObstacles = int(density * numberOfPoints);
	//std::uniform_real_distribution<float> distribution1(xMin, xMax);
	//std::uniform_real_distribution<float> distribution2(yMin, yMax);
	std::uniform_int_distribution<int> distribution1(xMin, xMax);
	std::uniform_int_distribution<int> distribution2(yMin, yMax);
	for (int i = 0; i < numberOfObstacles; i++)
	{
		float x1 = distribution1(generator);
		float y1 = distribution2(generator);

		StaticObstacle* o = new StaticObstacle( x1, y1, radius);
		this->push_back(o);
	}

}

//StaticObstacle::StaticObstacle(std::mt19937 generator, int xMin, int xMax, int yMin, int yMax, float radius)
//{
//	//this->position_t.x = xMin + rand() % ((xMax + 1) - xMin);
//	//this->position_t.y = yMin + rand() % ((yMax + 1) - yMin);
//	
//	this->position_t.x = x1;
//	this->position_t.y = y1;
//	this->radius = radius;
//}
StaticObstacle::StaticObstacle( float x1, float y1, float radius)
{
	//this->position_t.x = xMin + rand() % ((xMax + 1) - xMin);
	//this->position_t.y = yMin + rand() % ((yMax + 1) - yMin);

	this->position_t.x = x1;
	this->position_t.y = y1;
	this->radius = radius;
}

//void Terrain::setStaticObstacles(float density, float radius, int xMin, int xMax, int yMin, int yMax)
//{
//	StaticObstaclesList(density, radius, xMin, xMax, yMin, yMax);
//}
//
//StaticObstaclesList Terrain::getStaticObstacles()
//{
//	return this->staticObstacles;
//}
