#include "ft_nmap.h"




int	main(int argc, char **argv)
{
	cli_t	cli = parse_cli(argc, argv);

	if (init_port_names() == -1) {
		free_cli(&cli);
		return (EXIT_FAILURE);
	}

	printf("port 22: %s\n", get_port_name(22));
	printf("port 80: %s\n", get_port_name(80));
	printf("port 443: %s\n", get_port_name(443));
	printf("port 6546: %s\n", get_port_name(6546));

	free_cli(&cli);
	free_port_names();
	return (EXIT_SUCCESS);
}
