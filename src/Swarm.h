#ifndef SWARM_H
#define SWARM_H

#include "utils.h"
#include "Particle.h"

#include <vector>
#include <functional>
#include <limits>
#include <iostream>

class Swarm
{
public:
	/**
	 * @brief Constructor
	 * param[in] num_particles number of particles
	 * param[in] num_iters number of iterations
	 * param[in] lbs standard vector with problem lower bounds
	 * param[in] ubs standard vector with problem upper bounds
	 * param[in] global flag for global or knowledge of the best position. If false, each particle knows just the best position of the closest one.
	 */
	Swarm(int num_particles,
	 	  int num_iters,
	 	  std::vector<double> lbs,
		  std::vector<double> ubs,
		  bool glob = true);

	/**
	 * @brief Empty constructor
	 */
	Swarm();

	/**
	 * @brief Destructor
	 */
	~Swarm();
	
	/**
	 * @brief Initialise swarm
	 * param[in] num_particles number of particles
	 * param[in] num_iters number of iterations
	 * param[in] lbs standard vector with problem lower bounds
	 * param[in] ubs standard vector with problem upper bounds
	 * param[in] global flag for global or knowledge of the best position. If false, each particle knows just the best position of the closest one.
	 */
	void initialise(int num_particles,
 					int num_iters,
	 	       		std::vector<double> lbs,
		       		std::vector<double> ubs,
		 		    bool glob = true);
	
	/**
	 * @brief Optimization function
	 * param[in] fun function to minimizie
	 */
	void optimize(std::function<double(std::vector<double>)>);

	/**
	 * @brief Print results
	 */
	void printResults();

private:
	/**
	 * Swarm particles
	 */
	std::vector<Particle> particles;

	/**
	 * Problem lower bounds
	 */
	std::vector<double> lower_bounds;

	/**
	 * Problem upper bounds
	 */
	std::vector<double> upper_bounds;

	/**
	 * Problem dimensions
	 */
	uint n_dimensions;

	/**
	 * Number of iterations
	 */
	uint n_iterations;

	/**
	 * Number of particles
	 */
	uint n_particles;

	/**
	 * Swarm (global) best position
	 */
	std::vector<double> swarm_best_position;

	/**
	 * Swarm (global) best fitness
	 */
	double swarm_best_fitness;

	/**
	 * Global knowledge pf best fitness by the particles
	 */
	bool global;

	/**
	 * Default velocity parameters (Clerc and Kennedy constriction coefficients)
	 */
	double velocity_parameters[3] = {0.7298437881283576, 1.496179765663133, 1.496179765663133};

	/**
	 * @brief Initialise swarm by creating the particles
	 */
	void initialiseSwarm();

	/**
	 * @brief Update particles' positions and velocities
	 * param[in] fun function to minimizie
	 */
	void updateParticlesGlobal();

	/**
	 * @brief Update particles' positions and velocities with close firsts
	 * param[in] fun function to minimizie
	 */
	void updateParticlesCloseFirsts();

	std::function<double(std::vector<double>)> updateParticles;

};

#endif
