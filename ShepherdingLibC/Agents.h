//#pragma once
//#ifndef AGENTS_EXPORT
//#define AGENTS_API __declspec(dllexport)
//#else
//#define AGENTS_API __declspec(dllimport)
//#endif
//#ifndef AGENTS_H
//#define AGENTS_H

#pragma once
#ifndef AGENTS_EXPORT
#define AGENTS_API __declspec(dllexport)
#else
#define AGENTS_API __declspec(dllimport)
#endif
//#ifndef AGENTS_H
//#define AGENTS_H

#include<string>
#include <vector>
#include <list>
#include "Traits.h"
#include "Behaviors.h"
#include <random>

//#include "Environment.h"
#include "Vector2.h"
	//class AGENTS_API Globals
	//{
	//	//Omega_t Set of pi agents at time t that have not reached the goal; that is, the remaining agents to complete the mission.
	//	//card_Omega_t  Number of pi agents at time t that have not reached the goal; that is, the remaining agents to complete the mission.//

	//};
	//

	//class AGENTS_API Agent
/// <summary>
/// Class Agent is a superclass that represent any type of agent within the library. SheepAgent and SheepDogAgent are examples of subclass of Agent class.
/// Shared prosperities of Class Agent includes the agent type, the current position, next position, local centre of mass, and the list of behaviours that this agent has.
/// </summary>
class AGENTS_API Agent
	{
	public:
		/// <summary>
		/// Unique identifier by agent. 
		/// </summary>
		int agentID;
		/// <summary>
		/// The agent type: Examples are: "Sheep" and "SheepDog".
		/// </summary>
		std::string agentType;
		/// <summary>
		/// The current position of the agent, stored in a vector of <x,y> 
		/// </summary>
		Vector2f position_t;
		/// <summary>
		/// The next position of the agent,  stored in a vector of <x,y>
		/// </summary>
		Vector2f position_t1;
		/// <summary>
		/// The local centre of mass of sheep in neighbourhood,  stored in a vector of <x,y>
		/// </summary>
		Vector2f Lambda_t;   

		/// <summary>
		/// A list of the agent behaviors
		/// </summary>
		BehaviorList agentBehaviors;
		
		//Vector2f P_beta_j_d_t;
		//Vector2f P_beta_j_c_t; //P_beta_j_c_t          Position for collection by agent j at time t;

		/// <summary>
		/// The total of the forces that affects this agent to estimate the next location
		/// Total force vector: equivalent to \f$F^t_{\beta_j}\f$ movement vector of the \f$\beta_j\f$ agent at time t, and \f$F^t_{\pi_i}\f$ Force vector, movement vector of the \f$pi_i\f$ agent at time t
		/// </summary>
		Vector2f F_t;  
		Vector2f F_obst_t;
		//int toBeCollectedSheepID;
		std::string LoggingSupportingInformation;


		/// <summary>
		/// A constructor to initialize a new instance of the <see cref="Agent"/> class.
		/// </summary>
		Agent();

	
	private:

		Traits agentTraits;
		

		

	};


	
	class AGENTS_API SheepDogAgent : public Agent
	{
	private:
		
		Vector2f F_beta_j_c_t; //!< \f$F^t_{\beta_jc}\f$         Force vector, collecting vector of the \f$\beta_j\f$ agent at time \f$t\f$
		Vector2f F_beta_j_d_t; //!< \f$F^t_{\beta_jc}\f$         Force vector, driving vector of the \f$\beta_j\f$ agent at time \f$t\f$
		Vector2f  F_beta_j_E_t; //!<\f$F^t_{\beta_j\epsilon}\f$        Force vector, jittering movements by the \f$\beta_j\f$ agent at time \f$t\f$
		Vector2f F_beta_i_beta_k_t; //!< \f$F^t_{\beta_i \beta_k}\f$         Force vector, repulsion of \f$\pi_i\f$ agent away from other \f$\beta_{k\ne i}\f$ agent at time \f$t\f$
		Vector2f P_beta_j_d_t; //!< \f$P^t_{\beta_j \sigma_1}\f$         Position for driving by agent \f$j\f$ at time \f$t\f$;
		Vector2f P_beta_j_c_t; //!< \f$P^t_{\beta_j \sigma_2}\f$          Position for collection by agent \f$j\f$ at time \f$t\f$;

		float S_t_beta_j ;		//!< Speed of agent \f$\beta\f$ at time \f$t\f$

		//Vector2f F_beta_j_cd_t; //F_beta_j_cd_t         Force vector, driving and collection vector of the beta_j agent at time t
		//SheepPtrList Omega_beta_j_pi;  //Omega_beta_j_pi Set of pi agents a beta_j agent operates on
		//SheepPtrList Omega_beta_j_pi_t; //Omega_beta_j_pi_t Set of pi agents a beta_j agent operates on at time t
		//int card_Omega_beta_j_pi; //card_Omega_beta_j_pi (20) Number of pi agents a beta_j agent operates on
		//int card_Omega_beta_j_pi_t; //card_Omega_beta_j_pi_t Number of pi agents a beta_j agent operates on at time t
		//Vector2f Lambda_beta_j_t; //Lambda_beta_j_t       Local centre of mass for agent beta_j at time t
		//Vector2f P_beta_j_t; //!< P_beta_j_t            Position of agent beta_j at time t
		//Vector2f Gamma_beta_j_t; //!< Gamma__beta_j_t       Global centre of mass for agent beta_j at time t
			//Vector2f F_beta_j_t; //!< F_beta_j_t            Force vector, movement vector of the \f$\beta_j\f$ agent at time \f$t\f$
	
	public:
		/// <summary>
		/// This function estimate the next location of the SheepDogAgent based on its current location, current forces, and current agent speed. It update the SheepDogAgent position_t attribute based on this estimation.
		/// </summary>
		void calculateSheepDogPositiont1();

		SheepDogAgent(float x1, float y1, int ID, float agentSpeed, int mode);

		SheepDogAgent(std::mt19937 generator, float x1, float y1, int ID, float agentSpeed, int mode);

		//SheepDogAgent(std::mt19937 generator, int xMin, int xMax, int yMin, int yMax, int ID, float agentSpeed, int mode);
		
		
		
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
		
		/// <summary>
		/// Sets the speed of this agent.
		/// </summary>
		/// <param name="S_t_beta_j">The speed to set.</param>
		void set_S_t_beta_j(float S_t_beta_j);		//						Speed of beta at time t



		//void set_F_beta_j_cd_t(Vector2f F_beta_j_cd_t); //F_beta_j_cd_t         Force vector, driving and collection vector of the beta_j agent at time t
		//void set_Lambda_beta_j_t(Vector2f Lambda_beta_j_t); //Lambda_beta_j_t       Local centre of mass for agent beta_j at time t
		//void set_Omega_beta_j_pi(std::list<SheepAgent*> Omega_beta_j_pi);  //Omega_beta_j_pi Set of pi agents a beta_j agent operates on
		//void set_Omega_beta_j_pi_t(std::list<SheepAgent*> Omega_beta_j_pi_t); //Omega_beta_j_pi_t Set of pi agents a beta_j agent operates on at time t
		//void set_card_Omega_beta_j_pi(int card_Omega_beta_j_pi); //card_Omega_beta_j_pi (20) Number of pi agents a beta_j agent operates on
		//void set_card_Omega_beta_j_pi_t(int card_Omega_beta_j_pi_t); //card_Omega_beta_j_pi_t Number of pi agents a beta_j agent operates on at time t
		//void set_F_beta_j_t(Vector2f F_beta_j_t); //F_beta_j_t            Force vector, movement vector of the beta_j agent at time t
		//		void set_P_beta_j_t(Vector2f P_beta_j_t); //P_beta_j_t            Position of agent beta_j at time t
//		void set_Gamma_beta_j_t(Vector2f Gamma_beta_j_t); //Gamma__beta_j_t       Global centre of mass for agent beta_j at time t

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

		/// <summary>
		/// returns the speed of the agent
		/// </summary>
		/// <returns></returns>
		float get_S_t_beta_j();		


		//Vector2f get_Gamma_beta_j_t(); //Gamma__beta_j_t       Global centre of mass for agent beta_j at time t
		//Vector2f get_F_beta_j_t(); //F_beta_j_t            Force vector, movement vector of the beta_j agent at time t
		//Vector2f get_P_beta_j_t(); //P_beta_j_t            Position of agent beta_j at time t
		//Vector2f get_Lambda_beta_j_t(); //Lambda_beta_j_t       Local centre of mass for agent beta_j at time t
		//std::list<SheepAgent*> get_Omega_beta_j_pi();  //Omega_beta_j_pi Set of pi agents a beta_j agent operates on
		//std::list<SheepAgent*> get_Omega_beta_j_pi_t(); //Omega_beta_j_pi_t Set of pi agents a beta_j agent operates on at time t
		//int get_card_Omega_beta_j_pi(); //card_Omega_beta_j_pi (20) Number of pi agents a beta_j agent operates on
		//int get_card_Omega_beta_j_pi_t(); //card_Omega_beta_j_pi_t Number of pi agents a beta_j agent operates on at time t
		//Vector2f get_F_beta_j_cd_t(); //F_beta_j_cd_t         Force vector, driving and collection vector of the beta_j agent at time t

	};

	class AGENTS_API SheepAgent : public Agent
	{
	private:
		
		Vector2f F_pi_i_beta_j_t;    //!<  \f$F^t_{ \pi_i\beta_j }\f$  Force vector, repulsion of \f$\pi_i\f$ agent away from \f$\beta_j\f$ agents at time \f$t\f$
		
					
			Vector2f F_pi_i_pi_k_t;   //!<\f$F^t_{ \pi_i\pi_{k} }\f$  Force vector, repulsion of \f$\pi_i\f$ agent away from other \f$\pi_{ k\ne i }\f$ agent at time \f$t\f$

		Vector2f F_pi_i_Lambda_t;   //!<\f$F^t_{ \pi_i{\Lambda^t_{\pi_i}} }\f$  Force vector, attraction to Local Centre of Mass for the neighbours of a \f$\pi_i\f$ agent at time \f$t\f$ 

		Vector2f F_pi_i_E_t;   //!<\f$F^t_{ \pi_i\epsilon }\f$  Force vector, jittering movements by the \f$\pi_i\f$ agent at time \f$t\f$ 
		
		//Vector2f F_pi_i_t; //F_pi_i_t              Force vector, movement vector of the pi_i agent at time t
		
		//SheepPtrList Omega_pi_i_pi;// Omega_pi_i_pi Set of pi agents (neighbourhood) a pi_i agent operates on
		//int card_Omega_pi_i_pi = 0; // card_Omega_pi_i_pi (1–200) Number of pi agents (neighbourhood) a pi_i agent operates on
		//Vector2f P_pi_i_t; //P_pi_i_t              Position of agent pi_i at time t
		//Vector2f Lambda_t; //Lambda_t Local centre of mass for agent pi_i at time t
		//Vector2f Gamma_pi_i_t; //Gamma_pi_i_t          Global centre of mass for agent pi_i at time t
		
		float S_t_pi_i=1;			//!< Speed of agent \f$\pi_i\f$ at time \f$t\f$

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

//		void set_F_pi_i_t(Vector2f); //F_pi_i_t              Force vector, movement vector of the pi_i agent at time t

		//void set_Omega_pi_i_pi(std::list<SheepPtr*> Omega_pi_i_pi);// Omega_pi_i_pi Set of pi agents (neighbourhood) a pi_i agent operates on
		//void set_card_Omega_pi_i_pi(int card_Omega_pi_i_pi); // card_Omega_pi_i_pi (1–200) Number of pi agents (neighbourhood) a pi_i agent operates on
		//void set_P_pi_i_t(Vector2f P_pi_i_t); //P_pi_i_t              Position of agent pi_i at time t
		//void set_Lambda_t(Vector2f Lambda_t); //Lambda_t Local centre of mass for agent pi_i at time t
		//void set_Gamma_pi_i_t(Vector2f Gamma_pi_i_t); //Gamma_pi_i_t          Global centre of mass for agent pi_i at time t


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


		//Vector2f get_F_pi_i_t(); //F_pi_i_t              Force vector, movement vector of the pi_i agent at time t
		//std::list<SheepPtr*> get_Omega_pi_i_pi();// Omega_pi_i_pi Set of pi agents (neighbourhood) a pi_i agent operates on
		//int get_card_Omega_pi_i_pi(); // card_Omega_pi_i_pi (1–200) Number of pi agents (neighbourhood) a pi_i agent operates on
		//Vector2f get_P_pi_i_t(); //P_pi_i_t              Position of agent pi_i at time t
		//Vector2f get_Lambda_t(); //Lambda_t Local centre of mass for agent pi_i at time t
		//Vector2f get_Gamma_pi_i_t(); //Gamma_pi_i_t          Global centre of mass for agent pi_i at time t

	};




	

	
	
//#endif