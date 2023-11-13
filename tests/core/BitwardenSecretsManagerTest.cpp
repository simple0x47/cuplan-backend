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
  std::string accessToken = std::getenv(core::SECRETS_MANAGER_ACCESS_TOKEN_ENV);
  std::string secretId =
      (configReader.read().unwrap())["SecretsManager"]["TestSecretId"];

  core::BitwardenSecretsManager secretsManager =
      core::BitwardenSecretsManager(std::move(accessToken));

  core::Result<std::string, Error> result =
      secretsManager.getSecret(std::move(secretId));

  ASSERT_TRUE(result.isOk());
  ASSERT_EQ(expectedSecret, result.unwrap());
}

TEST(BitwardenSecretsManagerTest, GetSecret_NonExistingSecret_Error) {
  std::string nonExistingSecretId = "1234";
  std::string accessToken = std::getenv(core::SECRETS_MANAGER_ACCESS_TOKEN_ENV);

  core::BitwardenSecretsManager secretsManager =
      core::BitwardenSecretsManager(std::move(accessToken));

  core::Result<std::string, Error> result =
      secretsManager.getSecret(std::move(nonExistingSecretId));

  ASSERT_FALSE(result.isOk());
}