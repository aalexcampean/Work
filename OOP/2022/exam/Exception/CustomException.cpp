//
// Created by Alex Campean on 11.06.2022.
//


#include "CustomException.h"

CustomException::CustomException() {
    this->exception = ExceptionTypes::DefaultException;
}

CustomException::CustomException(ExceptionTypes e) noexcept{
    this->exception = e;
}

const char * CustomException::what() const noexcept {
    switch (this->exception) {
        case ExceptionTypes::EmptyFieldException:
            return "Invalid empty field";
        case ExceptionTypes::InvalidActException:
            return  "Invalid act";
        case ExceptionTypes::DefaultException:
            return "Default exception";
        default:
            return "Exception";
    }
}
