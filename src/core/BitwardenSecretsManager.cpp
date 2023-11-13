#include <array>
#include <cstdio>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>

#include "BitwardenSecretsManager.h"

#include "ErrorKind.h"

namespace core {
BitwardenSecretsManager::BitwardenSecretsManager(
    std::unique_ptr<std::string> accessToken) {
  _accessToken = std::move(accessToken);
}

Result<std::string, Error> BitwardenSecretsManager::getSecret(
    const std::unique_ptr<std::string> secretId) {
  if (secretId == nullptr) {
    return Result<std::string, Error>::err(std::make_unique<Error>(
        Error(std::make_unique<std::string>(INVALID_SECRET_ID),
              std::make_unique<std::string>("'secretId' is a nullptr."))));
  }

  std::string command =
      "bws secret get " + *secretId + " --access-token " + *_accessToken;
  std::array<char, 256> buffer;
  std::string result;
  std::shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

  if (!pipe) {
    return Result<std::string, Error>::err(std::make_unique<Error>(
        Error(std::make_unique<std::string>(FAILED_TO_RUN_COMMAND),
              std::make_unique<std::string>("failed to run 'bws' command."))));
  }

  while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
    result += buffer.data();
  }

  nlohmann::json jsonResult = nlohmann::json::parse(result);

  return Result<std::string, Error>::ok(
      std::make_unique<std::string>(jsonResult["value"]));
}

}  // namespace core