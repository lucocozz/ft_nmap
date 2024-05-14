#include "cli.h"

void	arg_thread_handler(cli_t *cli, char *arg)
{
	cli->threads = atoi(arg);

	if (cli->threads < 0 || cli->threads > 250) {
		fprintf(stderr, "Error: %d is invalide number of threads, must be [0 - 250]\n", cli->threads);
		free_cli(cli);
		exit(EXIT_FAILURE);
	}
}
