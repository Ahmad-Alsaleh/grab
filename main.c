#include "network.h"

#define ENABLE_DEBUG

#ifdef ENABLE_DEBUG
#include <stdio.h>
#else
#define printf(...)
#endif

#define IP_ADDR "142.250.201.142"
#define HOST_NAME "www.google.com"
#define PORT 80
#define RESPONSE_SIZE 1024

int main()
{
    const char *http_request = "GET / HTTP/1.1\r\n"
                               "Host: " HOST_NAME "\r\n"
                               "Connection: close\r\n"
                               "User-Agent: curl/7.68.0\r\n\r\n";

    printf("\nCreating socket...\n");
    Socket sock = socket();
    if (sock == -1)
        return 1;
    printf("Socket created (socket number: %d)\n", sock);

    printf("\nConnecting to '%s:%d'\n", IP_ADDR, PORT);
    if (!connect(sock, IP_ADDR, PORT))
        return 2;
    printf("Connected\n");

    printf("\nSending data...\n");
    if (!send(sock, http_request))
        return 3;
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
            return 4;
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
