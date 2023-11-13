#include <gtest/gtest.h>

#include "../test_base.h"
#include "core/ConfigurationReader.h"

TEST(ConfigurationReaderTest, Read_DevelopmentEnvironment_ReturnsExpectedJson) {
  const std::string expectedValue = "le test :)";
  core::ConfigurationReader reader = getConfigurationReader();

  nlohmann::json json = reader.read().unwrap();

  ASSERT_EQ(expectedValue, json["ConfigurationReader"]["Test"]);
}

TEST(ConfigurationReaderTest,
     Read_DevelopmentEnvironmentMultipleTimes_ReturnsExpectedJson) {
  const std::string expectedValue = "le test :)";
  core::ConfigurationReader reader = getConfigurationReader();

  reader.read();
  reader.read();
  nlohmann::json json = reader.read().unwrap();

  ASSERT_EQ(expectedValue, json["ConfigurationReader"]["Test"]);
}