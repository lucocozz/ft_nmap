#include "cli.h"

void free_cli(cli_t *cli)
{
	if (cli->ports != NULL)
		free(cli->ports);

	if (cli->targets != NULL)
		free_targets(&cli->targets);
}
