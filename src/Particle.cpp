#include "Particle.h"

/*
 ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████ 
██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████ 
██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
 ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

Particle::Particle(std::vector<double> pos) {
	position = pos;

	for(size_t i = 0; i < position.size(); i++)
		velocity.push_back(0.);

	best_fitness = std::numeric_limits<double>::infinity();
	}

Particle::Particle() {}

Particle::~Particle() {}

/*
███████ ██     ██  █████  ██████  ███    ███     ███████ ██    ██ ███    ██  ██████ ████████ ██  ██████  ███    ██ ███████
██      ██     ██ ██   ██ ██   ██ ████  ████     ██      ██    ██ ████   ██ ██         ██    ██ ██    ██ ████   ██ ██     
███████ ██  █  ██ ███████ ██████  ██ ████ ██     █████   ██    ██ ██ ██  ██ ██         ██    ██ ██    ██ ██ ██  ██ ███████
     ██ ██ ███ ██ ██   ██ ██   ██ ██  ██  ██     ██      ██    ██ ██  ██ ██ ██         ██    ██ ██    ██ ██  ██ ██      ██
███████  ███ ███  ██   ██ ██   ██ ██      ██     ██       ██████  ██   ████  ██████    ██    ██  ██████  ██   ████ ███████
*/

void Particle::updateVelocity(double param[],
							  double rand_nums[],
							  std::vector<double> lower_bounds,
							  std::vector<double> upper_bounds,
							  std::vector<double> swarm_best_position)
{
	for(size_t i = 0; i < velocity.size(); i++)
	{	
		// Add
		velocity[i] += param[0]*velocity[i] +
					   param[1]*rand_nums[0]*(best_position[i] - position[i]) +
					   param[2]*rand_nums[1]*(swarm_best_position[i] - position[i]);

		// Bound
		velocity[i] = std::min(velocity[i], upper_bounds[i]-lower_bounds[i]);
		velocity[i] = std::max(velocity[i], lower_bounds[i]-upper_bounds[i]);
	}
}

void Particle::updatePosition(double param[],
		                    double rand_nums[],
						std::vector<double> lower_bounds,
						std::vector<double> upper_bounds,
						std::vector<double> swarm_best_position)
{
	updateVelocity(param, rand_nums, lower_bounds, upper_bounds, swarm_best_position);

	for(size_t i = 0; i < velocity.size(); i++)
	{
		// Add
		position[i] += velocity[i];

		// Bound
		position[i] = std::min(position[i], upper_bounds[i]);
		position[i] = std::max(position[i], lower_bounds[i]);
	}
}

void Particle::setBestPosition(std::vector<double> new_best_pos) { best_position = new_best_pos; }

void Particle::setBestFitness(double new_best_fit) { best_fitness = new_best_fit; }

std::vector<double> Particle::getPosition() { return position; }

double Particle::getBestFitness() { return best_fitness; }
