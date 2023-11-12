#include <gtest/gtest.h>

#include "core/Result.h"

TEST(ResultTest, Unwrap_SuccessfulResult_ExpectedValue) {
  constexpr int expectedNumber = 1234;
  std::unique_ptr<int> example = std::make_unique<int>(expectedNumber);

  const core::Result<int, char> result =
      core::Result<int, char>::ok(std::move(example));

  ASSERT_TRUE(result.isOk());
  ASSERT_EQ(expectedNumber, result.unwrap());
}

TEST(ResultTest, Unwrap_UnsuccessfulResult_ThrowsException) {
  constexpr char exampleError = 'a';
  std::unique_ptr<char> example = std::make_unique<char>(exampleError);

  const core::Result<int, char> result =
      core::Result<int, char>::err(std::move(example));

  ASSERT_THROW(result.unwrap(), std::logic_error);
}

TEST(ResultTest, UnwrapErr_UnsuccessfulResult_ExpectedValue) {
  const std::string expectedError = "abcd";
  std::unique_ptr<std::string> example =
      std::make_unique<std::string>(expectedError);

  const core::Result<bool, std::string> result =
      core::Result<bool, std::string>::err(std::move(example));

  ASSERT_FALSE(result.isOk());
  ASSERT_EQ(expectedError, result.unwrapErr());
}

TEST(ResultTest, UnwrapErr_SuccessfulResult_ThrowsException) {
  constexpr int exampleSuccess = 9313;
  std::unique_ptr<int> example = std::make_unique<int>(exampleSuccess);

  const core::Result<int, char> result =
      core::Result<int, char>::ok(std::move(example));

  ASSERT_THROW(result.unwrapErr(), std::logic_error);
}