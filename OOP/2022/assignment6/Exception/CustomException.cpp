#include "CustomException.h"

CustomException::CustomException() {
    this->exception = ExceptionTypes::DefaultException;
}

CustomException::CustomException(ExceptionTypes e) noexcept{
    this->exception = e;
}

const char * CustomException::what() const noexcept {
    switch (this->exception) {
        case ExceptionTypes::AddException:
            return "Dog already exists";
        case ExceptionTypes::DeleteException:
            return  "Dog does not exist";
        case ExceptionTypes::UpdateException:
            return "Dog does not exist";
        case ExceptionTypes::LogInException:
            return "Invalid Password";
        case ExceptionTypes::InvalidEmptyInput:
            return "Invalid empty field input";
        case ExceptionTypes::InvalidDoubleInput:
            return "Invalid input - should be of type double";
        case ExceptionTypes::InvalidAgeInput:
            return "Invalid numeric value for a dog's age - should be in interval (0, 30)";
        case ExceptionTypes::InvalidLinkInput:
            return "Invalid dog image - should begin with: https://";
        case ExceptionTypes::DefaultException:
            return "Default exception";
        default:
            return "Exception";
    }
}
