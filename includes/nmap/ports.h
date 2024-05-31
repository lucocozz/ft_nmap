#ifndef FT_NMAP_PORTS_H
#define FT_NMAP_PORTS_H

int		init_port_names(void);
char	*get_port_name(int port);
void	free_port_names(void);

#endif
