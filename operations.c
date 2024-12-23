#include "types.h"

void _get_octec_lengths(const char *addr, unsigned char octec_lengths[4])
{
    unsigned char octec_start = 0;
    unsigned char octet_i = 0;
    unsigned char char_i;
    for (char_i = 0; addr[char_i] != '\0'; ++char_i)
    {
        if (addr[char_i] == '.')
        {
            octec_lengths[octet_i++] = char_i - octec_start;
            octec_start = char_i + 1;
        }
    }
    octec_lengths[3] = char_i - octec_start;
}

void _get_octecs(const char *addr, unsigned char octecs[4])
{
    unsigned char octec_lengths[4];
    _get_octec_lengths(addr, octec_lengths);
    unsigned char digit_start = 0;
    for (unsigned char octec_i = 0; octec_i < 4; ++octec_i)
    {
        unsigned char octec_length = octec_lengths[octec_i];
        unsigned char multiplier = octec_length == 3 ? 100 : octec_length == 2 ? 10
                                                                               : 1;
        octecs[octec_i] = 0;
        for (unsigned char digit_i = digit_start; digit_i < digit_start + octec_length; ++digit_i)
        {
            unsigned char digit = addr[digit_i] - '0';
            octecs[octec_i] += digit * multiplier;
            multiplier /= 10;
        }
        digit_start += octec_lengths[octec_i] + 1;
    }
}

unsigned int parse_ip_address(const char *addr)
{
    unsigned char octecs[4];
    _get_octecs(addr, octecs);

    unsigned int ip_address = 0;
    for (unsigned char i = 0; i < 4; ++i)
        ip_address = (ip_address << 8) | octecs[3 - i];
    return ip_address;
}

bool _is_little_endian(unsigned short int number)
{
    unsigned short two_bytes = 0x0001;
    char *first_byte = (char *)&two_bytes;
    return *first_byte == 0x01;
}

unsigned short int parse_port(unsigned short int port)
{
    if (_is_little_endian(port))
        return (port >> 8) | (port << 8);
    return port;
}

unsigned long str_len(const char *str)
{
    for (unsigned long int i = 0; i < (unsigned long)-2; ++i)
        if (str[i] == '\0')
            return i;
    return 0;
}