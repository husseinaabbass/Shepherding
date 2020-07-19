#pragma once
#ifndef SHEEPAGENT_EXPORT
#define SHEEPAGENT_API __declspec(dllexport)
#else
#define SHEEPAGENT_API __declspec(dllimport)
#endif

#include<string>
#include <vector>
#include <list>
//#include "Traits.h"
#include "Behaviors.h"
#include <random>
#include "Vector2.h"

#include"Agents.h"




class SHEEPAGENT_API SheepAgent : public Agent
{
private:

	Vector2f F_pi_i_beta_j_t;    //!<  \f$F^t_{ \pi_i\beta_j }\f$  Force vector, repulsion of \f$\pi_i\f$ agent away from \f$\beta_j\f$ agents at time \f$t\f$


	Vector2f F_pi_i_pi_k_t;   //!<\f$F^t_{ \pi_i\pi_{k} }\f$  Force vector, repulsion of \f$\pi_i\f$ agent away from other \f$\pi_{ k\ne i }\f$ agent at time \f$t\f$

	Vector2f F_pi_i_Lambda_t;   //!<\f$F^t_{ \pi_i{\Lambda^t_{\pi_i}} }\f$  Force vector, attraction to Local Centre of Mass for the neighbours of a \f$\pi_i\f$ agent at time \f$t\f$ 

	Vector2f F_pi_i_E_t;   //!<\f$F^t_{ \pi_i\epsilon }\f$  Force vector, jittering movements by the \f$\pi_i\f$ agent at time \f$t\f$ 

	float S_t_pi_i = 1;			//!< Speed of agent \f$\pi_i\f$ at time \f$t\f$

public:
	/// <summary>
	/// This function estimate the next location of the SheepAgent based on its current location, current forces, and current agent speed. It update the SheepAgent position_t attribute based on this estimation.
	/// </summary>
	void calculateSheepPositiont1();

	//SheepAgent(std::mt19937 generator, int xMin, int xMax, int yMin, int yMax, int ID);

	/// <summary>
	/// Initializes a new instance of the <see cref="SheepAgent"/> class.
	/// </summary>
	/// <param name="xMin">The minimum possible x location.</param>
	/// <param name="xMax">The maximum possible x location.</param>
	/// <param name="yMin">The minimum possible y location.</param>
	/// <param name="yMax">The maximum possible y location.</param>
	/// <param name="ID">The Agent identifier.</param>
	//SheepAgent(std::mt19937 generator, int xMin, int xMax, int yMin, int yMax, int ID);


	SheepAgent(float x1, float y1, int ID);

	//setters
	/// <summary>
	/// Sets the repulsion force of \f$pi_i\f$ agent away from \f$\beta_j\f$ agents at time \f$t\f$
	/// </summary>
	/// <param name="F_pi_i_beta_j_t">The predator repulsion force to set \f$F^t_{ \pi_i\beta_j }\f$.</param>
	void set_F_pi_i_beta_j_t(Vector2f F_pi_i_beta_j_t);

	/// <summary>
	/// Sets the collision avoidance force of \f$pi_i\f$ agent away from other \f$\pi_{ k\ne i }\f$ agent at time \f$t\f$
	/// </summary>
	/// <param name="F_pi_i_pi_k_t">The collision avoidance force to set \f$F^t_{ \pi_i\pi_{k} }\f$.</param>
	void set_F_pi_i_pi_k_t(Vector2f F_pi_i_pi_k_t);

	/// <summary>
	/// Sets the attraction force to the local centre of mass for the neighbours of this agent.
	/// </summary>
	/// <param name="F_pi_i_Lambda_t">The cohesion force to set \f$F^t_{ \pi_i{\Lambda^t_{\pi_i}} }\f$.</param>
	void set_F_pi_i_Lambda_t(Vector2f F_pi_i_Lambda_t);

	/// <summary>
	/// Sets the current jittering force of this agent.
	/// </summary>
	/// <param name="F_pi_i_E_t">The Jittering force to set \f$F^t_{\pi_i\epsilon}\f$.</param>
	void set_F_pi_i_E_t(Vector2f F_pi_i_E_t);

	/// <summary>
	/// Sets the speed of this agent.
	/// </summary>
	/// <param name="S_t_pi_i">The speed to set.</param>
	void set_S_t_pi_i(float S_t_pi_i);



	//getters

	/// <summary>
	/// Returns the predator avoidance force.
	/// </summary>
	/// <returns></returns>
	Vector2f get_F_pi_i_beta_j_t();


	/// <summary>
	/// Returns the current collision avoidance from friends force.
	/// </summary>
	/// <returns></returns>
	Vector2f get_F_pi_i_pi_k_t();


	/// <summary>
	/// Returns the current cohesion force (attraction to LCM) .
	/// </summary>
	/// <returns></returns>
	Vector2f get_F_pi_i_Lambda_t();


	/// <summary>
	/// Returns the current jittering force.
	/// </summary>
	/// <returns></returns>
	Vector2f get_F_pi_i_E_t();



	/// <summary>
	/// Returns the current agent speed.
	/// </summary>
	/// <returns></returns>
	float get_S_t_pi_i();


};