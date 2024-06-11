# ft_nmap

## Scan Types

### SYN Scan
#### Description
The SYN Scan sends a TCP SYN packet to determine the state of ports.
- **Open**: receives a TCP SYN/ACK packet
- **Closed**: receives a TCP RST packet
- **Filtered**: receives an ICMP error message (type 3, code 1, 2, 3, 9, 10, or 13) or nothing

#### Pros
- Fast and efficient
- Less intrusive as it does not complete the TCP handshake (stealth scan)

#### Cons
- Can be detected by some firewalls and intrusion detection systems (IDS)

### UDP Scan
#### Description
The UDP Scan sends a UDP packet to identify active UDP services.
- **Open**: receives a UDP packet or nothing
- **Closed**: receives an ICMP error message (type 3, code 3)
- **Filtered**: receives an ICMP error message (type 3, code 1, 2, 9, 10, or 13) or nothing

#### Pros
- Useful for scanning UDP services
- Can bypass some firewalls

#### Cons
- Slower than TCP scans
- Many false positives if no response packet is received

### NULL, FIN, XMAS Scan
#### Description
These scans send TCP packets with specific flag configurations to bypass certain filtering systems.
- **Open**: receives nothing
- **Closed**: receives a TCP RST packet
- **Filtered**: receives an ICMP error message (type 3, code 1, 2, 9, 10, or 13) or nothing

#### Pros
- Can bypass some firewalls and packet filters
- Less likely to be detected by IDS

#### Cons
- Does not work on Windows systems
- May be slower due to the need to handle responses

### ACK Scan
#### Description
The ACK Scan sends a TCP ACK packet to determine if ports are filtered.
- **Unfiltered**: receives a TCP RST packet
- **Filtered**: receives an ICMP error message (type 3, code 1, 2, 9, 10, or 13) or nothing

#### Pros
- Useful for determining firewall rules
- Helps identify if ports are filtered by stateful rules

#### Cons
- Does not determine if a port is open or closed, only if it is filtered
- Can be noisy and detected by IDS
