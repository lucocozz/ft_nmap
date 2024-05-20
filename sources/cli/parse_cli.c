#include "cli.h"

static const cli_option_t	g_options[] = {
	{.short_flag = "-h", .long_flag = "--help",   .has_argument = false, .arg_handler = arg_help_handler},
	{.short_flag = "-f", .long_flag = "--file",   .has_argument = true,  .arg_handler = arg_file_handler},
	{.short_flag = "-p", .long_flag = "--ports",  .has_argument = true,  .arg_handler = arg_ports_handler},
	{.short_flag = "-t", .long_flag = "--thread", .has_argument = true,  .arg_handler = arg_thread_handler},
};


static const cli_option_t	*__get_option(char *flag)
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

static int	__parse_options(cli_t *cli, int argc, char **argv)
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
			option->arg_handler(cli, argv[i]);
		}
		else if (rbt_insert(cli->targets, argv[i], RBT_COPY_DATA) == ENOMEM)
			return (-1);
	}
	return (0);
}

cli_t parse_cli(int argc, char **argv)
{
	cli_t cli = INITIALIZE_CLI;

	if (argc == 1) {
		fprintf(stderr, "%s", PROGRAM_HELPER);
		exit(EXIT_FAILURE);
	}

	cli.targets = rbt_new(RBT_STR);
	if (cli.targets == NULL) {
		fprintf(stderr, "Error: failed to parse cli\n");
		exit(EXIT_FAILURE);
	}

	if (__parse_options(&cli, argc, argv) == -1) {
		free_cli(&cli);
		exit(EXIT_FAILURE);
	}

	if (cli.targets->size == 0) {
		fprintf(stderr, "Error: No target specified\n");
		free_cli(&cli);
		exit(EXIT_FAILURE);
	}

	return (cli);
}
