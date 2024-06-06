#ifndef FT_NMAP_SCAN_H
#define FT_NMAP_SCAN_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>

typedef enum {
	SYN_SCAN  = 1 << 0,
	NULL_SCAN = 1 << 1,
	ACK_SCAN  = 1 << 2,
	FIN_SCAN  = 1 << 3,
	XMAS_SCAN = 1 << 4,
	UDP_SCAN  = 1 << 5,
} scan_type_e;

typedef enum {
	CLOSED 		= 0,
	OPEN 		= 1 << 0,
	FILTERED 	= 1 << 1,
	UNFILTERED 	= 1 << 2,
	UNKNOWN 	= 1 << 3
} scan_status_e;

typedef struct port_scan {
	int				port;
	scan_status_e	status[6];
} port_scan_t;

typedef struct host_scan {
	bool 				is_up;
	char				*ip;
	char 				*hostname;
	struct port_scan	*ports;
	struct timeval 		start_time;
	struct timeval 		end_time;
} host_scan_t;

extern host_scan_t *hosts;

#endif // FT_NMAP_SCAN_H
