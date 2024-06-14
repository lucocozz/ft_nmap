#ifndef FT_NMAP_SCAN_H
#define FT_NMAP_SCAN_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>

typedef enum {
	SYN_SCAN  = 1 << 0,
	NULL_SCAN = 1 << 1,
	ACK_SCAN  = 1 << 2,
	FIN_SCAN  = 1 << 3,
	XMAS_SCAN = 1 << 4,
	UDP_SCAN  = 1 << 5,
} scan_type_e;

typedef struct {
	unsigned int scan_type;
	char *scan_name;
} scan_info_t;


typedef enum {
	CLOSED 		= 0,
	OPEN 		= 1 << 0,
	FILTERED 	= 1 << 1,
	UNFILTERED 	= 1 << 2,
} scan_status_e;

typedef struct {
	scan_status_e status;
	char *status_name;
} scan_status_t;

typedef struct port_scan {
	int				port;
	scan_status_e	status[6];
	// scan_status_e	syn_scan;
	// scan_status_e	null_scan;
	// scan_status_e	ack_scan;
	// scan_status_e	fin_scan;
	// scan_status_e	xmas_scan;
	// scan_status_e	udp_scan;
	bool 			is_open;
} port_scan_t;

typedef struct host_scan {
	bool 				is_up;
	char				*ip;
	char 				*hostname;
	port_scan_t			*ports;
	struct timeval 		start_time;
	struct timeval 		end_time;
} host_scan_t;

extern host_scan_t *hosts;

#endif // FT_NMAP_SCAN_H
