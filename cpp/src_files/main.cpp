#include <fstream>
#include <sstream>

#include "../header_files/mcmc_tsm.h"

Park parse_csv_line(const std::string& line)
{
    std::string name;
    std::string state;
    double latit = 0;
    double longit = 0;
    std::stringstream ss(line);
    std::string token;

    std::getline(ss, name, ',');
    std::getline(ss, state, ',');
    std::getline(ss, token, ',');
    latit = std::stod(token);
    std::getline(ss, token, ',');
    longit = std::stod(token);

    Park park(name, state, latit, longit);
    return park;
}

int main()
{

    // ======== DATA PARSING ========

    std::string filename = "../data/parks.csv";
    std::ifstream file(filename);

    if (!file.is_open()) 
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return 1;
    }

    std::string line;
    std::vector<Park> init_route;
    Park final_park;

    try
    {
        if (std::getline(file, line)) {
            std::cout << "Skipped header: " << line << std::endl;
        }

        while (std::getline(file, line))
        {
            Park park = parse_csv_line(line);
            if (park.get_name() == "Pinnacles")
            {
                init_route.insert(init_route.begin(), park); 
                final_park = park;
            }
            else { init_route.push_back(park); }

        }

        init_route.push_back(final_park);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        file.close();
    }
    

    file.close();

    ParkList plist(init_route);
    
    std::cout << "Distance of Initial Route: " << plist.get_total_distance() << std::endl;

    std::cout << "Initial Route:" <<std::endl;
    
    plist.print_parks();

    // ===== BEGIN EXPERIMENTS =====

    // -------- Consecutive Swaps --------

    vector<int> temp_list = { 0, 1, 10, 100 };

    vector<optimal_solution> consecutive_solutions;

    for (int temp : temp_list)
    {
        optimal_solution solution = {.z_star=INFINITY, .x_star=plist};

        for (unsigned int i = 0; i < 10; i++)
        {
            optimal_solution possible_solution = mcmc_tsm(init_route, 10000, temp, false);
            if (possible_solution.z_star < solution.z_star) { solution = possible_solution; }
        }

        consecutive_solutions.push_back(solution);
    }

    std::cout << "CONSECUTIVE SWAP EXPERIMENT" << std::endl;

    for (unsigned int i = 0; i < temp_list.size(); i++)
    {
        std::cout << "Solution Distance for temp_parm = " << temp_list[i] << " is: " << consecutive_solutions[i].z_star <<std::endl;
    }

    // -------- Large Swaps --------


    vector<optimal_solution> large_swap_solutions;

    for (int temp : temp_list)
    {
        optimal_solution solution = {.z_star=INFINITY, .x_star=plist};

        for (unsigned int i = 0; i < 10; i++)
        {
            optimal_solution possible_solution = mcmc_tsm(init_route, 10000, temp, true);
            if (possible_solution.z_star < solution.z_star) { solution = possible_solution; }
        }

        large_swap_solutions.push_back(solution);
    }

    std::cout << "LARGE SWAP EXPERIMENT" << std::endl;

    for (unsigned int i = 0; i < temp_list.size(); i++)
    {
        std::cout << "Solution Distance for temp_parm = " << temp_list[i] << " is: " << large_swap_solutions[i].z_star <<std::endl;
    }


    return 0;
}