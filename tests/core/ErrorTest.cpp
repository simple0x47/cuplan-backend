#include <gtest/gtest.h>

#include "core/Error.h"

TEST(ErrorTest, ErrorKind_ExpectedErrorKind) {
  const std::string expectedErrorKind = "error hahaha";
  std::string message = std::string("a");

  Error error = Error(expectedErrorKind, std::move(message));

  ASSERT_EQ(expectedErrorKind, error.errorKind());
}

TEST(ErrorTest, Message_ExpectedMessage) {
  const std::string expectedMessage = "THAT'S WHAT SHE SAID!";
  std::string errorKind = std::string("a");

  Error error = Error(std::move(errorKind), expectedMessage);

  ASSERT_EQ(expectedMessage, error.message());
}