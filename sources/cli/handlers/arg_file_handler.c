#include "cli.h"

void	arg_file_handler(cli_builder_t *cli_builder, char *arg)
{
	FILE *file = fopen(arg, "r");

	if (file == NULL) {
		fprintf(stderr, "Error: cannot open file '%s'\n", arg);
		free_cli_builder(cli_builder);
		exit(EXIT_FAILURE);
	}

	size_t	len = 0;
	char	*line = NULL;
	ssize_t	read;
	
	while ((read = getline(&line, &len, file)) != -1)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		rbt_insert(cli_builder->targets, line);
	}
	if (line != NULL)
		free(line);
	fclose(file);
}
