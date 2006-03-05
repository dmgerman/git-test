#ifndef RUN_COMMAND_H
#define RUN_COMMAND_H

#define MAX_RUN_COMMAND_ARGS 256
enum {
	ERR_RUN_COMMAND_FORK = 10000,
	ERR_RUN_COMMAND_EXEC,
	ERR_RUN_COMMAND_WAITPID,
	ERR_RUN_COMMAND_WAITPID_WRONG_PID,
	ERR_RUN_COMMAND_WAITPID_SIGNAL,
	ERR_RUN_COMMAND_WAITPID_NOEXIT,
};

#define RUN_COMMAND_NO_STDIO 1
#define RUN_GIT_CMD	     2	/*If this is to be git sub-command */
int run_command_v_opt(int argc, const char **argv, int opt);
int run_command_v(int argc, const char **argv);
int run_command(const char *cmd, ...);

#endif
