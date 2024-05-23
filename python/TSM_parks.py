import random
from copy import deepcopy

from numpy import (ndarray, copy, exp)

from park import (Park, ParkList)

def tsm_mcmc(initial_route: ParkList, max_iter: int, T: float,
             large_swap: bool=False):

    num_parks = initial_route.num_parks
    route: ParkList = deepcopy(initial_route)
    best: ParkList = deepcopy(initial_route)
    best_dist = best.total_dist

    ## metrics ##
    updated_distances = [best_dist]
    updated_updated = [0]

    best_distances = [best_dist]
    best_updated = [0]
    

    for iter in range(max_iter):

        old_dist = route.total_dist
        
        if (large_swap):
            swap_index1 = random.randint(1, num_parks-2)
            swap_index2 = swap_index1
            while (swap_index1 == swap_index2):
                swap_index2 = random.randint(1, num_parks-2)

            route.swap_two(swap_index1, swap_index2)
        
        else:
            swap_index = random.randint(1, num_parks-2)
            route.swap(swap_index)
        
        new_dist = route.total_dist
        delta_dist = new_dist - old_dist

        if not(delta_dist < 0 or (T > 0 and random.random() < exp(-delta_dist / T))):
            '''
            if prop inside not(prop) is true, then we want to 
            keep this new route. If it is false, then we want to 
            move to the next iteration of the search with the same 
            route that we started this iteration with.
            '''
            if (large_swap):
                route.swap_two(swap_index1, swap_index2, old_dist)
            else:
                route.swap(swap_index)
            
            continue

        updated_updated.append(iter+1)
        updated_distances.append(new_dist)
        
        if new_dist < best_dist:
            best_dist = new_dist
            best = deepcopy(route)
            
            ## update stats ##
            best_distances.append(new_dist)
            best_updated.append(iter+1)
    
    return best_dist, best, best_distances, best_updated, updated_distances, updated_updated