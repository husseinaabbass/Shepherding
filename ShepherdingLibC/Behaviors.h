#pragma once
#ifndef BEHAVIORS_EXPORT
#define BEHAVIORS_API __declspec(dllexport)
#else
#define BEHAVIORS_API __declspec(dllimport)
#endif
#include <vector>
#include <list>
#include "Vector2.h"
#include<string>

//#include "Environment.h"

//#include "Agents.h"

//namespace Shepherding
//{
class Agent;
class SheepList;

	class BEHAVIORS_API Behavior
	{
	public:
		virtual  Vector2f GetForce();
		float Weight;
		float GetMagnitude();
		std::string behaviorType;
	private:
		void FindSheepNotAtGoal();
		// %todo check this function
		
	protected:

		Agent* agent;
		//SheepList SenseSheepInNeighborhood(Agent* agent, int targetSizeOfNeighborhood);
		float magnitude;

	};

	
	class BEHAVIORS_API BehaviorList : public std::list<Behavior*>
	{
	public:
		//SheepDogsList();
		//SheepDogsList(int numberSheepDogs);
	};


	class BEHAVIORS_API RepulsionBehaviorM1 : public Behavior //Modulated repulsion of type 1 ==> low repulsion as in the case of avoiding collision with friends
	{
	public:
		Vector2f GetForce() override;
  float GetMagnitude();

	};

	class BEHAVIORS_API RepulsionBehaviorM2 : public Behavior //Modulated repulsion of type 2 ==> high repulsion as in the case of avoiding collision with predator
	{
	public:
		Vector2f GetForce() override;
  float GetMagnitude();

	};



	class BEHAVIORS_API AttractionBehavior : public Behavior
	{
	public:
		Vector2f GetForce() override;
		float GetMagnitude();
		AttractionBehavior(Agent* agent);
	};

	class BEHAVIORS_API Covering : public Behavior
	{
	public:
		Vector2f GetForce() override;
		float GetMagnitude();
		Covering(Agent* agent);
		Vector2f GetNextCoveringPosition();
	};


	class BEHAVIORS_API FollowingPreviousDirectionBehavior : public Behavior
	{
	public:
		Vector2f GetForce() override;
		float GetMagnitude();
		FollowingPreviousDirectionBehavior(Agent* agent);

	};


	class BEHAVIORS_API CollisionAvoidanceFriends : public RepulsionBehaviorM1
	{
	public :
		Vector2f GetForce() override;
		float GetMagnitude();
		CollisionAvoidanceFriends( Agent * agent);

		//CollisionAvoidanceFriends(float weight);

	}	;

	class BEHAVIORS_API CollisionAvoidanceOthers : public RepulsionBehaviorM1
	{
	public:
		Vector2f GetForce() override;


	};

	class BEHAVIORS_API CollisionAvoidanceOpponents : public RepulsionBehaviorM2
	{
	public:
		Vector2f GetForce() override;
		float GetMagnitude();
		CollisionAvoidanceOpponents(Agent * agent);


	};

	class BEHAVIORS_API CollisionAvoidanceStaticObstacles : public RepulsionBehaviorM2
	{
	public:
		Vector2f GetForce() override;
		float GetMagnitude();
		CollisionAvoidanceStaticObstacles(Agent* agent);

	};

	class BEHAVIORS_API CollisionAvoidanceDynamicObstacles : public RepulsionBehaviorM2
	{
	public:
		Vector2f GetForce() override;


	};

	class BEHAVIORS_API Jittering : public Behavior
	{
	public:
		Vector2f GetForce() override;
		Jittering(Agent* agent);

	};

	class BEHAVIORS_API Driving : public Behavior
	{
	public:
		Driving(Agent* agent);
		Vector2f GetForce();

		Vector2f GetDrivingPosition();
	};

	class BEHAVIORS_API DrivingMultiSheepDogMode : public Behavior
	{
	public:
		DrivingMultiSheepDogMode(Agent * agent);
		Vector2f GetForce();

		Vector2f GetDrivingPosition();
	};

	class BEHAVIORS_API Collecting : public Behavior
	{
	public:
		Collecting(Agent* agent);
		Vector2f GetForce();
		
		Vector2f GetCollectingPosition();

	};

	class BEHAVIORS_API CollectingMultiSheepDogMode : public Behavior
	{
	public:
		CollectingMultiSheepDogMode(Agent* agent);
		Vector2f GetForce();

		Vector2f GetCollectingPosition();

	};


	
//}
