/**
 * @file PSO.cpp
 * @brief Source file for class PSO
 * @date 05/10/2024
 * @author Andrea Antonione
 */

#include "PSO.h"
#include "psoutils.h"

#include <iostream>
#include <fstream>

PSO::PSO() { swarm_best_iter = 0.; }

PSO::PSO(int num_particles, int num_iters, std::vector<double> lbs, std::vector<double> ubs, std::string name) : PSO() {
	initialise(num_particles, num_iters, lbs, ubs, name);
}

PSO::~PSO() {}

void PSO::initialise(int num_particles, int num_iters, std::vector<double> lbs, std::vector<double> ubs, std::string name) {
	// Set problem dimensions
	lower_bounds = lbs;
	upper_bounds = ubs;
	n_dimensions = std::min(lower_bounds.size(), upper_bounds.size()); // neglect possible error in dimensions
	
	// Initialise number of iterations
	n_particles  = num_particles;
	n_iterations = num_iters;
	
	// Initialise particles
	for (uint i = 0; i < n_particles; i++) {
		std::vector<double> init_pos;
		std::vector<double> init_vel;
		for (uint i = 0; i < n_dimensions; i++) {
			double x = generateRandom(lower_bounds[i], upper_bounds[i]);
			double v = generateRandom(lower_bounds[i], upper_bounds[i]) - x;
			init_pos.push_back(x);
			init_vel.push_back(v);
		}
		swarm.push_back(Particle(init_pos, init_vel));
	}

	swarm_best_fitness = std::numeric_limits<double>::infinity();

	outname = name + ".log";
  std::remove(outname.c_str()); 

	LOG("PSO initialized\n");
	LOG("Particles:%u\n", n_particles);
	LOG("Iterations:%u\n", n_iterations);
}

void PSO::optimize(std::function<double(std::vector<double>)> fun) {
	for (uint iter_index = 0; iter_index < n_iterations; iter_index++) {
		evolveCoefficients(iter_index);
		uint p_i = 0;
		for (auto& particle : swarm) {  
			std::vector<double> pos = particle.getPosition();
      double fitness = fun(pos);
      if(fitness < particle.getBestFitness()) {
        particle.setBestFitness(fitness);
        particle.setBestPosition(pos);
        if(fitness < swarm_best_fitness) {
          swarm_best_fitness = fitness;
          swarm_best_position = pos;
					swarm_best_iter = iter_index;
					swarm_best_particle = p_i;
					LOG("Fitness: %f (iteration %u, particle %u)\n",
						  swarm_best_fitness, swarm_best_iter, swarm_best_particle);
        }
      }
			p_i++;
    }
    printToCsv(iter_index);
		updateParticles();
  }
}

void PSO::updateParticles() {
	double random_numbers[2];

	for (auto& particle : swarm) {
		random_numbers[0] = generateRandom(0., 1.);
		random_numbers[1] = generateRandom(0., 1.);
		particle.updatePosition(vel_par, random_numbers, lower_bounds, upper_bounds, swarm_best_position);
	}
}

void PSO::printToCsv(uint iter) {
	std::ofstream output(outname, std::ofstream::out | std::ofstream::app);
	output << "Iteration: " << iter << std::endl;
	output << "Best fitness: " << swarm_best_fitness << std::endl;
	output << "Best position: [";
  for (uint i = 0; i < n_dimensions-1; i++) {
    output << swarm_best_position[i] << ", ";
  }
  output << swarm_best_position[n_dimensions-1] << "]\n" << std::endl;
	output.close();
}

void PSO::evolveCoefficients(uint iter_index) {
	double diff = (double) iter_index - n_iterations;
	double den = (double) n_iterations*n_iterations;
	vel_par[0] = 0.4*diff*diff/den + 0.4;
	vel_par[1] = -3*( (double) iter_index/n_iterations ) + 3.5;
	vel_par[2] = 3*( (double) iter_index/n_iterations ) + 0.5;
}
