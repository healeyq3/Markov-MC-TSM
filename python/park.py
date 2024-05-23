from math import sqrt
from dataclasses import dataclass

from numpy import (array, ndarray)


@dataclass
class Park:
    """
    Class for keeping track of a park and its attributes
    """
    name: str
    state: str
    lat: float
    long: float

def distance_between(p1: Park, p2: Park):
    """
    Calculate the distance between the two provided parks.
    
    Parameters
    ----------
    p1: Park
    p2: Park

    Returns
    -------
    The distance between the two parks as measured in the Euclidean sense using
    the park's latitude and longitude.
    """
    lat_diff: float = p1.lat - p2.lat
    long_diff: float = p1.long - p2.long
    dist_sqrd: float = lat_diff**2 + long_diff**2
    return sqrt(dist_sqrd)

class ParkList:

    def __init__(self, parks):
        self.parks: ndarray[Park] = array(parks)
        self.num_parks: int = len(parks)
        self.total_dist: float = self.calculate_total_distance()

    def swap_two(self, index1: int, index2: int, orig_dist: float=None) -> None:
        if (index1 < 0 or index1 >= self.num_parks):
            raise IndexError("Index out of range for accessing parks.")
        if (index2 < 0 or index2 >= self.num_parks):
            raise IndexError("Index out of range for accessing parks.")
        if (index1 == 0 or index1 == self.num_parks - 1):
            raise IndexError("Technically these are valid indices for accessing park elements, but\
                              they are invalid for swapping in the TSM search algorithm.")
        if (index2 == 0 or index2 == self.num_parks - 1):
            raise IndexError("Technically these are valid indices for accessing park elements, but\
                              they are invalid for swapping in the TSM search algorithm.")
        
        self.parks[index1], self.parks[index2] = self.parks[index2], self.parks[index1]
        if (orig_dist == None):
            self.total_dist = self.calculate_total_distance()
        else:
            self.total_dist = orig_dist
    
    def swap(self, index: int) -> None:
        """
        Swap method specifically created for aiding in the TSM problem.
        Note that because of TSM design, the first and last parks cannot be
        swapped.

        self.num_parks - 1 is last element (CANNOT BE SWAPPED)

        self.num_parks - 2 is the second to last element. It can be swapped, just not with the park after it.
        """
        if (index < 0 or index >= self.num_parks):
            raise IndexError("Index out of range for accessing parks.")
        if (index == 0 or index == self.num_parks - 1):
            raise IndexError("Technically these are valid indices for accessing park elements, but\
                              they are invalid for swapping in the TSM search algorithm.")
        
        prev_dist_1: float = 0
        prev_dist_2: float = 0
        new_dist_1: float = 0
        new_dist_2: float = 0

        if (index < self.num_parks - 2):
            
            prev_dist_1 = distance_between(self.parks[index], self.parks[index-1])
            prev_dist_2 = distance_between(self.parks[index+1], self.parks[index+2])
            
            self.parks[index], self.parks[index+1] = self.parks[index+1], self.parks[index]
            
            new_dist_1 = distance_between(self.parks[index], self.parks[index-1])
            new_dist_2 = distance_between(self.parks[index+1], self.parks[index+2])
        
        elif (index == self.num_parks - 2):
            
            prev_dist_1 = distance_between(self.parks[index], self.parks[index+1])
            prev_dist_2 = distance_between(self.parks[index-1], self.parks[index-2])

            self.parks[index], self.parks[index-1] = self.parks[index-1], self.parks[index]

            new_dist_1 = distance_between(self.parks[index], self.parks[index+1])
            new_dist_2 = distance_between(self.parks[index-1], self.parks[index-2])

        else:
            raise ValueError("Unexpected condition occured when swapping parks")
        

        self.total_dist -= prev_dist_1
        self.total_dist -= prev_dist_2
        self.total_dist += new_dist_1
        self.total_dist += new_dist_2

    def calculate_total_distance(self) -> float:
        total_distance = 0

        for park_index in range(self.num_parks - 1):
            total_distance += distance_between(self.parks[park_index], self.parks[park_index+1])
        
        return total_distance


    
    