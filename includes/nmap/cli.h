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
#include <rbtree.h>


#define DEFAULT_PORTS_PATH "/tmp/ft_nmap_services/default_ports.txt"

#define PROGRAM_HELPER 															\
"Usage: ft_nmap [OPTIONS] <target>\n"											\
"Options:\n"																	\
" -s,  --scan <scan type>:      Scan type (eg: SYN,NULL,XMAS,ACK,UDP)\n"	\
" -p,  --ports <ports list>:    Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n"	\
" -ep, --exclude-ports <ports>: Exclude ports from scan\n"						\
" -t,  --thread <num-threads>:  Number of parallel threads to use (250 max)\n"	\
" -f,  --file </path/file>:     Use file with targets\n"						\
" -h,  --help:                  Display this help message\n"					\


typedef struct cli_builder_s {
	RBTree_t	*targets;
	int			threads;
	RBTree_t	*ports;
	RBTree_t	*excluded_ports;
	uint8_t		scans;
} cli_builder_t;

#define INITIALIZE_CLI_BUILDER	\
(cli_builder_t){				\
	.targets = NULL,			\
	.threads = 0,				\
	.ports = NULL,				\
	.excluded_ports = NULL,		\
	.scans = 0,					\
}

typedef struct cli_s {
	char	**targets;
	int		threads;
	int		*ports;
	size_t	ports_size;
	uint8_t	scans;
} cli_t;

#define INITIALIZE_CLI	\
(cli_t){				\
	.targets = NULL,	\
	.threads = 0,		\
	.ports = NULL,		\
	.ports_size = 0,	\
	.scans = 0,			\
}


typedef void (*cli_arg_handler_t)(cli_builder_t*, char*);

typedef struct cli_option_s {
	char				*short_flag;
	char				*long_flag;
	bool				has_argument;
	cli_arg_handler_t	arg_handler;
} cli_option_t;




/*	CLI	*/
cli_t	parse_cli(int argc, char **argv);
void	free_cli(cli_t *cli);
void	free_cli_builder(cli_builder_t *cli_builder);


/* CLI/HANDLERS */
void	arg_file_handler(cli_builder_t *cli_builder, char *arg);
void	arg_ports_handler(cli_builder_t *cli_builder, char *arg);
void	arg_exclude_ports_handler(cli_builder_t *cli_builder, char *arg);
void	get_default_ports(cli_builder_t *cli_builder);
void	arg_help_handler(cli_builder_t *cli_builder, char *arg);
void	arg_thread_handler(cli_builder_t *cli_builder, char *arg);
void	arg_scan_handler(cli_builder_t *cli_builder, char *arg);

static inline void arg_default_handler(cli_builder_t *cli_builder, char *arg)
{
	UNUSED(cli_builder);
	printf("arg=%s\n", arg);
}

#endif	// CLI_H
