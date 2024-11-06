#include "PSO.h"

#define Nparticles 1000
#define Niters 100
#define ub 10
#define lb -ub

double obj_fun(std::vector<double> input) {
	double sum = 0;
	double prod = 1;
	int i = 1;
	for (auto& in : input) {
		sum += in*in;
		prod *= cos(in/sqrt(i));
		i++;
	}
	return 1 + sum/4000 - prod;
}

int main() {
	std::vector<double> lbs = {lb, lb};
	std::vector<double> ubs = {ub, ub};

	// Test with classic PSO
	PSO pso(Nparticles, Niters, lbs, ubs);
	pso.optimize(obj_fun);
	
	return 0;
}
