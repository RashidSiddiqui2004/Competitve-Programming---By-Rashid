class House:

    numberOfHouses = 0

    def __init__(self, owner: str, numberOfBedrooms: int, numberOfFloors: int):
        House.numberOfHouses += 1
        self.__owner = owner
        self.numberOfBedrooms = numberOfBedrooms
        self.numberOfFloors = numberOfFloors
    
    def get_House_Description(self):
        return self.__owner + " " +  str(self.numberOfBedrooms) + "$" + str(self.numberOfFloors)
    
    @property
    def owner(self):
        return self.__owner
    
    @staticmethod
    def getNumberOfHouses():
        return House.numberOfHouses

sinhaHouse = House("Sinha", 4, 2)

print(sinhaHouse.get_House_Description())

# getting read-only attribute
 
# print(sinhaHouse.__owner) # private attribute -> not accessible outside the class 

sinhaHouse.__owner = "Rashid" # this doesn't overwrite the read-only attribute
print(sinhaHouse.owner) # Sinha
 
print(House.getNumberOfHouses())

rashidHouse = House("Siddiqui", 12, 6)

print(House.getNumberOfHouses())

# we get the same result here as well
print(rashidHouse.getNumberOfHouses())