#pragma once

#include "types.h"

Socket socket(void);
bool connect(Socket socket, const char *addr, unsigned short int port);
bool send(Socket socket, const char *data);
long int recv(Socket socket, char *response, unsigned long int responze_size);
bool close(Socket socket);

long syscall(long number, ...);
