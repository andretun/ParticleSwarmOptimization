#ifndef UTILS_H
#define UTILS_H

#include <random>

#define ERROR(...) \
	printf("[%s,%d] Error: ", __FILE__, __LINE__); \
	printf(__VA__ARGS__);

#define DEBUG(...) \
	printf("[%s,%d] DEBUG: ", __FILE__, __LINE__); \
	printf(__VA_ARGS__);

/**
 * @brief Generate random number inside a given range
 * param[in] lb range lower bound
 * param[in] ub range upper bound
 */
double generateRandom(double lb,
					  double ub);

#endif
