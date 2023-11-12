#ifndef RESULT_H
#define RESULT_H

#include <memory>
#include <stdexcept>

namespace core {
template <typename TOk, typename TError>
class Result {
 public:
  /// \brief Checks whether or not the result was a success.
  /// \return true if the result is successful, false otherwise.
  [[nodiscard]] bool isOk() const { return _success; }

  /// \brief Tries to unwrap the TOk type. If the result is not ok, it will throw a logic_error() exception.
  /// \return the Ok result.
  TOk unwrap() const {
    if (!_success) {
      throw std::logic_error("unwrapped a non-successful result");
    }

    return *_ok.get();
  }

  /// \brief Tries to unwrap the TError type. IF the result is not an error, it will throw a logic_error() exception.
  /// \return the Error result.
  TError unwrapErr() const {
    if (_success) {
      throw std::logic_error("unwrapped error on a successful result");
    }

    return *_error.get();
  }

  /// \brief Creates an instance of Result which indicates a successful operation.
  /// \param ok success value.
  /// \return a successful Result.
  static Result ok(std::unique_ptr<TOk> ok) {
    return Result(std::move(ok), nullptr, true);
  }

  /// \brief Creates an instance of Result which indicates a failed operation.
  /// \param error
  /// \return a failed Result.
  static Result err(std::unique_ptr<TError> error) {
    return Result(nullptr, std::move(error), false);
  }

 private:
  std::unique_ptr<TOk> _ok;
  std::unique_ptr<TError> _error;
  bool _success;

  Result(std::unique_ptr<TOk> ok, std::unique_ptr<TError> error, bool success) {
    if (ok != nullptr) {
      _ok = std::move(ok);
    } else {
      _ok = nullptr;
    }

    if (error != nullptr) {
      _error = std::move(error);
    } else {
      _error = nullptr;
    }

    _success = success;
  }
};
}  // namespace core

#endif  //RESULT_H
