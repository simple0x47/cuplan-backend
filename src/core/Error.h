#ifndef ERROR_H
#define ERROR_H

#include <string>

class Error {
 public:
  Error(std::unique_ptr<std::string> errorKind,
        std::unique_ptr<std::string> message) {
    _errorKind = std::move(errorKind);
    _message = std::move(message);
  }

  std::string errorKind() { return *_errorKind; }

  std::string message() { return *_message; }

 private:
  std::unique_ptr<std::string> _errorKind;
  std::unique_ptr<std::string> _message;
};

#endif  //ERROR_H
