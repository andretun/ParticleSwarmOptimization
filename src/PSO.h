/**
 * @file PSO.h
 * @brief Header file for class PSO
 * @date 05/10/2024
 * @author Andrea Antonione
 */

#ifndef PSO_H
#define PSO_H

#include "Particle.h"

#include <functional>

/**
 * @brief Class for PSO swarm
 */
class PSO {
public:
	/**
	 * @brief Empty constructor.
	 * @details Initializes best iterations to zero.
	 */
	PSO();

	/**
	 * @brief Constructor.
	 * @see PSO().
	 * @see initialise().
	 * @param[in] num_particles number of particles.
	 * @param[in] num_iters number of iterations.
	 * @param[in] lbs standard vector with problem lower bounds.
	 * @param[in] ubs standard vector with problem upper bounds.
	 * @param[in] output csv file name. Defaults to "output".
	 */
	PSO(int num_particles,
	 	  int num_iters,
	 	  std::vector<double> lbs,
		  std::vector<double> ubs,
		  std::string name = "output");

	/**
	 * @brief Destructor.
	 */
	~PSO();
	
	/**
	 * @brief Initialise swarm.
	 * @param[in] num_particles number of particles.
	 * @param[in] num_iters number of iterations.
	 * @param[in] lbs standard vector with problem lower bounds.
	 * @param[in] ubs standard vector with problem upper bounds.
	 * @param[in] output csv file name. Defaults to "output".
	 */
	void initialise(int num_particles,
 					        int num_iters,
                  std::vector<double> lbs,
                  std::vector<double> ubs,
                  std::string name = "output");
	
	/**
	 * @brief Optimization function.
	 * @param[in] fun function to minimizie.
	 */
	void optimize(std::function<double(std::vector<double>)>);

private:
	/**
	 * PSO swarm.
	 */
	std::vector<Particle> swarm;

	/**
	 * Problem lower bounds.
	 */
	std::vector<double> lower_bounds;

	/**
	 * Problem upper bounds.
	 */
	std::vector<double> upper_bounds;

	/**
	 * Problem dimensions.
	 */
	uint n_dimensions;

	/**
	 * Number of iterations.
	 */
	uint n_iterations;

	/**
	 * Number of particles.
	 */
	uint n_particles;

	/**
	 * PSO (global) best position.
	 */
	std::vector<double> swarm_best_position;

	/**
	 * PSO (global) best iteration.
	 */
	uint swarm_best_iter;

	/**
	 * PSO (global) best particle.
	 */
	uint swarm_best_particle;

	/**
	 * PSO (global) best fitness.
	 */
	double swarm_best_fitness;

	/**
	 * Default velocity parameters (Clerc and Kennedy constriction coefficients).
	 */
	double velocity_parameters[3] = {0.7298437881283576, 1.496179765663133, 1.496179765663133};

	/**
	 * Velocity parameters.
	 */
	double vel_par[3];

	/**
	 * Output csv file name.
	 */
	std::string outname;

	/**
	 * @brief Update particles' positions and velocities.
	 */
	void updateParticles();

	/**
	 * @brief Print progression to csv file.
	 * @param[in] iter current iteration.
	 */
	void printToCsv(uint iter);

	/**
	 * @brief Evolve velocity coefficients through iterations.
	 * @param[in] iter_index current iteration index.
	 */
	void evolveCoefficients(uint iter_index);

};

#endif /* PSO_H */
