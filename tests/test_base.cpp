#include "test_base.h"

#include "core/ErrorKind.h"

#include <filesystem>
#include <gtest/gtest.h>
#include <unistd.h>

core::Result<Empty, Error> initializeNewEnvironment() {
  pid_t scriptId = fork();

  if (scriptId == -1) {
    return core::Result<Empty, Error>::err(std::make_unique<Error>(Error(
        FAILED_TO_CREATE_CHILD_PROCESS, "failed to create child process.")));
  }

  if (scriptId == 0) {
    std::filesystem::path rootDir =
        std::filesystem::current_path().parent_path().parent_path();
    std::string composeDir = rootDir.string() + "/compose/";
    std::string bashScript = composeDir + "dev.sh";

    execl("/bin/bash", "/bin/bash", bashScript.c_str(), composeDir.c_str());

    _exit(127);
  }

  int status;
  waitpid(scriptId, &status, 0);

  if (!(WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
    return core::Result<Empty, Error>::err(std::make_unique<Error>(
        Error(FAILED_TO_RUN_COMMAND, "failed to run 'dev.sh' script.")));
  }

  return core::Result<Empty, Error>::ok(std::make_unique<Empty>(Empty{}));
}

TEST(TestBase, InitializeNewEnvironment_Succeeds) {
  core::Result<Empty, Error> result = initializeNewEnvironment();

  ASSERT_TRUE(result.isOk());
}
