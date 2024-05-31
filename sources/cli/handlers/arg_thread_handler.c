#include "nmap/cli.h"

void	arg_thread_handler(cli_builder_t *cli_builder, char *arg)
{
	cli_builder->threads = atoi(arg);

	if (cli_builder->threads < 0 || cli_builder->threads > 250) {
		fprintf(stderr, "Error: %d is invalide number of threads, must be [0 - 250]\n", cli_builder->threads);
		free_cli_builder(cli_builder);
		exit(EXIT_FAILURE);
	}
}
