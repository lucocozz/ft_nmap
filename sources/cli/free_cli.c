#include "cli.h"

void free_cli_builder(cli_builder_t *cli_builder)
{
	if (cli_builder->ports != NULL)
		rbt_destroy(cli_builder->ports);

	if (cli_builder->excluded_ports != NULL)
		rbt_destroy(cli_builder->excluded_ports);

	if (cli_builder->targets != NULL)
		rbt_destroy(cli_builder->targets);
}

void free_cli(cli_t *cli)
{
	if (cli->ports != NULL)
		free(cli->ports);

	if (cli->targets != NULL)
		free_split(cli->targets);
}
