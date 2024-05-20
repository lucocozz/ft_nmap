#include "cli.h"
#include <sys/param.h>

typedef struct _port_range_s {
	int start;
	int end;
} _port_range_t;


static int	__check_port_validity(int port)
{
	if (port < 0 || port > 65535) {
		fprintf(stderr, "Invalid port: %d\n", port);
		return (-1);
	}
	return (0);
}

static int	__port_range(_port_range_t *range, char *port_args)
{
	int start, end;
	char *endptr = NULL;

	start = strtoul(port_args, &endptr, 10);
	if (*endptr == '\0')
		end = start;
	else if (sscanf(port_args, "%d-%d", &start, &end) != 2) {
		fprintf(stderr, "Invalid port range: %s\n", port_args);
		return (-1);
	}

	if (__check_port_validity(start) || __check_port_validity(end) == -1)
		return (-1);
	
	range->start = MIN(start, end);
	range->end = MAX(start, end);
	
	return (0);
}

static int	__insert_ports(RBTree_t *ports, _port_range_t range)
{
	for (int i = range.start; i <= range.end; ++i)
	{
		if (rbt_insert(ports, &i, RBT_ALLOC_DATA) == ENOMEM) {
			fprintf(stderr, "Failed to parse ports\n");
			return (-1);
		}
	}
	return (0);
}

static RBTree_t	*__parse_ports(char *arg)
{
	char		**port_args = split(arg, ",");
	RBTree_t	*ports = rbt_new(RBT_INT);

	if (ports == NULL) {
		fprintf(stderr, "Failed to parse ports\n");
		return (NULL);
	}

	for (int i = 0; port_args[i] != NULL; ++i)
	{
		_port_range_t range;

		if (__port_range(&range, port_args[i]) == -1) {
			rbt_destroy(ports);
			return (NULL);
		}

		if (__insert_ports(ports, range) == -1) {
			rbt_destroy(ports);
			return (NULL);
		}
	}

	return (ports);
}

void	arg_ports_handler(cli_t *cli, char *arg)
{
	RBTree_t	*ports = __parse_ports(arg);

	if (ports == NULL) {
		free_cli(cli);
		exit(EXIT_FAILURE);
	}
	cli->ports = ports;
}
