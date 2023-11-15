#ifndef LOGINSUCCESS_H
#define LOGINSUCCESS_H
#include <nlohmann/detail/macro_scope.hpp>
#include <string>

struct LoginSuccess {
  std::string accessToken;
  std::string idToken;
  std::string refreshToken;
  unsigned long expiresIn;

  NLOHMANN_DEFINE_TYPE_INTRUSIVE(LoginSuccess, accessToken, idToken,
                                 refreshToken, expiresIn);
};

#endif // LOGINSUCCESS_H
