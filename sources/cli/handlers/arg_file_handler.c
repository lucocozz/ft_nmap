#include "cli.h"


static void	__insert_line(cli_builder_t *cli_builder, char *line)
{
	char **args = split(line, " ,;");
	if (args == NULL)
		return;

	for (int i = 0; args[i] != NULL; ++i)
		rbt_insert(cli_builder->targets, args[i]);
	free_split(args);
}


static void	__read_file(cli_builder_t *cli_builder, FILE *file)
{
	size_t	len = 0;
	char	*line = NULL;
	ssize_t	read;
	
	while ((read = getline(&line, &len, file)) != -1)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		__insert_line(cli_builder, line);	
	}
	if (line != NULL)
		free(line);
}

void	arg_file_handler(cli_builder_t *cli_builder, char *arg)
{
	FILE *file = fopen(arg, "r");

	if (file == NULL) {
		fprintf(stderr, "Error: cannot open file '%s'\n", arg);
		free_cli_builder(cli_builder);
		exit(EXIT_FAILURE);
	}

	__read_file(cli_builder, file);
	fclose(file);
}
