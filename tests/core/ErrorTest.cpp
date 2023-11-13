#include <gtest/gtest.h>

#include "core/Error.h"

TEST(ErrorTest, ErrorKind_ExpectedErrorKind) {
  const std::string expectedErrorKind = "error hahaha";
  std::unique_ptr<std::string> errorKind =
      std::make_unique<std::string>(expectedErrorKind);
  std::unique_ptr<std::string> message = std::make_unique<std::string>("a");

  Error error = Error(std::move(errorKind), std::move(message));

  ASSERT_EQ(expectedErrorKind, error.errorKind());
}

TEST(ErrorTest, Message_ExpectedMessage) {
  const std::string expectedMessage = "THAT'S WHAT SHE SAID!";
  std::unique_ptr<std::string> errorKind = std::make_unique<std::string>("a");
  std::unique_ptr<std::string> message =
      std::make_unique<std::string>(expectedMessage);

  Error error = Error(std::move(errorKind), std::move(message));

  ASSERT_EQ(expectedMessage, error.message());
}

TEST(ErrorTest, ErrorKind_NullAfterMove) {
  std::unique_ptr<std::string> errorKind = std::make_unique<std::string>("a");
  std::unique_ptr<std::string> message = std::make_unique<std::string>("a");

  Error error = Error(std::move(errorKind), std::move(message));

  ASSERT_EQ(nullptr, error.errorKind());
}

TEST(ErrorTest, Message_NullAfterMove) {
  std::unique_ptr<std::string> errorKind = std::make_unique<std::string>("a");
  std::unique_ptr<std::string> message = std::make_unique<std::string>("a");

  Error error = Error(std::move(errorKind), std::move(message));

  ASSERT_EQ(nullptr, error.message());
}