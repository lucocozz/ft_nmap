#include "ft_nmap.h"


int	main(int argc, char **argv)
{
	cli_t	cli = parse_cli(argc, argv);

	rbt_print(cli.targets);
	free_cli(&cli);
	return (EXIT_SUCCESS);
}
