#include "House.h"

House::House(const std::string &owner, int numberOfBedrooms, int numberOfFloors)
    : owner(owner), numberOfBedrooms(numberOfBedrooms), numberOfFloors(numberOfFloors) {}

std::string House::get_House_Description() const
{
    return owner + " " + std::to_string(numberOfBedrooms) + "$" + std::to_string(numberOfFloors);
}
