#include "ft_nmap/cli.h"
#include "ft_nmap/scan.h"

static const cli_option_t	g_options[] = {
	{.short_flag = "-s",  .long_flag = "--scan",          .has_argument = true,  .arg_handler = arg_scan_handler},
	{.short_flag = "-h",  .long_flag = "--help",          .has_argument = false, .arg_handler = arg_help_handler},
	{.short_flag = "-f",  .long_flag = "--file",          .has_argument = true,  .arg_handler = arg_file_handler},
	{.short_flag = "-p",  .long_flag = "--ports",         .has_argument = true,  .arg_handler = arg_ports_handler},
	{.short_flag = "-ep", .long_flag = "--exclude-ports", .has_argument = true,  .arg_handler = arg_exclude_ports_handler},
	{.short_flag = "-t",  .long_flag = "--thread",        .has_argument = true,  .arg_handler = arg_thread_handler},
};


static const cli_option_t*	__get_option(char *flag)
{
	for (uint8_t i = 0; i < ARRAY_SIZE(g_options); ++i)
	{
		if (g_options[i].short_flag != NULL && start_with(g_options[i].short_flag, flag) == true)
			return (&g_options[i]);
		if (g_options[i].long_flag != NULL && start_with(g_options[i].long_flag, flag) == true)
			return (&g_options[i]);
	}
	return (NULL);
}

static int	__parse_options(cli_builder_t *cli_builder, int argc, char **argv)
{
	const cli_option_t	*option;

	for (int i = 1; i < argc; ++i)
	{
		if (start_with("-", argv[i]) == true)
		{
			option = __get_option(argv[i]);
			if (option == NULL) {
				fprintf(stderr, "Error: '%s' unknown option\n", argv[i]);
				return (-1);
			}

			if (option->has_argument == true)
				++i;

			if (option->arg_handler == NULL) {
				fprintf(stderr, "Error: '%s' option has no handler\n", argv[i]);
				return (-1);
			}
			option->arg_handler(cli_builder, argv[i]);
		}
		else if (rbt_insert(cli_builder->targets, argv[i]) == ENOMEM)
			return (-1);
	}
	return (0);
}

static void	__exclude_ports(cli_builder_t *cli_builder)
{
	RBT_Iter_t	*it = rbt_begin(cli_builder->excluded_ports);

	while (it != NULL)
	{
		RBT_Iter_t	*to_erase = it;
		rbt_it_next(&it);
		rbt_erase(cli_builder->ports, to_erase->data);
	}
}

static int*	__build_ports(RBTree_t *ports)
{
	int *ports_array = malloc(sizeof(int) * ports->size);
	if (ports == NULL)
		return (NULL);

	RBT_Iter_t	*it = rbt_begin(ports);
	for (uint i = 0; it != NULL; ++i) {
		ports_array[i] = *(int*)it->data;
		rbt_it_next(&it);
	}

	return (ports_array);
}

static char**	__build_targets(RBTree_t *targets)
{
	char **targets_array = malloc(sizeof(char*) * (targets->size + 1));
	if (targets_array == NULL)
		return (NULL);

	size_t i = 0;
	RBT_Iter_t	*it = rbt_begin(targets);
	while (it != NULL) {
		targets_array[i++] = strdup(it->data);
		rbt_it_next(&it);
	}
	targets_array[i] = NULL;
	return (targets_array);
}

static cli_t	__build_cli(cli_builder_t *cli_builder)
{
	cli_t	cli = INITIALIZE_CLI;

	if (rbt_empty(cli_builder->ports) == true)
		get_default_ports(cli_builder);

	if (cli_builder->excluded_ports != NULL)
		__exclude_ports(cli_builder);
	
	cli.threads = cli_builder->threads;
	cli.ports_size = cli_builder->ports->size;
	cli.ports = __build_ports(cli_builder->ports);
	cli.targets = __build_targets(cli_builder->targets);
	if (cli_builder->scans == 0)
		cli.scans = SYN_SCAN;
	else
		cli.scans = cli_builder->scans;

	free_cli_builder(cli_builder);
	return (cli);
}

cli_t parse_cli(int argc, char **argv)
{
	cli_builder_t cli_builder = INITIALIZE_CLI_BUILDER;

	if (argc == 1) {
		fprintf(stderr, "%s", PROGRAM_HELPER);
		exit(EXIT_FAILURE);
	}

	cli_builder.targets = rbt_new(RBT_STR);
	cli_builder.ports = rbt_new(RBT_INT);
	if (cli_builder.targets == NULL || cli_builder.ports == NULL) {
		free_cli_builder(&cli_builder);
		fprintf(stderr, "Error: failed to parse cli\n");
		exit(EXIT_FAILURE);
	}

	if (__parse_options(&cli_builder, argc, argv) == -1) {
		free_cli_builder(&cli_builder);
		exit(EXIT_FAILURE);
	}

	if (cli_builder.targets->size == 0) {
		fprintf(stderr, "Error: No target specified\n");
		free_cli_builder(&cli_builder);
		exit(EXIT_FAILURE);
	}

	return (__build_cli(&cli_builder));
}
