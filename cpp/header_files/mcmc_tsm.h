// need pragma once?
#include "park.h"

using namespace std;

struct optimal_solution {
    double z_star;
    ParkList x_star;
};

typedef struct optimal_solution optimal_solution;

optimal_solution mcmc_tsm(vector<Park> initial_route, unsigned int max_iter,
                            int temp_param, bool large_swap=false);




