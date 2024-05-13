#ifndef CLI_H
#define CLI_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <toolbox/string.h>
#include <toolbox/def.h>

#define PROGRAM_HELPER 																\
"Usage: ft_nmap [OPTIONS] <target>\n"												\
" -p, --ports <ports list>:   Ports to scan (eg: 1-10 or 1,2,3 or 1,5-15)\n"		\
" -t, --thread <num-threads>: Number of parallel threads to use (250 max)\n"		\
" -h, --help:\t\t     Display this help message\n"									\
" -f, --file:\t\t     `<target>` become the `./path/file` to use for the target\n"	\

typedef struct cli_s {
	char		*target;
	uint8_t		threads;
	uint16_t	*ports;
	bool		from_file;
} cli_t;

#define INITIALIZE_CLI	\
(cli_t){				\
	.target = NULL,		\
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
cli_t parse_cli(int argc, char **argv);

#endif
