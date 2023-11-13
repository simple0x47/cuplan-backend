#ifndef BITWARDENSECRETSMANAGER_H
#define BITWARDENSECRETSMANAGER_H
#include <fruit/fruit.h>

#include "ISecretsManager.h"

namespace core {

/// \brief User of Bitwarden's secrets manager CLI. The program 'bws' must be
/// located within the PATH environment variable.
class BitwardenSecretsManager final : public ISecretsManager {
 public:
  INJECT(BitwardenSecretsManager(ASSISTED(std::string) accessToken));
  ~BitwardenSecretsManager() override = default;

  Result<std::string, Error> getSecret(std::string secretId) override;

 private:
  std::string _accessToken;
};

}  // namespace core

#endif  // BITWARDENSECRETSMANAGER_H
