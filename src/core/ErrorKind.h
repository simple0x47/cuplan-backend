#ifndef ERRORKIND_H
#define ERRORKIND_H

inline const char *INVALID_SECRET_ID = "invalid_secret_id";
inline const char *FAILED_TO_RUN_COMMAND = "failed_to_run_command";
inline const char *COMMAND_EXITED_WITH_NON_ZERO_CODE =
    "command_exited_with_non_zero_code";
inline const char *FAILED_TO_CREATE_CHILD_PROCESS =
    "failed_to_create_child_process";

#endif // ERRORKIND_H
