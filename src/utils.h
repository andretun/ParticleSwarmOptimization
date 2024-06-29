#ifndef UTILS_H
#define UTILS_H

#include <random>

#define ERROR(...) \
	printf("[%s,%d] Error: ") \
	printf(__VA__ARGS__)

#define DEBUG(...) \
	printf("[%s,%d] DEBUG: ") \
	printf(__VA__ARGS__)

/**
 * @brief Generate random number inside a given range
 * param[in] lb range lower bound
 * param[in] ub range upper bound
 */
double generateRandom(double lb,
					  double ub) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> distribution(lb, ub);
    return distribution(rng);
}

#endif
