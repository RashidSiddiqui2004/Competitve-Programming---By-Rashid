#ifndef HOUSE_H
#define HOUSE_H

#include <string>

class House
{
protected:
    std::string owner;
    int numberOfBedrooms;
    int numberOfFloors;

public:
    House(const std::string &owner, int numberOfBedrooms, int numberOfFloors);
    virtual std::string get_House_Description() const;
};

#endif // HOUSE_H
