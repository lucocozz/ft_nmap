# ft_nmap

## Scan Types

### SYN Scan
#### Description
The SYN Scan sends a TCP SYN packet to determine the state of ports.  
| State    | Response |
|----------|----------|  
| Open     | TCP SYN/ACK response |
| Closed   | TCP RST response |
| Filtered | ICMP error message (type 3, code 1, 2, 3, 9, 10, or 13) or nothing |

#### Pros
- **Fast and efficient:** Quickly identifies the state of ports.
- **Less intrusive:** Does not complete the TCP handshake, making it a stealth scan.

#### Cons
- **Detectable:** Can be detected by some firewalls and intrusion detection systems (IDS).

### UDP Scan
#### Description
The UDP Scan sends a UDP packet to identify active UDP services.
| State    | Response |
|----------|----------|  
| Open     | Receives a UDP packet or nothing |
| Closed   | Receives an ICMP error message (type 3, code 3) |
| Filtered | Receives an ICMP error message (type 3, code 1, 2, 9, 10, or 13) or nothing |

#### Pros
- **Useful for scanning UDP services:** Can identify active UDP services that are often overlooked.
- **Firewall evasion:** Can bypass some firewalls.

#### Cons
- **Slower:** Generally slower than TCP scans.
- **False positives:** Many false positives if no response packet is received.

### NULL, FIN, XMAS Scan
#### Description
These scans send TCP packets with specific flag configurations to bypass certain filtering systems.
| State    | Response |
|----------|----------|  
| Open     | Receives nothing |
| Closed   | Receives a TCP RST packet |
| Filtered | Receives an ICMP error message (type 3, code 1, 2, 9, 10, or 13) or nothing |

#### Pros
- **Firewall evasion:** Can bypass some firewalls and packet filters.
- **Stealthy:** Less likely to be detected by IDS.

#### Cons
- **Incompatibility:** Does not work on Windows systems.
- **Speed:** May be slower due to the need to handle responses.

### ACK Scan
#### Description
The ACK Scan sends a TCP ACK packet to determine if ports are filtered.
| State    | Response |
|----------|----------|  
| Unfiltered | Receives a TCP RST packet |
| Filtered   | Receives an ICMP error message (type 3, code 1, 2, 9, 10, or 13) or nothing |

#### Pros
- **Firewall rule identification:** Useful for determining firewall rules.
- **Filter detection:** Helps identify if ports are filtered by stateful rules.

#### Cons
- **Limited information:** Does not determine if a port is open or closed, only if it is filtered.
- **Noisy:** Can be noisy and detected by IDS.