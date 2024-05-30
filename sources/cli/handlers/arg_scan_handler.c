#include "ft_nmap/cli.h"
#include "ft_nmap/scan.h"
#include <string.h>

typedef struct scan_list {
	scan_type_t	type;
	char		*name;
} scan_list_t;

static scan_list_t _g_scan_types[] = {
	{ SYN_SCAN,  "SYN" },
	{ NULL_SCAN, "NULL"},
	{ ACK_SCAN,  "ACK" },
	{ FIN_SCAN,  "FIN" },
	{ XMAS_SCAN, "XMAS"},
	{ UDP_SCAN,  "UDP" },
	{ 0, NULL }
};


static scan_type_t	__get_scan_type(char *arg)
{
	for (size_t i = 0; _g_scan_types[i].type; ++i)
	{
		if (strcmp(arg, _g_scan_types[i].name) == 0)
			return (_g_scan_types[i].type);
	}
	return (0);
}

void	arg_scan_handler(cli_builder_t *cli_builder, char *arg)
{
	char **scan_args = split(arg, " ,;");

	for (size_t i = 0; scan_args[i]; ++i)
	{
		str_upper(scan_args[i]);
		scan_type_t type = __get_scan_type(scan_args[i]);
		if (type == 0) {
			fprintf(stderr, "Error: '%s' unknown scan type\n", scan_args[i]);
			free_cli_builder(cli_builder);
			exit(EXIT_FAILURE);
		}
		cli_builder->scans |= type;
	}
}
