#include <gtest/gtest.h>

#include "../test_base.h"
#include "core/ConfigurationReader.h"
#include "core/ErrorKind.h"
#include "core/SecretsManagerComponent.h"

std::unique_ptr<core::ISecretsManager> getSecretsManager() {
  const std::string accessToken =
      std::getenv(core::SECRETS_MANAGER_ACCESS_TOKEN_ENV);
  std::unique_ptr<std::string> accessTokenPointer =
      std::make_unique<std::string>(accessToken);

  fruit::Injector<SecretsManagerFactory> injector(getSecretsManagerComponent);
  SecretsManagerFactory factory(injector);

  std::unique_ptr<core::ISecretsManager> secretsManager =
      factory(&accessTokenPointer);

  return secretsManager;
}

TEST(SecretsManagerComponentTest, Injection_WorksAsExpected) {
  std::unique_ptr<core::ISecretsManager> secretsManager = getSecretsManager();
  std::unique_ptr<std::string> nonExistingSecret =
      std::make_unique<std::string>(std::string("abcd1234"));

  core::Result<std::string, Error> result =
      secretsManager->getSecret(std::move(nonExistingSecret));

  ASSERT_FALSE(result.isOk());
  ASSERT_EQ(COMMAND_EXITED_WITH_NON_ZERO_CODE, result.unwrapErr().errorKind());
}