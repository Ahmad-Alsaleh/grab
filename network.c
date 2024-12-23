#include "network.h"
#include "operations.h"
#include "types.h"
#include <stdio.h>

Socket socket()
{
    return syscall(SYS_socket, AF_INET, SOCK_STREAM, 0);
}

bool connect(Socket socket, const char *addr, unsigned short int port)
{
    IpAddr ip_addr;
    ip_addr.family = AF_INET;
    ip_addr.addr = parse_ip_address(addr);
    ip_addr.port = parse_port(port);

    return syscall(SYS_connect, socket, (SockAddr *)&ip_addr, (unsigned int)sizeof(ip_addr)) != -1;
}

bool send(Socket socket, const char *data)
{
    return syscall(SYS_sendto, socket, data, str_len(data), 0, NULL, 0) != -1;
}

long int recv(Socket socket, char *response, unsigned long int responze_size)
{
    return syscall(SYS_recvfrom, socket, response, responze_size, 0, NULL, NULL);
}

bool close(Socket socket)
{
    return syscall(SYS_close) != -1;
}
