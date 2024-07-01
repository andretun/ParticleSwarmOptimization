#include "utils.h"

double generateRandom(double lb,
					  double ub) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> distribution(lb, ub);
    return distribution(rng);
}
