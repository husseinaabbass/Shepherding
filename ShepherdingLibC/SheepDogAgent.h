#pragma once
#ifndef SHEEPDOGAGENT_EXPORT
#define SHEEPDOGAGENT_API __declspec(dllexport)
#else
#define SHEEPDOGAGENT_API __declspec(dllimport)
#endif

#include"Agents.h"
#include"SheepAgent.h"
#include<string>
#include <vector>
#include <list>
//#include "Traits.h"
#include "Behaviors.h"
#include <random>
#include "Vector2.h"




class SHEEPDOGAGENT_API SheepDogAgent : public Agent
{
private:

	Vector2f F_beta_j_c_t; //!< \f$F^t_{\beta_jc}\f$         Force vector, collecting vector of the \f$\beta_j\f$ agent at time \f$t\f$
	Vector2f F_beta_j_d_t; //!< \f$F^t_{\beta_jc}\f$         Force vector, driving vector of the \f$\beta_j\f$ agent at time \f$t\f$
	Vector2f  F_beta_j_E_t; //!<\f$F^t_{\beta_j\epsilon}\f$        Force vector, jittering movements by the \f$\beta_j\f$ agent at time \f$t\f$
	Vector2f F_beta_i_beta_k_t; //!< \f$F^t_{\beta_i \beta_k}\f$         Force vector, repulsion of \f$\pi_i\f$ agent away from other \f$\beta_{k\ne i}\f$ agent at time \f$t\f$
	Vector2f P_beta_j_d_t; //!< \f$P^t_{\beta_j \sigma_1}\f$         Position for driving by agent \f$j\f$ at time \f$t\f$;
	Vector2f P_beta_j_c_t; //!< \f$P^t_{\beta_j \sigma_2}\f$          Position for collection by agent \f$j\f$ at time \f$t\f$;

	Vector2f P_beta_j_cv_t; //!< \f$P^t_{\beta_j \sigma_2}\f$          Position for covering by agent \f$j\f$ at time \f$t\f$;
	Vector2f F_beta_j_cv_t;  // Force vector, covering force vector of the \f$\beta_j\f$ agent at time \f$t\f$
	float S_t_beta_j;		//!< Speed of agent \f$\beta\f$ at time \f$t\f$

	//std::vector<DetectedSheepRow> DetectedSheep;
	void UpdateDetectedSheepList();
	void UpdateSheepDogAgentLCM();


public:
	/// <summary>
	/// This function estimate the next location of the SheepDogAgent based on its current location, current forces, and current agent speed. It update the SheepDogAgent position_t attribute based on this estimation.
	/// </summary>
	void calculateSheepDogPositiont1();
	SheepDogAgent(float x1, float y1, int ID, float agentSpeed, int mode);


	/// <summary>
	/// Initializes a new instance of the <see cref="SheepDogAgent"/> class.
	/// </summary>
	/// <param name="xMin">The minimum possible x location.</param>
	/// <param name="xMax">The maximum possible x location.</param>
	/// <param name="yMin">The minimum possible y location.</param>
	/// <param name="yMax">The maximum possible y location.</param>
	/// <param name="ID">The Agent identifier.</param>
	/// <param name="agentSpeed">The agent speed.</param>
	SheepDogAgent(std::mt19937 generator, float xMin, float xMax, float yMin, float yMax, int ID, float agentSpeed, int mode);



	//setters
			/// <summary>
			/// Sets the current jittering force of this agent.
			/// </summary>
			/// <param name="F_beta_j_E_t">The Jittering force to set \f$F^t_{\beta_j\epsilon}\f$.</param>
	void set_F_beta_j_E_t(Vector2f  F_beta_j_E_t);


	/// <summary>
	/// Sets the current collecting force of this agent.
	/// </summary>
	/// <param name="F_beta_j_c_t">The collecting force to set \f$F^t_{\beta_jc}\f$.</param>
	void set_F_beta_j_c_t(Vector2f F_beta_j_c_t);

	void set_F_beta_j_cv_t(Vector2f F_beta_j_cv_t);

	/// <summary>
	/// Sets the current driving force of this agent.
	/// </summary>
	/// <param name="F_beta_j_d_t">The driving force to set \f$F^t_{\beta_jc}\f$ .</param>
	void set_F_beta_j_d_t(Vector2f F_beta_j_d_t);

	/// <summary>
	/// Sets the current driving position.
	/// </summary>
	/// <param name="P_beta_j_d_t">the driving position to set \f$P^t_{\beta_j \sigma_1}\f$.</param>
	void set_P_beta_j_d_t(Vector2f P_beta_j_d_t);

	/// <summary>
	/// Sets the current collecting position.
	/// </summary>
	/// <param name="P_beta_j_c_t">the collecting position to set \f$P^t_{\beta_j \sigma_2}\f$.</param>
	void set_P_beta_j_c_t(Vector2f P_beta_j_c_t);

	void set_P_beta_j_cv_t(Vector2f P_beta_j_c_t);

	/// <summary>
	/// Sets the speed of this agent.
	/// </summary>
	/// <param name="S_t_beta_j">The speed to set.</param>
	void set_S_t_beta_j(float S_t_beta_j);		//						Speed of beta at time t









//getters
		/// <summary>
		/// returns the jittering movements force vector
		/// </summary>
		/// <returns></returns>
	Vector2f  get_F_beta_j_E_t();
	/// <summary>
	/// returns the collecting force vector
	/// </summary>
	/// <returns></returns>
	Vector2f get_F_beta_j_c_t();
	Vector2f get_F_beta_j_cv_t();



	/// <summary>
	/// returns the SheepDog to SheepDog collision avoidance force vector
	/// </summary>
	/// <returns></returns>
	Vector2f get_F_beta_i_beta_k_t();

	/// <summary>
	/// returns the driving force vector
	/// </summary>
	/// <returns></returns>

	Vector2f get_F_beta_j_d_t();

	/// <summary>
	/// returns the driving position 
	/// </summary>
	/// <returns></returns>
	Vector2f get_P_beta_j_d_t();

	/// <summary>
	/// returns the collecting position 
	/// </summary>
	/// <returns></returns>
	Vector2f get_P_beta_j_c_t();
	Vector2f get_P_beta_j_cv_t();

	//std::vector<DetectedSheepRow> get_DetectedSheep();
	/// <summary>
	/// returns the speed of the agent
	/// </summary>
	/// <returns></returns>
	float get_S_t_beta_j();



};
