#ifndef TESTBASE_H
#define TESTBASE_H
#include "core/ConfigurationReader.h"
#include "core/Constants.h"

#include <gtest/gtest.h>

inline core::ConfigurationReader getConfigurationReader() {
  return core::ConfigurationReader(core::DEVELOPMENT_ENVIRONMENT);
}

class TestBase : public testing::Test {
protected:
  void SetUp() override;
  void TearDown() override;

private:
  pid_t _apiRunnerProcessId = -1;
};

#endif // TESTBASE_H
