#include <gtest/gtest.h>

#include "core/ConfigurationReader.h"
#include "core/Constants.h"

TEST(ConfigurationReaderTest, Read_DevelopmentEnvironment_ReturnsExpectedJson) {
  const std::string expectedValue = "le test :)";
  core::ConfigurationReader reader =
      core::ConfigurationReader(core::DEVELOPMENT_ENVIRONMENT);

  nlohmann::json json = reader.read().unwrap();

  ASSERT_EQ(expectedValue, json["ConfigurationReader"]["Test"]);
}

TEST(ConfigurationReaderTest,
Read_DevelopmentEnvironmentMultipleTimes_ReturnsExpectedJson) {
  const std::string expectedValue = "le test :)";
  core::ConfigurationReader reader =
      core::ConfigurationReader(core::DEVELOPMENT_ENVIRONMENT);

  reader.read();
  reader.read();
  nlohmann::json json = reader.read().unwrap();

  ASSERT_EQ(expectedValue, json["ConfigurationReader"]["Test"]);
}