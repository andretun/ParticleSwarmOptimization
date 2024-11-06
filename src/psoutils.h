/**
 * @file psoutils.h
 * @brief Header file for psoutils
 * @date 05/10/2024
 * @author Andrea Antonione
 */

#ifndef PSO_UTILS_H
#define PSO_UTILS_H

#define PRINT(type, ...) \
	printf("[%s:%d] %s: ", __FILE__, __LINE__, type); \
	printf(__VA_ARGS__);

#define ERROR(...) PRINT("Error", __VA_ARGS__)

#define DEBUG(...) PRINT("Debug", __VA_ARGS__)

#define LOG(...) PRINT("Log", __VA_ARGS__)

/**
 * @brief Generate random number inside a given range.
 * @param[in] lb range lower bound.
 * @param[in] ub range upper bound.
 * @return random number inside bounds.
 */
double generateRandom(double lb,
					            double ub);

#endif /* PSO_UTILS_H*/
