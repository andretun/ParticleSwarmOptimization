#ifndef SWARM_H
#define SWARM_H

#include "Particle.h"

#include <vector>
#include <random>
#include <functional>
#include <limits>
#include <iostream>

class Swarm
{
public:
	// Constructor and destructor
	Swarm(int,
		  int,
		  std::vector<double>,
		  std::vector<double>);
	Swarm();
	~Swarm();

	// Optimization functions
	void optimize(std::function<double(std::vector<double>)>);

private:
	std::vector<Particle> particles;
	std::vector<double> lower_bounds;
	std::vector<double> upper_bounds;
	int n_dimensions;
	int n_iterations;
	int n_particles;
	std::vector<double> swarm_best_position;
	double swarm_best_fitness;
	double velocity_parameters[3] = {0.7298437881283576, 1.496179765663133, 1.496179765663133}; // Clerc and Kennedy constriction coefficients
	double random_numbers[2];

	// private functions
	void initialiseSwarm();
	void updateParticles();
	double generateRandom(double, double);
};

#endif