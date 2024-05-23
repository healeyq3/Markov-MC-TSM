# About

This repository contains a Python implementation and a C++ implementation of [Stanford CS 168's](https://web.stanford.edu/class/cs168/) Mini-project #7 Question 2. Specifically, each "codebase" uses a Markov Chain Monte Carlo (MCMC) approach to find a desirable tour of a [travelling salesman problem](https://en.wikipedia.org/wiki/Travelling_salesman_problem) (TSM), where the "cities" the "salesman" must traverse between are the 51 US national parks. 

# Codebases

Each codebase uses an object oriented programming approach to simplify the implementation of the actual MCMC algorithm. Having run the experiments detailed in the mini-project problem description, both my Python and my C++ version of the solution work. The driver file for the C++ implementation is main.cpp and the driver file for the Python implementation is main.ipynb. For viewing purposes, I recommend the jupyter notebook as there are plots of the best found route and current route versus iteration number as the MCMC algorithm progresses. In the python folder there are also plotly geo plots which depict a random TSM tour and a good TSM tour. However, it is currently easier to compare the distances travelled by the best tours using the experimentation performed in C++.

**NOTE** (if you want to run yourself). Makefile coming to C++ version soon. For now, navigate to src_files folder and type the following commands (on a mac system with clang, yada yada)

```bash
clang++ -std=c++14 main.cpp park.cpp mcmc_tsm.cpp  -o out
./out
```