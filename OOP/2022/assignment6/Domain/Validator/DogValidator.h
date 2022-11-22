//
// Created by Alex Campean on 13.04.2022.
//

#include <string>

class DogValidator {
public:
    static void validateDog(const std::string& breed, const std::string& name, const std::string& age, const std::string& image);
    static void validateBreed(const std::string& breed);
    static void validateName(const std::string& name);
    static void validateAge(const std::string& age);
    static void validateImage(const std::string& image);
};