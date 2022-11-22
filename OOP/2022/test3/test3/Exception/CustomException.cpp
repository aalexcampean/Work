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
            return "Equation already exists";
        case ExceptionTypes::InvalidDoubleCoefficient:
            return "Invalid input for coefficient - should be of type double";
        case ExceptionTypes::InvalidZeroCoefficient:
            return "Invalid input for coefficient A - should be non zero";
        case ExceptionTypes::DefaultException:
            return "Default exception";
        default:
            return "Exception";
    }
}
