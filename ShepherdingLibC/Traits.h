#pragma once
#ifndef TRAITS_EXPORT
#define TRAITS_API __declspec(dllexport)
#else
#define TRAITS_API __declspec(dllimport)
#endif

#include "Agents.h"



class PhysicalTraits
{
public:
	float sensingRangeHomogeneous = 0;
	float sensingRangeHetrogeneous = 0;
	float maximumSpeed = 0;

};

class CognitiveTraits
{
};

class PersonalityTraits
{

};

class TRAITS_API Traits {

	PhysicalTraits agentPhysicalTraits;
	CognitiveTraits agentCognitiveTraits;
	PersonalityTraits agentPersonalityTraits;

};



