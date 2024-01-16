#include "../include/Swarm.h"

/*
 ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████ 
██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████ 
██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
 ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

Swarm::Swarm(int num_particles,
			 int num_iters,
			 std::vector<double> lbs,
			 std::vector<double> ubs)
{
	// set problem dimensions
	lower_bounds = lbs;
	upper_bounds = ubs;
	n_dimensions = std::min(lower_bounds.size(), upper_bounds.size()); // neglect possible error in dimensions
	
	// Initialise number of iterations
	n_iterations = num_iters;
	n_particles  = num_particles;
	
	// Initialise particles
	initialiseSwarm();

	swarm_best_fitness = std::numeric_limits<double>::infinity(); 
}

Swarm::Swarm() {}

Swarm::~Swarm() {}

/*
 ██████  ██████  ████████ ██ ███    ███ ██ ███████  █████  ████████ ██  ██████  ███    ██
██    ██ ██   ██    ██    ██ ████  ████ ██    ███  ██   ██    ██    ██ ██    ██ ████   ██
██    ██ ██████     ██    ██ ██ ████ ██ ██   ███   ███████    ██    ██ ██    ██ ██ ██  ██
██    ██ ██         ██    ██ ██  ██  ██ ██  ███    ██   ██    ██    ██ ██    ██ ██  ██ ██
 ██████  ██         ██    ██ ██      ██ ██ ███████ ██   ██    ██    ██  ██████  ██   ████
*/

void Swarm::optimize(std::function<double(std::vector<double>)> fun)
{
	for(int iter_index = 0; iter_index < n_iterations; iter_index++)
	{
		for(auto& particle : particles) {
			// Evaluate fitness
			std::vector<double> pos = particle.getPosition();
	        double fitness = fun(pos);
		    std::cout << "Particle fitness: " << fitness << std::endl;
		    std::cout << "Particle position: {";
	        for(auto& p : pos)
		    	std::cout << p << ", ";
		    std::cout << "}" << std::endl;

	        // Update best positions if necessary
	        if(fitness < particle.getBestFitness())
	        {
			    std::cout << "Changing fitness" << std::endl;
	        	particle.setBestFitness(fitness);
	        	particle.setBestPosition(pos);

	        	if(fitness < swarm_best_fitness)
	        	{
	        		swarm_best_fitness = fitness;
	        		swarm_best_position = pos;
	        	}
	        }
	    }
	    std::cout << "Swarm best position: " << swarm_best_fitness << std::endl;
	    std::cout << "Best position: {";
	    for(auto& swarm_pos : swarm_best_position)
	    	std::cout << swarm_pos << ", ";
	    std::cout<< "}" << std::endl;

        // Update position for next iteration
        updateParticles();
    }
}


/*
██████  ██████  ██ ██    ██  █████  ████████ ███████
██   ██ ██   ██ ██ ██    ██ ██   ██    ██    ██     
██████  ██████  ██ ██    ██ ███████    ██    █████  
██      ██   ██ ██  ██  ██  ██   ██    ██    ██     
██      ██   ██ ██   ████   ██   ██    ██    ███████
*/

void Swarm::initialiseSwarm()
{
	for(size_t i = 0; i < n_particles; i++)
	{
		std::vector<double> init_pos;
		for(size_t i = 0; i < n_dimensions; i++)
			init_pos.push_back(generateRandom(lower_bounds[i], upper_bounds[i]));
		particles.push_back(Particle(init_pos));
	}
}

void Swarm::updateParticles()
{
	double random_numbers[2];

	for(auto& particle : particles)
	{
		random_numbers[0] = generateRandom(0., 1.);
		random_numbers[1] = generateRandom(0., 1.);
		particle.updatePosition(velocity_parameters,
								random_numbers,
								lower_bounds,
								upper_bounds,
								swarm_best_position);
	}
}

double Swarm::generateRandom(double lb, double ub)
{
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> distribution(lb, ub);
    
    return distribution(rng);
}

