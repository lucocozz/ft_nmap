#include "cli.h"

void	free_targets(target_list_t **targets)
{
	target_list_t *current = *targets;

	while (current != NULL)
	{
		target_list_t *next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	*targets = NULL;
}

target_list_t	*target_new(char *name)
{
	target_list_t *new = malloc(sizeof(target_list_t) * 1);
	if (new == NULL)
		return (NULL);

	new->name = strdup(name);
	if (new->name == NULL) {
		free(new);
		return (NULL);
	}
	new->next = NULL;

	return (new);
}

target_list_t	*target_last(target_list_t *targets)
{
	target_list_t *current = targets;

	if (current == NULL)
		return (NULL);

	while (current->next != NULL)
		current = current->next;
	return (current);
}

target_list_t	*target_push_back_new(target_list_t **targets, char *name)
{
	target_list_t *new = target_new(name);

	if (new == NULL)
		return (NULL);
	
	if (*targets == NULL) {
		*targets = new;
		return (new);
	}

	target_list_t *last = target_last(*targets);
	last->next = new;
	return (new);
}

target_list_t	*target_push_front_new(target_list_t **targets, char *name)
{
	target_list_t *new = target_new(name);

	if (new == NULL)
		return (NULL);

	new->next = *targets;
	*targets = new;
	return (new);
}


void	print_targets(target_list_t *targets)
{
	target_list_t *current = targets;

	while (current != NULL)
	{
		printf("target: %s\n", current->name);
		current = current->next;
	}
}
