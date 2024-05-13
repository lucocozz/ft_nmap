#include "cli.h"

static void __default_handler(cli_t *cli, char *arg)
{
	UNUSED(cli);
	printf("arg=%s\n", arg);
}

static const cli_option_t	g_options[] = {
	{.short_flag = "-h", .long_flag = "--help",   .has_argument = false, .arg_handler = __default_handler},
	{.short_flag = "-f", .long_flag = "--file",   .has_argument = false, .arg_handler = __default_handler},
	{.short_flag = "-p", .long_flag = "--ports",  .has_argument = true,  .arg_handler = __default_handler},
	{.short_flag = "-t", .long_flag = "--thread", .has_argument = true,  .arg_handler = __default_handler},
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
		// TODO: Allow multiple targets (Bonus)
		if (start_with("-", argv[i]) == false) {
			cli->target = argv[i];
			continue ;
		}

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

	return (0);
}

cli_t parse_cli(int argc, char **argv)
{
	cli_t cli = INITIALIZE_CLI;

	if (argc == 1) {
		fprintf(stderr, "%s", PROGRAM_HELPER);
		exit(EXIT_FAILURE);
	}

	if (__parse_options(&cli, argc, argv) == -1)
		exit(EXIT_FAILURE);

	if (cli.target == NULL) {
		fprintf(stderr, "Error: No target specified\n");
		exit(EXIT_FAILURE);
	}

	return (cli);
}
