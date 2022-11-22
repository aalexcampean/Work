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
        case ExceptionTypes::EmptyFieldException:
            return "Empty field input";
        case ExceptionTypes::DeleteException:
            return  "Dog does not exist";
        case ExceptionTypes::DefaultException:
            return "Default exception";
        default:
            return "Exception";
    }
}
