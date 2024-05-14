#ifndef CLI_H
#define CLI_H

#define _GNU_SOURCE

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <toolbox/string.h>
#include <toolbox/def.h>

#define PROGRAM_HELPER 															\
"Usage: ft_nmap [OPTIONS] <target>\n"											\
" -p, --ports <ports list>:   Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n"	\
" -t, --thread <num-threads>: Number of parallel threads to use (250 max)\n"	\
" -h, --help:                 Display this help message\n"						\
" -f, --file <path/file>:     Use file with targets\n"							\

typedef struct target_list_s {
	char					*name;
	struct target_list_s	*next;
} target_list_t;

typedef struct cli_s {
	target_list_t	*targets;
	int				threads;
	int				*ports;
} cli_t;

#define INITIALIZE_CLI	\
(cli_t){				\
	.targets = NULL,	\
	.threads = 0,		\
	.ports = NULL,		\
};


typedef void (*cli_arg_handler_t)(cli_t*, char*);

typedef struct cli_option_s {
	char				*short_flag;
	char				*long_flag;
	bool				has_argument;
	cli_arg_handler_t	arg_handler;
} cli_option_t;




/*	CLI	*/
cli_t	parse_cli(int argc, char **argv);
void	free_cli(cli_t *cli);

/* CLI/TARGET */
void			targets_from_file(cli_t *cli);
void			free_targets(target_list_t **targets);
target_list_t	*target_push_back_new(target_list_t **targets, char *name);
target_list_t	*target_push_front_new(target_list_t **targets, char *name);
target_list_t	*target_new(char *name);
void			print_targets(target_list_t *targets);

/* CLI/HANDLERS */
void	arg_file_handler(cli_t *cli, char *arg);
void	arg_ports_handler(cli_t *cli, char *arg);
void	arg_help_handler(cli_t *cli, char *arg);
void	arg_thread_handler(cli_t *cli, char *arg);

static inline void arg_default_handler(cli_t *cli, char *arg)
{
	UNUSED(cli);
	printf("arg=%s\n", arg);
}

#endif	// CLI_H
