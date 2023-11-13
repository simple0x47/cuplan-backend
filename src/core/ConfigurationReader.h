#ifndef CONFIGURATIONREADER_H
#define CONFIGURATIONREADER_H

#include <nlohmann/json.hpp>
#include <string>

#include "Error.h"
#include "Result.h"

namespace core {
class ConfigurationReader {
 public:
  explicit ConfigurationReader(std::string environment);
  ~ConfigurationReader();

  Result<nlohmann::json, Error> read();

 private:
  std::string _environment;
  nlohmann::json _configuration;
};
}  // namespace core

#endif  //CONFIGURATIONREADER_H
