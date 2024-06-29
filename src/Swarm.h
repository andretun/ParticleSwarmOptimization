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
	 */
	Swarm(int num_particles,
	 	  int num_iters,
	 	  std::vector<double> lbs,
		  std::vector<double> ubs);

	/**
	 * @brief Empty constructor
	 */
	Swarm();

	/**
	 * @brief Destructor
	 */
	~Swarm();
	
	/**
	 * @brief Optimization function
	 * param[in] fun function to minimizie
	 */
	void optimize(std::function<double(std::vector<double>)>);

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
	void updateParticles();
};

#endif
