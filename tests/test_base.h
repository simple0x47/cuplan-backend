#ifndef TESTBASE_H
#define TESTBASE_H
#include "core/ConfigurationReader.h"
#include "core/Constants.h"
#include "core/Empty.h"

inline core::ConfigurationReader getConfigurationReader() {
  return core::ConfigurationReader(core::DEVELOPMENT_ENVIRONMENT);
}

/// \brief Prepares all the dependencies and resets their state, so they act
/// as a new environment for every integration test.
core::Result<Empty, Error> initializeNewEnvironment();

#endif // TESTBASE_H
