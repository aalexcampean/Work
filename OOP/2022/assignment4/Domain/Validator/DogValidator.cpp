//
// Created by Alex Campean on 13.04.2022.
//

#include <iostream>
#include "DogValidator.h"
#include "../../Exception/CustomException.h"

void DogValidator::validateDog(const std::string &breed, const std::string &name, const std::string &age,
                               const std::string &image) {
    validateBreed(breed);
    validateName(name);
    validateAge(age);
    validateImage(image);
}

void DogValidator::validateBreed(const std::string &breed) {
    if (breed.empty()) {
        throw CustomException(ExceptionTypes::InvalidEmptyInput);
    }
}

void DogValidator::validateName(const std::string &name) {
    if (name.empty()) {
        throw CustomException(ExceptionTypes::InvalidEmptyInput);
    }
}

void DogValidator::validateAge(const std::string &age) {
    double validatedAge;
    size_t pos1;
    try {
        validatedAge = std::stoi(age, &pos1);
    }
    catch (std::invalid_argument invalidArgument) {
        throw invalidArgument;
    }

    if (pos1 != age.size()) {
        throw CustomException(ExceptionTypes::InvalidDoubleInput);
    }

    if (validatedAge < 0 || validatedAge > 30) {
        throw CustomException(ExceptionTypes::InvalidAgeInput);
    }
}

void DogValidator::validateImage(const std::string &image) {
    if (image.rfind("https://", 0) != 0) {
        throw CustomException(ExceptionTypes::InvalidLinkInput);
    }
}
