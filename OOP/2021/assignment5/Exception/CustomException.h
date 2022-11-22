#include <exception>
#include <string>

class CustomException : public std::exception {
private:
    int errorCode;
    std::string message;

public:
    CustomException(int errorCode, const std::string &message) noexcept;
    virtual ~CustomException() = default;
    virtual const char* what() const noexcept override;
};

