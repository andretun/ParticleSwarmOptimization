#ifndef SWARM_H
#define SWARM_H

#include "utils.h"
#include "Particle.h"

#include <functional>
#include <iostream>
#include <fstream>

/**
 * @brief Class for PSO swarm
 */
class Swarm {
public:
	/**
	 * @brief Empty constructor
	 * @details Initializes best iterations to zero
	 */
	Swarm();

	/**
	 * @brief Constructor
	 * @see Swarm()
	 * @see initialise()
	 * @param[in] num_particles number of particles
	 * @param[in] num_iters number of iterations
	 * @param[in] lbs standard vector with problem lower bounds
	 * @param[in] ubs standard vector with problem upper bounds
	 * @param[in] output csv file name (defaults to "output")
	 */
	Swarm(int num_particles,
	 	  int num_iters,
	 	  std::vector<double> lbs,
		  std::vector<double> ubs,
		  std::string name = "output");

	/**
	 * @brief Destructor
	 */
	~Swarm();
	
	/**
	 * @brief Initialise swarm
	 * @param[in] num_particles number of particles
	 * @param[in] num_iters number of iterations
	 * @param[in] lbs standard vector with problem lower bounds
	 * @param[in] ubs standard vector with problem upper bounds
	 * @param[in] output csv file name (defaults to "output")
	 */
	void initialise(int num_particles,
 					int num_iters,
	 	       		std::vector<double> lbs,
		       		std::vector<double> ubs,
		    	    std::string name = "output");
	
	/**
	 * @brief Optimization function
	 * @param[in] fun function to minimizie
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
	 * Swarm (global) best iteration
	 */
	uint swarm_best_iter;

	/**
	 * Swarm (global) best particle
	 */
	uint swarm_best_particle;

	/**
	 * Swarm (global) best fitness
	 */
	double swarm_best_fitness;

	/**
	 * Default velocity parameters (Clerc and Kennedy constriction coefficients)
	 */
	double velocity_parameters[3] = {0.7298437881283576, 1.496179765663133, 1.496179765663133};

	/**
	 * Velocity parameters
	 */
	double vel_par[3];

	/**
	 * Output csv file name
	 */
	std::string outname;

	/**
	 * @brief Update particles' positions and velocities
	 */
	void updateParticles();

	/**
	 * @brief Print final particles position to output csv file
	 * @param[in] s string to prepend at output file name
	 */
	void printToCsv(std::string s);

	/**
	 * @brief Evolve velocity coefficients through iterations
	 * @param[in] iter_index current iteration index
	 */
	void evolveCoefficients(uint iter_index);

};

#endif
