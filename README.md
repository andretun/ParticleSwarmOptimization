# Particle Swarm Optimization
---
The **Particle Swarm Optimization (PSO)** is a type of bio-inspired algorithm based on animal behaviour. It provides a simple, yet, powerful method to iteratively optimize a problem based on a function to minimize (the so-called _objective function_).
The strengths of the algorithm lay in its independence from the solution hypersurface gradient and the use of few hyperpararameters.
As the name suggests, the PSO consists of a _swarm_ made of a number of _particles_ (animals), which represent the possible solution of the objective function. The particles behave both individually and collectively at the same time, providing a combination between personal exploration of the space and convergence towards the best solution of the swarm.

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

$$\bold{x_i}(t+1) = \bold{x_i}(t) + \bold{v_i}(t+1) = \bold{x_i}(t) + \omega \cdot \bold{v_i}(t) + c_1 \cdot r_1(0,1) \cdot [\bold{P_i(t)} - \bold{x_i(t)}] + c_2 \cdot r_2(0,1) \cdot [\bold{S_i(t)} - \bold{x_i(t)}]$$

As it is shown in the equation, the velocity consists of three components, the **inertial** , **cognitive**, and **social** terms.

##### Inertial term
The inertial term, as the name suggests, represent the dependence on the velocity at the previous iteration.
It depends on the hyperparameter $\omega$.

##### Cognitive term
The cognitive term provides a component to the velocity dependent on the personal best position, therefore inuitively adding the direction the region of space in which the particle found its best objective function solution.
It depends on the hyperparameter $c_1$ and a random number between $0$ and $1$, $r_1(0,1)$, generated at each iteration.

##### Social term
The social term provides a component to the velocity dependent on the global best position, therefore inuitively adding the direction the region of space in which the swarm found its best objective function solution.
It depends on the hyperparameter $$c_2$$ and a random number between $0$ and $1$, $r_2(0,1)$, generated at each iteration.

In the simplest PSO implementation presented, there are only thre hyperparameters, as shown in the explanation of the three terms of the velocity. These parameters can be changed at will, giving more importance to whichever terms.
In this code, the hyperparameter set by [Clerc and Kennedy (2002)](https://ieeexplore.ieee.org/document/985692) is used.

