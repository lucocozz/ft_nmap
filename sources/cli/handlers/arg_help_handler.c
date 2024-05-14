#include "cli.h"

void	arg_help_handler(cli_t *cli, char *arg)
{
	UNUSED(cli); UNUSED(arg);
	printf("%s", PROGRAM_HELPER);
	free_cli(cli);
	exit(EXIT_SUCCESS);
}
