//
// Created by Alex Campean on 11.06.2022.
//

#pragma once

#include <exception>
#include <string>
#include <map>

enum class ExceptionTypes {
    EmptyFieldException,
    InvalidActException,
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