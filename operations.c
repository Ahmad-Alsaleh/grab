#include "types.h"

unsigned int parse_ip_address(const char *addr)
{
    unsigned int ip_address = 0;
    unsigned short octet = 0;
    unsigned char dots_n = 0;

    for (const char *chr = addr; *chr; ++chr)
    {
        if (*chr >= '0' && *chr <= '9')
        {
            octet = octet * 10 + (*chr - '0');
            if (octet > 255)
                return -1; // invalid octet
        }
        else if (*chr == '.')
        {
            if (++dots_n > 3)
                return -1; // to many dots
            ip_address |= octet << 8 * (dots_n - 1);
            octet = 0;
        }
        else
            return -1; // invalid charecter
    }
    if (dots_n < 3)
        return -1; // too little dots

    ip_address |= octet << 8 * dots_n;

    return ip_address;
}

bool _is_big_endian()
{
    unsigned short two_bytes = 0x0001;
    char *first_byte = (char *)&two_bytes;
    return *first_byte == 0x00;
}

unsigned short int parse_port(unsigned short int port)
{
    if (_is_big_endian())
        return port;
    return (port >> 8) | (port << 8);
}

unsigned long str_len(const char *str)
{
    for (unsigned long int i = 0; i < (unsigned long)-2; ++i)
        if (str[i] == '\0')
            return i;
    return 0;
}

void copy_str(const char *from, char *to)
{
    for (const char *p = from; *p; ++p)
        *to++ = *p;
    *to = '\0';
}

unsigned long int ascii_to_number(const char *str)
{
    unsigned long int number = 0;
    for (const char *p = str; *p; ++p)
        number = number * 10 + (*p - '0');
    return number;
}