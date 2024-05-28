#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <rbtree.h>

#define PORT_NAMES_PATH			"/tmp/ft_nmap_services/port-names.tsv"
#define UNKMOWN_PORT_NAME		"unknown"
#define DOMAIN_NAME_MAX_SIZE	254

RBTree_t *g_port_names = NULL;

static void	__insert_port_name(char *entry)
{
	int		port = 0;
	char	name[DOMAIN_NAME_MAX_SIZE] = {0};

	if (sscanf(entry, "%s\t%d", name, &port) == 2)
		rbt_insert(g_port_names, RBT_MAKE_PAIR(&port, name));
}

static void	__read_port_names(FILE *file)
{
	size_t	len = 0;
	char	*line = NULL;
	int		read;
	
	while ((read = getline(&line, &len, file)) != -1)
	{
		if (line[read - 1] == '\n')
			line[read - 1] = '\0';
		__insert_port_name(line);
	}
	if (line != NULL)
		free(line);
}

int	init_port_names(void)
{
	g_port_names = rbt_new(RBT_PIS);
	if (g_port_names == NULL) {
		fprintf(stderr, "Failed to create rbtree for port names\n");
		return (-1);
	}
	
	FILE *file = fopen(PORT_NAMES_PATH, "r");
	if (file == NULL) {
		rbt_destroy(g_port_names);
		fprintf(stderr, "Failed to open " PORT_NAMES_PATH "\n");
		return (-1);
	}

	__read_port_names(file);
	fclose(file);
	return (0);
}

const char *get_port_name(int port)
{
	RBT_Iter_t	*it = rbt_find(g_port_names, RBT_MAKE_PAIR(&port, NULL));
	if (it == NULL)
		return (UNKMOWN_PORT_NAME);

	rbt_pair_t	*pair = it->data;
	return (pair->value);
}


void	free_port_names(void)
{
	rbt_destroy(g_port_names);
}
