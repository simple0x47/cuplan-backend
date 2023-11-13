#include <fstream>
#include <utility>

#include "ConfigurationReader.h"

namespace core {
ConfigurationReader::ConfigurationReader(std::string environment) {
  _environment = std::move(environment);
  _configuration = nullptr;
}

ConfigurationReader::~ConfigurationReader() = default;

Result<nlohmann::json, Error> ConfigurationReader::read() {
  if (_configuration == nullptr) {
    const std::string configurationFile = "config." + _environment + ".json";
    std::ifstream f(configurationFile);

    _configuration = nlohmann::json::parse(f);

    f.close();
  }

  return Result<nlohmann::json, Error>::ok(
      std::make_unique<nlohmann::json>(_configuration));
}

}  // namespace core