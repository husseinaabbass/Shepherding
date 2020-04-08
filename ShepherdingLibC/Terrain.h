#pragma once
#ifndef TERRAIN_EXPORT
#define TERRAIN_API __declspec(dllexport)
#else
#define TERRAIN_API __declspec(dllimport)
#endif

#include <list>
#include <vector>
#include "Vector2.h"
#include <random>

class TERRAIN_API Obstacle
{
public:Vector2f position_t;
float radius;

};
class TERRAIN_API StaticObstacle : public Obstacle
{
public: 
	  //StaticObstacle(std::mt19937 generator, float xMin, float xMax, float yMin, float yMax, float radius);
	  //StaticObstacle(std::mt19937 generator, float x1, float y1, float radius);
	  StaticObstacle(float x1, float y1, float radius);
};

class TERRAIN_API DynamicObstacle : public Obstacle
{
private:
	Vector2f position_t1;

public: void updatePositiont();
};

class TERRAIN_API Fence : public Obstacle
{
	//private:
	//	std::vector<vector<float>> position_t;



};





class TERRAIN_API StaticObstaclesList : public  std::vector<StaticObstacle*>
{

//public:	  StaticObstaclesList(float density, float radius, int xMin, int xMax, int yMin, int yMax);

public: StaticObstaclesList(std::mt19937 generator, float density, float radius, float xMin, float xMax, float yMin, float yMax);

};
class TERRAIN_API DynamicObstaclesList : public std::list<DynamicObstacle*>
{

};
class TERRAIN_API FencesList : public std::list<Fence*>
{

};


class TERRAIN_API Communication {
	//topology
	//protocols
	//messages
};

class TERRAIN_API Atmosphere {};


class TERRAIN_API Terrain {

private:
	DynamicObstaclesList dynamicObstacles;
	FencesList fences;
public:
	//void setStaticObstacles(float density, float radius, int xMin, int xMax, int yMin, int yMax);
	StaticObstaclesList* staticObstacles;

	//StaticObstaclesList getStaticObstacles();

};
