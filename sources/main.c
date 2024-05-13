#include "ft_nmap.h"


int	main(int argc, char **argv)
{
	cli_t	cli = parse_cli(argc, argv);

	printf("Target: %s\n", cli.target);
	return (EXIT_SUCCESS);
}
