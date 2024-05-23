#include "../header_files/park.h"

// -------------- PARK CODE --------------

Park::Park() : _name(), _state(), _lat(), _long()
{ }

Park::Park(std::string name, std::string state,
        double latitude, double longitude)
    : _name(name), _state(state), _lat(latitude), _long(longitude)
{ }

std::string Park::get_name() const { return _name; }
std::string Park::get_state() const { return _state; }
double Park::get_lat() const { return _lat;}
double Park::get_long() const { return _long; }


double distance_between(const Park &p1, const Park &p2)
{
    double lat_diff = p1.get_lat() - p2.get_lat();
    double long_diff = p1.get_long() - p2.get_long();
    double dist_sqrt = pow(lat_diff, 2) + pow(long_diff, 2);
    return sqrt(dist_sqrt);
}

// -------------- PARKLIST CODE --------------

ParkList::ParkList(std::vector<Park> parks)
{
    /*
    Note that I hardcopy (don't use reference) the parks 
    begin passed in since this is a one time operation
    and I want the original path (the one being passed to the ParkList)
    to not be forgotten.
    */
    _parks = parks;
    _num_parks = parks.size();
    _total_distance = calculate_total_distance();
}

std::vector<Park> ParkList::get_parks() const { return _parks; }
unsigned int ParkList::get_num_parks() const { return _num_parks; }

double ParkList::calculate_total_distance() const
{
    return std::accumulate(_parks.begin(), _parks.end() - 1, 0.0,
                [this](double total_dist, const Park& park){
                    auto next_park = &park + 1;
                    return total_dist + distance_between(park, *next_park);
                }
            );
}

double ParkList::get_total_distance() const { return _total_distance; }

void ParkList::inefficient_swap(unsigned int index1, int index2)
{
    // =========== VALIDITY CHECKS ===========
    
    if (index1 >= _num_parks) { throw std::invalid_argument{
                                "index 1 = " + std::to_string(index1) + " is out of range for accessing parks." }; }
    
    if (index1 == 0 || index1== _num_parks - 1)
    {
        throw std::invalid_argument{"Technically index 1 = " + std::to_string(index1) +  " is a valid index for accessing park elements, but\
                              it is invalid for swapping in the TSM search algorithm."};
    }

    if (abs(index2) >= _num_parks) { throw std::invalid_argument{
                                "index 2 = " + std::to_string(index2) + " is out of range for accessing parks." }; }
    
    if (index2 == 0 || index2== _num_parks - 1)
    {
        throw std::invalid_argument{"Technically index 2 = " + std::to_string(index2) +  " is a valid index for accessing park elements, but\
                              it is invalid for swapping in the TSM search algorithm."};
    }

    bool two_before = false;
    bool two_after = true;
    
    if (index2 < 0 && index1 == _num_parks-2)
    {
        /*
        Consecutive swap edge case where
        swapping index1 and index+1 would result in the TSM 
        not ending in the same park he started in.
        */
        index2 = index1 - 1;
        two_before = true;
    }
    else if (index2 < 0)
    {
        /*
        Remaining consecutive cases
        */
        index2 = index1 + 1;
        two_after = true;
    }

    std::swap(_parks[index1], _parks[index2]);

    _total_distance = ParkList::calculate_total_distance();
}

void ParkList::swap(unsigned int index1, int index2)
{
    /**
     * This swap method currently has an error which is causing
     * the large swap case to end up with a negative value. I need to check
     * the code associated with two_before==false and two_after==false
     * 
    */
    // =========== VALIDITY CHECKS ===========
    
    if (index1 >= _num_parks) { throw std::invalid_argument{
                                "index 1 = " + std::to_string(index1) + " is out of range for accessing parks." }; }
    
    if (index1 == 0 || index1== _num_parks - 1)
    {
        throw std::invalid_argument{"Technically index 1 = " + std::to_string(index1) +  " is a valid index for accessing park elements, but\
                              it is invalid for swapping in the TSM search algorithm."};
    }

    if (abs(index2) >= _num_parks) { throw std::invalid_argument{
                                "index 2 = " + std::to_string(index2) + " is out of range for accessing parks." }; }
    
    if (index2 == 0 || index2== _num_parks - 1)
    {
        throw std::invalid_argument{"Technically index 2 = " + std::to_string(index2) +  " is a valid index for accessing park elements, but\
                              it is invalid for swapping in the TSM search algorithm."};
    }

    // =========== MAIN FUNCTIONALITY ===========
    // (should be faster performing than Python counterpart, but can also use some tidying up)

    bool two_before = false;
    bool two_after = true;
    
    if (index2 < 0 && index1 == _num_parks-2)
    {
        /*
        Consecutive swap edge case where
        swapping index1 and index+1 would result in the TSM 
        not ending in the same park he started in.
        */
        index2 = index1 - 1;
        two_before = true;
    }
    else if (index2 < 0)
    {
        /*
        Remaining consecutive cases
        */
        index2 = index1 + 1;
        two_after = true;
    }
    else
    {
        if (index2 == index1 - 1) { two_before = true; }
        else if (index2 == index1 + 1) { two_after = true; }
    }

    double prev_dist1_1 = 0.0;
    double prev_dist1_2 = 0.0;
    double prev_dist2_1 = 0.0;
    double prev_dist2_2 = 0.0;

    double new_dist1_1 = 0.0;
    double new_dist1_2 = 0.0;
    double new_dist2_1 = 0.0;
    double new_dist2_2 = 0.0;

    if (!two_before && ! two_after)
    {
        prev_dist1_1 = distance_between(static_cast<Park>(_parks[index1]), static_cast<Park>(_parks[index1-1]));
        prev_dist1_2 = distance_between(static_cast<Park>(_parks[index1]), static_cast<Park>(_parks[index1+1]));
        prev_dist2_1 = distance_between(static_cast<Park>(_parks[index2]), static_cast<Park>(_parks[index2-1]));
        prev_dist2_2 = distance_between(static_cast<Park>(_parks[index2]), static_cast<Park>(_parks[index2+1]));
    }
    else if (two_before)
    {
        prev_dist1_2 = distance_between(static_cast<Park>(_parks[index1]), static_cast<Park>(_parks[index1+1]));
        prev_dist2_1 = distance_between(static_cast<Park>(_parks[index2]), static_cast<Park>(_parks[index2-1]));
    }
    else if (two_after)
    {
        prev_dist1_1 = distance_between(static_cast<Park>(_parks[index1]), static_cast<Park>(_parks[index1-1]));
        prev_dist2_2 = distance_between(static_cast<Park>(_parks[index2]), static_cast<Park>(_parks[index2+1]));
    }

    std::swap(_parks[index1], _parks[index2]);

    if (!two_before && ! two_after)
    {
        new_dist1_1 = distance_between(static_cast<Park>(_parks[index1]), static_cast<Park>(_parks[index1-1]));
        new_dist1_2 = distance_between(static_cast<Park>(_parks[index1]), static_cast<Park>(_parks[index1+1]));
        new_dist2_1 = distance_between(static_cast<Park>(_parks[index2]), static_cast<Park>(_parks[index2-1]));
        new_dist2_2 = distance_between(static_cast<Park>(_parks[index2]), static_cast<Park>(_parks[index2+1]));
    }
    else if (two_before)
    {
        new_dist1_2 = distance_between(static_cast<Park>(_parks[index1]), static_cast<Park>(_parks[index1+1]));
        new_dist2_1 = distance_between(static_cast<Park>(_parks[index2]), static_cast<Park>(_parks[index2-1]));
    }
    else if (two_after)
    {
        new_dist1_1 = distance_between(static_cast<Park>(_parks[index1]), static_cast<Park>(_parks[index1-1]));
        new_dist2_2 = distance_between(static_cast<Park>(_parks[index2]), static_cast<Park>(_parks[index2+1]));
    }

    _total_distance -= (prev_dist1_1+prev_dist1_2+prev_dist2_1+prev_dist2_2);
    _total_distance += (new_dist1_1+new_dist1_2+new_dist2_1+new_dist2_2);
    
}

void ParkList::print_parks() const
{
    for (const Park &park : _parks)
    {
        std::cout << park.get_name() << ", ";
    }
    std::cout<<std::endl;
}
