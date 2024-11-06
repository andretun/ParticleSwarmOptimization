/**
 * @file Particle.cpp
 * @brief Source file for class Particle
 * @date 05/10/2024
 * @author Andrea Antonione
 */

#include "Particle.h"
#include "psoutils.h"
#include <limits>

Particle::Particle() { best_fitness = std::numeric_limits<double>::infinity(); }

Particle::Particle(std::vector<double> pos, std::vector<double> vel) : Particle() {
	position = pos;
	best_position = pos;
	velocity = vel;
}

Particle::~Particle() {}

void Particle::updateVelocity(double param[], double rand_nums[], std::vector<double> lower_bounds, std::vector<double> upper_bounds, std::vector<double> swarm_best_position) {
	for (uint i=0u; i<velocity.size(); i++) {
		velocity[i] += param[0]*velocity[i] +
                   param[1]*rand_nums[0]*(best_position[i] - position[i]) +
                   param[2]*rand_nums[1]*(swarm_best_position[i] - position[i]);
		velocity[i] = std::min(velocity[i], upper_bounds[i]-lower_bounds[i]);
		velocity[i] = std::max(velocity[i], lower_bounds[i]-upper_bounds[i]);
	}
}

void Particle::updatePosition(double param[], double rand_nums[], std::vector<double> lower_bounds, std::vector<double> upper_bounds, std::vector<double> swarm_best_position) {
	updateVelocity(param, rand_nums, lower_bounds, upper_bounds, swarm_best_position);
	for (uint i=0u; i<velocity.size(); i++) {
		bounce(i, lower_bounds[i], upper_bounds[i]);
	}
}

void Particle::bounce(uint i, double lb, double ub) {
	if (position[i] + velocity[i] > ub) {
		position[i] = generateRandom(position[i], ub);
		velocity[i] = position[i] - ub;
	} else if (position[i] + velocity[i] < lb) {
		position[i] = generateRandom(lb, position[i]);
		velocity[i] = position[i] - lb;
	} else {
		position[i] += velocity[i];
	}
}

void Particle::setBestPosition(std::vector<double> new_best_pos) { best_position = new_best_pos; }

void Particle::setBestFitness(double new_best_fit) { best_fitness = new_best_fit; }

std::vector<double> Particle::getPosition() const { return position; }

std::vector<double> Particle::getBestPosition() const { return best_position; }

double Particle::getBestFitness() const { return best_fitness; }
