#ifndef PARTICLE_H
#define PARTICLE_H

#include <vector>

class Particle
{
public:
	// Constructor and destructor
	Particle(std::vector<double>);
	Particle();
	~Particle();

	// Swarm functions
	void updateVelocity(double [],
					    double [], 
						std::vector<double>,
						std::vector<double>,
						std::vector<double>);
	void updatePosition(double [],
					    double [], 
						std::vector<double>,
						std::vector<double>,
						std::vector<double>);
	void setBestPosition(std::vector<double>);
	void setBestFitness(double);
	std::vector<double> getPosition();
	double getBestFitness();

private:
	std::vector<double> position;
	std::vector<double> velocity;
	std::vector<double> best_position;
	double best_fitness;
};

#endif