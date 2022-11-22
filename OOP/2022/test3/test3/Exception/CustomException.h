
#pragma once

#include <exception>
#include <string>
#include <map>

enum class ExceptionTypes {
    AddException,
    InvalidDoubleCoefficient,
    InvalidZeroCoefficient,
    DefaultException
};

class CustomException : public std::exception {
private:
    ExceptionTypes exception;

public:
    CustomException();
    CustomException(ExceptionTypes e) noexcept;
    ~CustomException() override = default;
    const char * what() const noexcept override;
};