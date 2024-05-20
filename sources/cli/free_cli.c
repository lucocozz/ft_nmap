#include "cli.h"

void free_cli(cli_t *cli)
{
	if (cli->ports != NULL)
		rbt_destroy(cli->ports);

	if (cli->targets != NULL)
		rbt_destroy(cli->targets);
}
