#pragma once

typedef enum
{
    false = 0,
    true = 1,
} bool;

// constants

#define SYS_socket 198
#define SYS_connect 203
#define SYS_sendto 206
#define SYS_recvfrom 207
#define SYS_close 57

#define AF_INET 2
#define SOCK_STREAM 1

// types for socket()

typedef int Socket;

// types for connect()

typedef struct
{
    unsigned short int family;
    char sa_data[14];
} SockAddr;

typedef struct
{
    unsigned short int family;
    unsigned short int port;
    unsigned int addr;
    unsigned char _padding[8];
} IpAddr;
