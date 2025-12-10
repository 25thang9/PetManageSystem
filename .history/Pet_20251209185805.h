// Pet.h 
#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Pet {
private:
    std::string species;   // Loài: Dog, Cat, Cow, Fish, Dragon...
    std::string name;
    int         age;
    std::string color;
    std::string breed;
    std::string owner;

public:
    // Constructor
    Pet(std::string s = "", std::string n = "", int a = 0,
        std::string c = "", std::string b = "", std::string o = "");

    // Getter
    std::string getSpecies() const { return species; }
    std::string getName()    const { return name; }
    int         getAge()     const { return age; }
    std::string getColor()   const { return color; }
    std::string getBreed()   const { return breed; }
    std::string getOwner()   const { return owner; }

    // Setter
    void setSpecies(std::string s) { species = s; }
    void setName(std::string n)    { name = n; }
    void setAge(int a)             { age = a; }
    void setColor(std::string c)   { color = c; }
    void setBreed(std::string b)   { breed = b; }
    void setOwner(std::string o)   { owner = o; }

    void display() const;
};