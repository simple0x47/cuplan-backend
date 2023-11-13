#ifndef ISECRETSMANAGER_H
#define ISECRETSMANAGER_H

#include <string>

#include "Error.h"
#include "Result.h"

namespace core {
class ISecretsManager {
 public:
  virtual ~ISecretsManager() = default;
  virtual Result<std::string, Error> getSecret(
      std::unique_ptr<std::string> secretId) = 0;
};
}  // namespace core

#endif  //ISECRETSMANAGER_H
