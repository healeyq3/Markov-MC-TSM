#include "../header_files/mcmc_tsm.h"
#include <random>

optimal_solution mcmc_tsm(vector<Park> initial_route, unsigned int max_iter,
                            int temp_param, bool large_swap)
{
    ParkList curr_route(initial_route);
    ParkList best_route(initial_route);
    const unsigned int num_parks = best_route.get_num_parks();
    double best_dist = best_route.get_total_distance();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> index_distribution(1, num_parks - 2);
    std::uniform_real_distribution<double> exploration_distribution(0, 1);

    unsigned int i = 0;
    while (i < max_iter)
    {
        
        double old_dist = curr_route.get_total_distance();
        int swap_index1 = 0;
        int swap_index2 = 0;

        if (large_swap)
        {
            swap_index1 = index_distribution(gen);
            swap_index2 = swap_index1;
            while (swap_index2 == swap_index1) { swap_index2 = index_distribution(gen); }

            curr_route.inefficient_swap(swap_index1, swap_index2);
        }
        else
        {
            swap_index1 = index_distribution(gen);
            curr_route.inefficient_swap(swap_index1);
        }

        double new_dist = curr_route.get_total_distance();
        double delta_dist = new_dist - old_dist;

        bool new_route_better = delta_dist < 0;
        bool explore = temp_param > 0 && exploration_distribution(gen) < exp(-delta_dist / static_cast<double>(temp_param));

        if ( !( new_route_better || explore ) )
        {
            /**
             * If new route isn't better and we are not going to choose
             * this route in an attempt to explore the state space, revert
             * curr_route to its state before this iteration, and then move to 
             * next iteration of loop.
            */
            if (large_swap) { curr_route.inefficient_swap(swap_index1, swap_index2); }
            else { curr_route.inefficient_swap(swap_index1); }
            i++;
            continue;
        }

        if (new_dist < best_dist)
        {
            best_dist = new_dist;
            best_route = curr_route;
        }
        
        i++;
    }

    return optimal_solution {.z_star = best_dist, .x_star = best_route};
}