#ifndef TESTBASE_H
#define TESTBASE_H
#include "core/ConfigurationReader.h"
#include "core/Constants.h"

inline core::ConfigurationReader getConfigurationReader() {
  return core::ConfigurationReader(core::DEVELOPMENT_ENVIRONMENT);
}

#endif  //TESTBASE_H
