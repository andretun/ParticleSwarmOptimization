/**
 * @file psoutils.cpp
 * @brief Source file for utils
 * @date 05/10/2024
 * @author Andrea Antonione
 */

#include "psoutils.h"
#include <random>

double generateRandom(double lb, double ub) {
  std::mt19937 rng(std::random_device{}());
  std::uniform_real_distribution<double> distribution(lb, ub);
  return distribution(rng);
}
