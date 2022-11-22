//
// Created by Alex Campean on 03.04.2022.
//

#pragma once
#include <string>

class Dog {
private:
    std::string breed;
    std::string name;
    double age;
    std::string image; /// Uniquely identifies a dog

public:
    /// Constructors, Destructor
    Dog();
    Dog(const std::string& newBreed, const std::string& newName, double newAge, const std::string& newImage);
    Dog(Dog& dog);
    ~Dog();

    /// Getters
    std::string getBreed() const;
    std::string getName() const;
    double getAge() const;
    std::string getImage() const;

    /// Setters
    void setBreed(const std::string& newBreed);
    void setName(const std::string& newName);
    void setAge(double newAge);
    void setImage(const std::string& newImage);

    /// <summary>Sets all non-unique attributes</summary>
    /// <param name="breed">string, dog's updated breed</param>
    /// <param name="name">string, dog's updated name</param>
    /// <param name="age">int, dog's updated age</param>
    /// <returns></returns
    void setNonUniqueAttributes(const std::string& newBreed, const std::string& newName, double newAge);

    /// Operator overload
    Dog& operator=(const Dog& dog);
    bool operator==(const Dog& dog) const;
    bool operator==(const std::string& newImage) const;

    /// String representation

    /// <summary>Returns the string representation of the dog</summary>
    /// <param name=""></param>
    /// <returns>A string containing the string representation of the dog</returns
    std::string toString() const;
};


