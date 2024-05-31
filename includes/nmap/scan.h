#ifndef FT_NMAP_SCAN_H
#define FT_NMAP_SCAN_H


typedef enum {
	SYN_SCAN  = 1 << 0,
	NULL_SCAN = 1 << 1,
	ACK_SCAN  = 1 << 2,
	FIN_SCAN  = 1 << 3,
	XMAS_SCAN = 1 << 4,
	UDP_SCAN  = 1 << 5,
} scan_type_t;


#endif // FT_NMAP_SCAN_H
