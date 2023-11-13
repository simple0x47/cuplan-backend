#include <gtest/gtest.h>

#include "core/BitwardenSecretsManager.h"
#include "core/ConfigurationReader.h"
#include "core/Constants.h"

core::ConfigurationReader getConfigurationReader() {
  return core::ConfigurationReader(core::DEVELOPMENT_ENVIRONMENT);
}

TEST(BitwardenSecretsManagerTest, GetSecret_ExampleSecretId_SecretValue) {
  core::ConfigurationReader configReader = getConfigurationReader();
  const std::string expectedSecret = "le_secret :)";
  const std::string accessToken =
      std::getenv(core::SECRETS_MANAGER_ACCESS_TOKEN_ENV);
  const std::string secretId =
      configReader.read().unwrap()["SecretsManager"]["TestSecretId"];

  core::BitwardenSecretsManager secretsManager =
      core::BitwardenSecretsManager(std::make_unique<std::string>(accessToken));

  core::Result<std::string, Error> result =
      secretsManager.getSecret(std::make_unique<std::string>(secretId));

  ASSERT_TRUE(result.isOk());
  ASSERT_EQ(expectedSecret, result.unwrap());
}