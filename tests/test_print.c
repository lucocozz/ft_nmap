#include "scan.h"


/*
 * These will be the structure for the final code
*/
host_scan_t *hosts = NULL;

scan_type_e scans = SYN_SCAN | NULL_SCAN | ACK_SCAN | FIN_SCAN | XMAS_SCAN | UDP_SCAN;

scan_info_t scan_info[] = {
	{SYN_SCAN, "SYN"},
	{NULL_SCAN, "NULL"},
	{ACK_SCAN, "ACK"},
	{FIN_SCAN, "FIN"},
	{XMAS_SCAN, "XMAS"},
	{UDP_SCAN, "UDP"},
	{0, NULL}
};

scan_status_t scan_status[] = {
	{OPEN, "OPEN"},
	{FILTERED, "FILTERED"},
	{UNFILTERED, "UNFILTERED"},
	{0, NULL}
};

/*
 * These are only for testing purposes
*/

char fake_hostname[10][20] = {
	"localhost",
	"searchsite",
	"socialmedia",
	"newsportal",
	"ecommerce",
	"streamingservice",
	"emailprovider",
	"cloudservice",
	"dataplatform",
	"devtools"
};

char fake_ip[10][16] = {
	"192.168.1.1",
	"172.16.2.2",
	"10.0.3.3",
	"192.168.4.4",
	"172.16.5.5",
	"10.0.6.6",
	"192.168.7.7",
	"172.16.8.8",
	"10.0.9.9",
	"192.168.10.10"
};

int fake_ports_5[5] = {80, 443, 8080, 22, 21};
int fake_ports_10[10] = {80, 443, 8080, 22, 21, 25, 110, 143, 3306, 5432};
int fake_ports_20[20] = {80, 443, 8080, 22, 21, 25, 110, 143, 3306, 5432, 8000, 8081, 8082, 8083, 8084, 8085, 8086, 8087, 8088, 8089};

void create_fake_ports_scan(port_scan_t *port_scan, scan_type_e scan_type) {
	if (scan_type & SYN_SCAN) {
		port_scan->status[0] = OPEN;
		port_scan->is_open = true;
	}
	if (scan_type & NULL_SCAN)
		port_scan->status[1] = CLOSED;
	if (scan_type & ACK_SCAN)
		port_scan->status[2] = FILTERED;
	if (scan_type & FIN_SCAN)
		port_scan->status[3] = UNFILTERED;
	if (scan_type & XMAS_SCAN)
		port_scan->status[4] = OPEN|UNFILTERED;
	if (scan_type & UDP_SCAN)
		port_scan->status[5] = OPEN|FILTERED;
}

host_scan_t create_fake_host_scan(char *ip, char *hostname, int nb_ports, int *fake_ports) {
	host_scan_t *host = malloc(sizeof(host_scan_t));
	host->is_up = true;
	host->ip = strdup(ip);
	host->hostname = strdup(hostname);
	host->ports = malloc(sizeof(port_scan_t) * nb_ports);
	gettimeofday(&host->start_time, NULL);
	for (int i = 0; i < nb_ports; i++) {
		host->ports[i].port = fake_ports[i];
		create_fake_ports_scan(&host->ports[i], scans);
	}
	gettimeofday(&host->end_time, NULL);
	return *host;
}

host_scan_t create_unreachable_host_scan(char *ip, char *hostname, int nb_ports) {
	host_scan_t *host = malloc(sizeof(host_scan_t));
	host->is_up = false;
	host->ip = strdup(ip);
	host->hostname = strdup(hostname);
	host->ports = NULL;
	return *host;
}

int *get_fake_ports(int nb_ports) {
	if (nb_ports == 5) {
		return fake_ports_5;
	} else if (nb_ports == 10) {
		return fake_ports_10;
	} else if (nb_ports == 20) {
		return fake_ports_20;
	}
}

void create_fake_hosts(int nb_fake_host, int nb_ports)
{
	int *fake_ports = get_fake_ports(nb_ports);

	hosts = malloc(sizeof(host_scan_t) * nb_fake_host);

	hosts[0] = create_unreachable_host_scan(fake_ip[0], fake_hostname[0], nb_ports);
	for (int i = 1; i < nb_fake_host; i++) {
		hosts[i] = create_fake_host_scan(fake_ip[i % 10], fake_hostname[i % 10], nb_ports, fake_ports);
	}
}

void print_scan_status(scan_status_e status) {
	bool first = true;
	if (status == 0) {
		printf("CLOSED");
		return;
	}
	for (int i = 0; scan_status[i].status; i++) {
		if (status & scan_status[i].status) {
			if (!first) {
				printf("|");
			}
			printf("%s", scan_status[i].status_name);
			first = false;
		}
	}
}

void print_open_ports_scan(port_scan_t *ports, scan_type_e scan_type) {
	printf("Open ports:\n");
	printf("Port\tService Name (if applicable)\tResults\tConclusion\n");
	printf("--------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 20; i++) {
		if (!(ports[i].is_open)) {
			break;
		}
		printf("%d\tUnassigned\t", ports[i].port);
		for (int j = 0; scan_info[j].scan_type; ++j) {
			if (scan_type & scan_info[j].scan_type) {
				printf("%s(", scan_info[j].scan_name);
				print_scan_status(ports[i].status[j]);
				printf(") ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void print_closed_ports_scan(port_scan_t *ports, scan_type_e scan_type) {
	printf("Closed ports:\n");
	printf("Port\tService Name (if applicable)\tResults\tConclusion\n");
	printf("--------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < 20; i++) {
		if ((ports[i].is_open)) {
			break;
		}
		printf("%d\tUnassigned\t", ports[i].port);
		for (int j = 0; scan_info[j].scan_type; ++j) {
			if (scan_type & scan_info[j].scan_type) {
				printf("%s(", scan_info[j].scan_name);
				print_scan_status(ports[i].status[j]);
				printf(") ");
			}
		}
		printf("\n");
	}
	printf("\n");
}

void print_result(int nb_hosts, int nb_ports) {
	
	for (int i = 0; i < nb_hosts; i++) {
		if (hosts[i].is_up) {
			printf("IP address: %s (%s)\n", hosts[i].ip, hosts[i].hostname);
			print_open_ports_scan(hosts[i].ports, scans);
			print_closed_ports_scan(hosts[i].ports, scans);
		} else {
			printf("Host %s (%s) is unreachable\n", hosts[i].hostname, hosts[i].ip);
		}
		printf("\n");
	}
}

void print_configuration(int nb_hosts, int nb_ports) {
	printf("Scan configuration:\n");
	printf("Target IP-Address: ");
	for (int i = 0; i < nb_hosts; i++) {
		printf("%s", hosts[i].ip);
		if (i < nb_hosts - 1) {
			printf(", ");
		}
	}
	printf("\n");
	printf("No. of ports scanned: %d\n", nb_ports);
	printf("Scan to be performed: ");
	for (int i = 0; scan_info[i].scan_type; i++) {
		if (scans & scan_info[i].scan_type) {
			printf("%s ", scan_info[i].scan_name);
		}
	}
	printf("\n");
	printf("No. of threads: 1\n"); // for now TODO: implement threading
	printf("Scanning...\n");
}

int main() {
	int nb_hosts = 5;
	int nb_ports = 5;
	create_fake_hosts(nb_hosts, nb_ports);
	print_configuration(nb_hosts, nb_ports);
	printf("Scan took 0.000000 seconds\n");
	print_result(nb_hosts, nb_ports);
	return 0;
}
