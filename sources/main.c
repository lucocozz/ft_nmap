#include "ft_nmap.h"


int	main(int argc, char **argv)
{
	cli_t	cli = parse_cli(argc, argv);

	if (init_port_names() == -1) {
		free_cli(&cli);
		return (EXIT_FAILURE);
	}

	free_cli(&cli);
	free_port_names();
	return (EXIT_SUCCESS);
}
