#include <gtest/gtest.h>

#include "../test_base.h"
#include "core/ConfigurationReader.h"
#include "core/ErrorKind.h"
#include "core/SecretsManagerComponent.h"

std::unique_ptr<core::ISecretsManager> getSecretsManager() {
  std::string accessToken = std::getenv(core::SECRETS_MANAGER_ACCESS_TOKEN_ENV);

  fruit::Injector<SecretsManagerFactory> injector(getSecretsManagerComponent);
  SecretsManagerFactory factory(injector);

  std::unique_ptr<core::ISecretsManager> secretsManager =
      factory(std::move(accessToken));

  return secretsManager;
}

TEST(SecretsManagerComponentTest, Injection_WorksAsExpected) {
  std::unique_ptr<core::ISecretsManager> secretsManager = getSecretsManager();
  std::string nonExistingSecret = "abcd1234";

  core::Result<std::string, Error> result =
      secretsManager->getSecret(std::move(nonExistingSecret));

  ASSERT_FALSE(result.isOk());
  ASSERT_EQ(COMMAND_EXITED_WITH_NON_ZERO_CODE, result.unwrapErr().errorKind());
}