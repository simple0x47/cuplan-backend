#include "TestBase.h"

#include "core/ErrorKind.h"

#include <csignal>
#include <filesystem>
#include <gtest/gtest.h>
#include <unistd.h>

core::Result<pid_t, Error> initializeNewEnvironment();

void TestBase::SetUp() {
  const core::Result<pid_t, Error> apiRunnerProcessId =
      initializeNewEnvironment();

  if (!apiRunnerProcessId.isOk()) {
    Error error = apiRunnerProcessId.unwrapErr();
    std::cerr << "failed to initialize new environment: " + error.message()
              << std::endl;
    FAIL();
  }

  _apiRunnerProcessId = apiRunnerProcessId.unwrap();
}

void TestBase::TearDown() {
  if (_apiRunnerProcessId == -1) {
    return;
  }

  kill(_apiRunnerProcessId, SIGKILL);
}

core::Result<pid_t, Error> initializeNewEnvironment() {
  const pid_t scriptProcessId = fork();

  if (scriptProcessId == -1) {
    return core::Result<pid_t, Error>::err(std::make_unique<Error>(Error(
        FAILED_TO_CREATE_CHILD_PROCESS, "failed to create child process.")));
  }

  if (scriptProcessId == 0) {
    const std::filesystem::path rootDir =
        std::filesystem::current_path().parent_path().parent_path();
    const std::string composeDir = rootDir.string() + "/compose/";
    const std::string bashScript = composeDir + "dev.sh";
    std::cout << "dev.sh path:" + bashScript << std::endl;

    execl("/bin/bash", "/bin/bash", bashScript.c_str(), composeDir.c_str(),
          nullptr);

    _exit(127);
  }

  int scriptStatus;
  waitpid(scriptProcessId, &scriptStatus, 0);

  if (WEXITSTATUS(scriptStatus) != 0) {
    return core::Result<pid_t, Error>::err(std::make_unique<Error>(
        Error(FAILED_TO_RUN_COMMAND, "failed to run 'dev.sh' script.")));
  }

  const pid_t apiRunnerProcessId = fork();

  if (apiRunnerProcessId == -1) {
    return core::Result<pid_t, Error>::err(std::make_unique<Error>(
        Error(FAILED_TO_CREATE_CHILD_PROCESS,
              "failed to create a process for the apiRunner.")));
  }

  if (apiRunnerProcessId == 0) {
    const std::filesystem::path buildDir =
        std::filesystem::current_path().parent_path();
    const std::string apiRunnerDir = buildDir.string() + "/src/apiRunner";
    std::cout << apiRunnerDir << std::endl;
    execl(apiRunnerDir.c_str(), apiRunnerDir.c_str(), nullptr);

    _exit(127);
  }

  return core::Result<pid_t, Error>::ok(
      std::make_unique<pid_t>(apiRunnerProcessId));
}

TEST(TestBase, InitializeNewEnvironment_Succeeds) {
  const core::Result<pid_t, Error> result = initializeNewEnvironment();

  if (!result.isOk()) {
    std::cerr << result.unwrapErr().message() << std::endl;
  }

  ASSERT_TRUE(result.isOk());

  const pid_t apiRunnerProcessId = result.unwrap();

  ASSERT_EQ(0, kill(apiRunnerProcessId, 0));

  kill(apiRunnerProcessId, SIGKILL);
}