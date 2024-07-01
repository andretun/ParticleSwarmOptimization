#include "Swarm.h"

Swarm::Swarm(int num_particles,
			 int num_iters,
			 std::vector<double> lbs,
			 std::vector<double> ubs,
			 bool glob) {
	initialise(num_particles, num_iters, lbs, ubs, global);
}

Swarm::Swarm() {}

Swarm::~Swarm() {}

void Swarm::initialise(int num_particles,
			           int num_iters,
			           std::vector<double> lbs,
			           std::vector<double> ubs,
			           bool glob) {
	// Set problem dimensions
	lower_bounds = lbs;
	upper_bounds = ubs;
	n_dimensions = std::min(lower_bounds.size(), upper_bounds.size()); // neglect possible error in dimensions
	global = glob;
	
	// Initialise number of iterations
	n_iterations = num_iters;
	n_particles  = num_particles;
	
	// Initialise particles
	initialiseSwarm();

	swarm_best_fitness = std::numeric_limits<double>::infinity();
}

void Swarm::optimize(std::function<double(std::vector<double>)> fun) {
	for (uint iter_index = 0; iter_index < n_iterations; iter_index++) {
		for (auto& particle : particles) {
			// Evaluate fitness
			std::vector<double> pos = particle.getPosition();
	        double fitness = fun(pos);

	        // Update best positions if necessary
	        if(fitness < particle.getBestFitness()) {
	        	particle.setBestFitness(fitness);
	        	particle.setBestPosition(pos);

	        	if(fitness < swarm_best_fitness) {
	        		swarm_best_fitness = fitness;
	        		swarm_best_position = pos;
	        	}
	        }
	    }

        // Update position for next iteration
        if (global) {
	        updateParticlesGlobal();
        } else {
        	updateParticlesCloseFirsts();
        }
    }
    printResults();
}

void Swarm::initialiseSwarm() {
	for (uint i = 0; i < n_particles; i++) {
		std::vector<double> init_pos;
		std::vector<double> init_vel;
		for (uint i = 0; i < n_dimensions; i++) {
			double x = generateRandom(lower_bounds[i], upper_bounds[i]);
			double v = generateRandom(lower_bounds[i], upper_bounds[i]) - x;
			init_pos.push_back(x);
			init_vel.push_back(v);
		}
		particles.push_back(Particle(init_pos, init_vel));
	}
}

void Swarm::updateParticlesGlobal() {
	double random_numbers[2];

	for (auto& particle : particles) {
		random_numbers[0] = generateRandom(0., 1.);
		random_numbers[1] = generateRandom(0., 1.);
		particle.updatePosition(velocity_parameters,
								random_numbers,
								lower_bounds,
								upper_bounds,
								swarm_best_position);
	}
}

void Swarm::updateParticlesCloseFirsts() {
	double random_numbers[2];
	double distances[n_particles][n_particles];

	for (uint i = 0; i < n_particles; i++) {
		distances[i][i] = 0;
		std::vector<double> pos_i = particles[i].getPosition();
		for (uint j = i+1; j < n_particles; j++) {
			std::vector<double> pos_j = particles[j].getPosition();
			double d = 0;
			for (uint k = 0; k < pos_i.size(); k++) {
				d += (pos_i[k] - pos_j[k])*(pos_i[k] - pos_j[k]);
			}
			distances[i][j] = d;
			distances[j][i] = d;
		}
	}

	for (uint i = 0; i < n_particles; i++) {
		random_numbers[0] = generateRandom(0., 1.);
		random_numbers[1] = generateRandom(0., 1.);
		double best_dist = std::numeric_limits<double>::infinity();
		uint best_index = 0;
		for (uint j = 0; j < n_particles; j++) {
			if (j != i && distances[i][j] < best_dist) {
				best_dist = distances[i][j];
				best_index = j;
			}
		}
		particles[i].updatePosition(velocity_parameters,
								random_numbers,
								lower_bounds,
								upper_bounds,
								particles[best_index].getBestPosition());
	}
}

void Swarm::printResults() {
    printf("Result\n");
    printf("Fitness: %f\n", swarm_best_fitness);
    printf("Position: ");
    for (uint i = 0; i < n_dimensions-1; i++) {
    	printf("%f, ", swarm_best_position[i]);
    }
	printf("%f\n", swarm_best_position[n_dimensions-1]);
}
