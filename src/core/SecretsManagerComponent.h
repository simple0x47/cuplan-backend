#ifndef SECRETSMANAGERCOMPONENT_H
#define SECRETSMANAGERCOMPONENT_H

#include <fruit/fruit.h>

#include "BitwardenSecretsManager.h"
#include "ISecretsManager.h"

using SecretsManagerFactory =
    std::function<std::unique_ptr<core::ISecretsManager>(std::string)>;

inline fruit::Component<SecretsManagerFactory> getSecretsManagerComponent() {
  return fruit::createComponent()
      .bind<core::ISecretsManager, core::BitwardenSecretsManager>();
}

#endif  // SECRETSMANAGERCOMPONENT_H
