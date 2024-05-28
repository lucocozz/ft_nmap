#include "ft_nmap/cli.h"

void	arg_help_handler(cli_builder_t *cli_builder, char *arg)
{
	UNUSED(arg);
	printf("%s", PROGRAM_HELPER);
	free_cli_builder(cli_builder);
	exit(EXIT_SUCCESS);
}
