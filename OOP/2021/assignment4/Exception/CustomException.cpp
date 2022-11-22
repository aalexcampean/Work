#include "CustomException.h"

CustomException::CustomException(int given_errorCode, const std::string &given_message) noexcept{
    this->errorCode = given_errorCode;
    this->message = given_message;
}

const char *CustomException::what() const noexcept {
    return this->message.c_str();
}