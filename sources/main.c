#include "ft_nmap.h"


int	main(int argc, char **argv)
{
	cli_t	cli = parse_cli(argc, argv);

	for (size_t i = 0; i < cli.ports_size; ++i)
		printf("%d ", cli.ports[i]);

	printf("\n");
	for (size_t i = 0; cli.targets[i] != NULL; ++i)
		printf("%s ", cli.targets[i]);
	printf("\n");

	free_cli(&cli);
	return (EXIT_SUCCESS);
}
