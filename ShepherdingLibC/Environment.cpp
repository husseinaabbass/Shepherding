#include "stdafx.h"
#include "Environment.h"
//Flock Environment::flock;

//Environment MyEnv;



//Environment::Environment()
//{
//	FieldHeight = 100;
//	FieldWidth = 1000;
//	N = 1;	//(1--201)          & Cardinality of Pi
//	M = 1;// (1--20)         & Cardinality of B
//	R_pi_beta = 65;		// (65u)			& pi sensing range for beta
//	Ra_pi_pi = 2;			// (2u)				& pi collision avoidance range for pi
//	W_pi_pi = 2;			// (2)				& pi repulsion strength from pi
//	W_pi_beta = 1;		// (1)				& pi repulsion strength from beta
//	W_pi_Lambda = 1.05;	// (1.05)			& pi attraction strength to Lambda
//	W_pi_upsilon = 0.5;	// (0.5)			& Strength of pi previous direction
//	W_e_pi_i = 0.3;		// (0.3)			& Strength of sheep pi_j angular noise
//	W_e_beta_j = 0.3;		// (0.3)			& Strength of shepherd beta_j angular noise
//	S_t_beta_j = 1;		//					& Speed of beta at time t
//	eta = 0.05;			//(0.05)			& Probability of moving per time step while grazing
//S_t_pi_i
//	//env.flock = Flock(numSheepAgents, numSheepDogAgents, fieldStartX, fieldStartX + fieldWidth, fieldStartY, fieldStartY + fieldHeight);
//}





Environment & Environment::getInstance()
{
	// TODO: insert return statement here
	static Environment    instance; // Guaranteed to be destroyed.
						  // Instantiated on first use.
	return instance;
}
