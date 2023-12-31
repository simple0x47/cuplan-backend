#include "BitwardenSecretsManager.h"

#include <array>
#include <cstdio>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

#include "ErrorKind.h"

namespace core {
BitwardenSecretsManager::BitwardenSecretsManager(std::string accessToken) {
  _accessToken = std::move(accessToken);
}

Result<std::string, Error> BitwardenSecretsManager::getSecret(
    const std::string secretId) {
  const std::string command =
      "bws secret get " + secretId + " --access-token " + _accessToken;
  std::array<char, 256> buffer{};
  std::string result;
  FILE* pipe = popen(command.c_str(), "r");

  if (!pipe) {
    return Result<std::string, Error>::err(std::make_unique<Error>(
        Error(FAILED_TO_RUN_COMMAND, "failed to run 'bws' command.")));
  }

  while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
    result += buffer.data();
  }

  const int exitCode = pclose(pipe);

  if (exitCode != 0) {
    return Result<std::string, Error>::err(std::make_unique<Error>(
        Error(COMMAND_EXITED_WITH_NON_ZERO_CODE,
              "'bws' exited with a non zero code: " + result)));
  }

  nlohmann::json jsonResult = nlohmann::json::parse(result);

  return Result<std::string, Error>::ok(
      std::make_unique<std::string>(jsonResult["value"]));
}

}  // namespace core