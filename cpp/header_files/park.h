#include <string>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <stdexcept>

class Park
{
    private:
        std::string _name;
        std::string _state;
        double _lat;
        double _long;

    public:
        Park();
        Park(std::string name, std::string state,
            double latitude, double longitude);
        std::string get_name() const;
        std::string get_state() const;
        double get_lat() const;
        double get_long() const;
    
};

double distance_between(Park &p1, Park &p2);

class ParkList
{
    private:
        std::vector<Park> _parks;
        unsigned int _num_parks;
        double _total_distance;

    public:
        ParkList(std::vector<Park> parks);
        std::vector<Park> get_parks() const;
        unsigned int get_num_parks() const;
        double calculate_total_distance() const;
        double get_total_distance() const;
        void inefficient_swap(unsigned int index1, int index2=-1.0);
        void swap(unsigned int index1, int index2=-1.0);
        void print_parks() const;

};