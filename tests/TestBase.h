#ifndef TESTBASE_H
#define TESTBASE_H
#include "core/BitwardenSecretsManager.h"
#include "core/ConfigurationReader.h"
#include "core/Constants.h"
#include "core/ISecretsManager.h"

#include <cpr/cpr.h>
#include <gtest/gtest.h>

inline core::ConfigurationReader getConfigurationReader() {
  return core::ConfigurationReader(core::DEVELOPMENT_ENVIRONMENT);
}

class TestBase : public testing::Test {
public:
  void TestBody() override {
    const core::Result<nlohmann::json, Error> configReaderResult =
        getConfigurationReader().read();

    if (!configReaderResult.isOk()) {
      throw std::runtime_error(
          std::string("configuration reader returned an Error: ") +
          configReaderResult.unwrapErr().message());
    }

    config = configReaderResult.unwrap();

    sslOptions =
        cpr::Ssl(cpr::ssl::VerifyHost{false}, cpr::ssl::VerifyPeer{false},
                 cpr::ssl::VerifyStatus{false});

    std::string secretsManagerAccessToken =
        std::getenv(core::SECRETS_MANAGER_ACCESS_TOKEN_ENV);

    if (secretsManagerAccessToken.empty()) {
      throw std::runtime_error("secrets manager access token is empty");
    }

    secretsManager = std::make_unique<core::BitwardenSecretsManager>(
        core::BitwardenSecretsManager(std::move(secretsManagerAccessToken)));
  }

protected:
  void SetUp() override;
  void TearDown() override;

  nlohmann::json config;
  cpr::SslOptions sslOptions;
  std::unique_ptr<core::ISecretsManager> secretsManager;

private:
  pid_t _apiRunnerProcessId = -1;
};

#endif // TESTBASE_H
