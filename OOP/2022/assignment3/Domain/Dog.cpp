//
// Created by Alex Campean on 03.04.2022.
//

#include <iomanip>
#include <sstream>
#include "Dog.h"

/// Constructors, Destructor
Dog::Dog() {
    this->breed = "";
    this->name = "";
    this->age = 0;
    this->image = "";
}

Dog::Dog(const std::string& newBreed, const std::string& newName, double newAge, const std::string& newImage) {
    this->breed = newBreed;
    this->name = newName;
    this->age = newAge;
    this->image = newImage;
}

Dog::Dog(Dog &dog) {
    this->breed = dog.breed;
    this->name = dog.name;
    this->age = dog.age;
    this->image = dog.image;
}

Dog::~Dog() {
}

/// Getters
std::string Dog::getBreed() const {
    return this->breed;
}

std::string Dog::getName() const {
    return this->name;
}

double Dog::getAge() const {
    return this->age;
}

std::string Dog::getImage() const {
    return this->image;
}

/// Setters
void Dog::setBreed(const std::string& newBreed) {
    this->breed = newBreed;
}

void Dog::setName(const std::string& newName) {
    this->name = newName;
}

void Dog::setAge(double newAge) {
    this->age = newAge;
}

void Dog::setImage(const std::string& newImage) {
    this->image = newImage;
}

void Dog::setNonUniqueAttributes(const std::string& newBreed, const std::string& newName, double newAge) {
    this->setBreed(newBreed);
    this->setName(newName);
    this->setAge(newAge);
}

/// Operator Overload
Dog &Dog::operator=(const Dog& dog) {
    this->breed = dog.breed;
    this->name = dog.name;
    this->age = dog.age;
    this->image = dog.image;

    return *this;
}

bool Dog::operator==(const Dog& dog) const {
    return this->image == dog.image;
}

bool Dog::operator==(const std::string& newImage) const {
    return this->image == newImage;
}

/// String Representation
std::string Dog::toString() const {
    std::string ageMeasureUnit;
    this->age < 1? ageMeasureUnit = "months" : ageMeasureUnit = "years";

    std::stringstream ageStream;
    ageStream << std::fixed << std::setprecision(1) << this->age;

    std::string destination_string =
            "Breed: " + this->breed + "  |  " +
            "Name: " + this->name + "  |  " +
            "Age: " + ageStream.str() + " " + ageMeasureUnit + "  |  " +
            "Image: " + this->image;

    return destination_string;
}


