#ifndef BITWARDENSECRETSMANAGER_H
#define BITWARDENSECRETSMANAGER_H
#include "ISecretsManager.h"

namespace core {

/// \brief User of Bitwarden's secrets manager CLI. The program 'bws' must be
/// located within the PATH environment variable.
class BitwardenSecretsManager final : ISecretsManager {
 public:
  BitwardenSecretsManager(std::unique_ptr<std::string> accessToken);
  ~BitwardenSecretsManager() override = default;

  Result<std::string, Error> getSecret(
      std::unique_ptr<std::string> secretId) override;

 private:
  std::unique_ptr<std::string> _accessToken;
};

}  // namespace core

#endif  //BITWARDENSECRETSMANAGER_H
