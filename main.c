#include "network.h"
#include "operations.h"

#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#include <stdio.h>
#else
#define printf(...)
#endif

#define RESPONSE_SIZE 1024

// Usage: grab <HOST_NAME> <IP-ADDRESS> <PORT>
int main(int argc, char *argv[])
{
    if (argc != 4)
        return 1;

    const char *host_name = argv[1];
    const char *ip_address = argv[2];
    unsigned short port = ascii_to_number(argv[3]);

    char http_request[128];

    copy_str("GET / HTTP/1.1\r\nHost: ", http_request);
    copy_str(host_name, http_request + sizeof("GET / HTTP/1.1\r\nHost: ") - 1);
    copy_str("\r\nConnection: close\r\nUser-Agent: curl/7.68.0\r\n\r\n",
             http_request + str_len("GET / HTTP/1.1\r\nHost: ") + str_len(host_name));

    printf("\nCreating socket...\n");
    Socket sock = socket();
    if (sock == -1)
        return 2;
    printf("Socket created (socket number: %d)\n", sock);

    printf("\nConnecting to '%s:%d'\n", ip_address, port);
    if (!connect(sock, ip_address, port))
        return 3;
    printf("Connected\n");

    printf("\nSending data...\n");
    if (!send(sock, http_request))
        return 4;
    printf("Data sent\n");

    printf("\nResponse:\n");
    char response[RESPONSE_SIZE];
    long int received_response_len;
    do
    {
        received_response_len = recv(sock, response, RESPONSE_SIZE - 1);
        if (received_response_len == -1)
        {
            close(sock);
            return 5;
        }
        response[received_response_len] = '\0';
        printf("%s", response);
    } while (received_response_len > 0);
    printf("\n");

    printf("\nClosing socket...\n");
    close(sock);
    printf("Socket closed\n");

    return 0;
}
