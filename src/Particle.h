/**
 * @file Particle.h
 * @brief Header file for class Particle
 * @date 05/10/2024
 * @author Andrea Antonione
 */

#ifndef PARTICLE_H
#define PARTICLE_H

#include "utils.h"

#include <vector>
#include <limits>

/**
 * @brief Class for PSO particle
 */
class Particle {
public:
	/**
	 * @brief Constructor
	 * @details Initializes velocity to zero and best fitness to infinity
	 */
	Particle();
	
	/**
	 * @brief Constructor
	 * @see Particle()
	 * @details Parameters initialized as inputs
	 * @param[in] pos initial position
	 * @param[in] vel initial initial velocity
	 */
	Particle(std::vector<double> pos,
			 std::vector<double> vel);

	/**
	 * @brief Destructor. NOOP.
	 */
	~Particle();

	/**
	 * @brief Update particle velocity
	 * @param[in] params 3-elements array with velocity update coefficients
	 * @param[in] rand_nums 2-elements array with velocity update random numbers
	 * @param[in] lower_bounds standard vector with problem lower bounds
	 * @param[in] upper_bounds standard vector with problem upper bounds
	 * @param[in] swarm_best_position standard vector with swarm best position
	 */
	void updateVelocity(double param[],
					    double rand_nums[], 
						std::vector<double> lower_bounds,
						std::vector<double> upper_bounds,
						std::vector<double> swarm_best_position);

	/**
	 * @brief Update particle position
	 * @param[in] params 3-elements array with velocity update coefficients
	 * @param[in] rand_nums 2-elements array with velocity update random numbers
	 * @param[in] lower_bounds standard vector with problem lower bounds
	 * @param[in] upper_bounds standard vector with problem upper bounds
	 * @param[in] swarm_best_position standard vector with swarm best position
	 */
	void updatePosition(double param[],
					    double rand_nums[], 
						std::vector<double> lower_bounds,
						std::vector<double> upper_bounds,
						std::vector<double> swarm_best_position);

	/**
	 * @brief Set particle new best position
	 * @param[in] new_best_pos new best position
	 */
	void setBestPosition(std::vector<double> new_best_pos);

	/**
	 * @brief Set particle new best fitness
	 * @param[in] new_best_fit new best fitness
	 */
	void setBestFitness(double new_best_fit);

	/**
	 * @brief Get particle position
	 * @return position
	 */
	std::vector<double> getPosition() const;
	
	/**
	 * @brief Get particle best position
	 * @return best_position
	 */
	std::vector<double> getBestPosition() const;

	/**
	 * @brief Get particle best fitness
	 * @return best_fitness
	 */
	double getBestFitness() const;

private:
	/**
	 * Particle position
	 */
	std::vector<double> position;

	/**
	 * Particle velocity
	 */
	std::vector<double> velocity;

	/**
	 * Particle best position
	 */
	std::vector<double> best_position;

	/**
	 * Particle best fitness
	 */
	double best_fitness;

	/**
	 * @brief Bounce against boundsries
	 * @param[in] i position index
	 * @param[in] lb i-th dimension lower bound
	 * @param[in] ub i-th dimension upper bound
	 */
	void bounce(uint i,
				double lb,
				double ub);
};

#endif
