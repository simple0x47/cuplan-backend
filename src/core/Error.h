#ifndef ERROR_H
#define ERROR_H

#include <string>
#include <utility>

class Error {
 public:
  Error(std::string errorKind, std::string message) {
    _errorKind = std::move(errorKind);
    _message = std::move(message);
  }

  std::string errorKind() { return _errorKind; }

  std::string message() { return _message; }

 private:
  std::string _errorKind;
  std::string _message;
};

#endif  //ERROR_H
