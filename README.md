# Particle Swarm Optimization
---

## Scope
---
Simple implementation of a **Particle Swarm Optimization (PSO)** algorithm for minimization problems.

## Overview
---
The PSO is a type of algorithm based on animal behaviour. It provides a simple and powerful method to iteratively optimize a problem based on a function to minimize (the so-called *objective function*).
The strengths of the algorithm lay in its independence from the solution hypersurface gradient and the use of few hyperpararameters.
As the name suggests, the PSO consists of a *swarm* made of a number of *particles* (animals), which represent the possible solution of the objective function. The particles behave both individually and collectively at the same time, providing a combination between personal exploration of the space and convergence towards the best solution of the swarm.

## Working principle
---
The underlayng principle of the optimization is in the particle position its evolution.
Each position provides a solution for the objective function. The latter needs to be minimized and therefore represent an indicator of the goodnes of the solution.
At every iteration, the objective function is evaluated for each particle position and two terms are continuosly updated, the **particle (personal) best position**, and the **swarm (global) best position**.
At the end of the iteration, each particle position is updated through a velocity term.


## The code
---
A simple C++ implementation of the basic PSO is provided here. The code is based on two main classes, **Particle** and **Swarm**.
At the initialization, a user-defined number of particles are initialised with random positions (uniformely distributed in the solutions space). After the first iteration, each personal best position and the global best position are set, therefore allowing to build the particle velocities needed to move through the space.
The position is updated as follows, where _i_ is the index of the particle:

$`
{x_i}(t+1) = x_i(t) + v_i(t+1) = x_i(t) + \omega v_i(t) + c_1 r^1_{(0,1)} (P_i(t) - x_i(t)) + c_2 r^2_{(0,1)} (S_i(t) - x_i(t))
`$

As it is shown in the equation, the velocity consists of three components, the **inertial** , **cognitive**, and **social** terms.

#### Inertial term
The inertial term, as the name suggests, represent the dependence on the velocity at the previous iteration.
It depends on the hyperparameter $\omega$.

#### Cognitive term
The cognitive term provides a component to the velocity dependent on the personal best position, therefore inuitively adding the direction the region of space in which the particle found its best objective function solution.
It depends on the hyperparameter $c_1$ and a random number between $0$ and $1$, $r_1(0,1)$, generated at each iteration.

#### Social term
The social term provides a component to the velocity dependent on the global best position, therefore inuitively adding the direction the region of space in which the swarm found its best objective function solution.
It depends on the hyperparameter $c_2$ and a random number between $0$ and $1$, $r_2(0,1)$, generated at each iteration.

In the simplest PSO implementation presented, there are only thre hyperparameters, as shown in the explanation of the three terms of the velocity. These parameters can be changed at will, giving more importance to whichever terms.
In this code, an evolution of the three hyperparameters along witht the iteration number is implemented.

## Use
---
The usage of the PSO is very simple (see the *example.cpp* in this page):

1. define an objective funtion that returns a double.
2. define the number of particles and iterations for the algorithm.
3. define the bounds of the problem (the space dimension will be extracted from the bound).
4. initialize a *PSO* with the chosen features (optional output file name)
5. run the optimization

The output file name *.log* is updated at every iteration with the best position and fitness.
