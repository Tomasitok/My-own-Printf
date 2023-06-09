#include <stdio.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"

int _printf(const char *format, ...)
{
    va_list args;
    int count = 0;
    char buffer[1024];
    int pos = 0;

    va_start(args, format);

    while (*format != '\0')
    {
        if (*format == '%')
        {
            format++;
            if (*format == ' ')
            {
                int num = va_arg(args, int);
                if (num < 0)
                {
                    buffer[pos] = '-';
                    pos++;
                    count++;
                    num = -num;
                    int temp = num;
                    int len = 0;

                    while (temp != 0)
                    {
                        temp /= 10;
                        len++;
                    }

                    int digits[len];
                    int i = len - 1;

                    while (num != 0)
                    {
                        digits[i] = num % 10;
                        num /= 10;
                        i--;
                    }
                    for (i = 0; i < len; i++)
                    {
                        buffer[pos] = digits[i] + '0';
                        pos++;
                        count++;
                    }
                }
                else
                {
                    buffer[pos] = ' ';
                    pos++;
                    count++;
                    int temp = num;
                    int len = 0;

                    while (temp != 0)
                    {
                        temp /= 10;
                        len++;
                    }

                    int digits[len];
                    int i = len - 1;

                    while (num != 0)
                    {
                        digits[i] = num % 10;
                        num /= 10;
                        i--;
                    }
                    for (i = 0; i < len; i++)
                    {
                        buffer[pos] = digits[i] + '0';
                        pos++;
                        count++;
                    }
                }
                format++;
                continue;
            }

            switch (*format)
            {
            case 'c':
            {
                buffer[pos] = (char)va_arg(args, int);
                pos++;
                count++;
                break;
            }

            case 's':
            {
                char *str = va_arg(args, char *);
                int i = 0;
                while (str[i] != '\0' && pos < 1023)
                {
                    buffer[pos] = str[i];
                    pos++;
                    count++;
                    i++;
                }
            }
            break;

            case '%':
            {
                buffer[pos] = '%';
                pos++;
                count++;
                break;
            }
            case 'd':
            {
                int num = va_arg(args, int);
                int temp = num;
                int len = 0;

                if (num == 0)
                {
                    buffer[pos] = '0';
                    pos++;
                    count++;
                    break;
                }

                while (temp != 0)
                {
                    temp /= 10;
                    len++;
                }

                if (num < 0)
                {
                    buffer[pos] = '-';
                    pos++;
                    count++;
                    num = -num;
                }

                int digits[len];
                int i = len - 1;

                while (num != 0)
                {
                    digits[i] = num % 10;
                    num /= 10;
                    i--;
                }
                for (i = 0; i < len; i++)
                {
                    buffer[pos] = digits[i] + '0';
                    pos++;
                    count++;
                }
                break;
            }
            case 'i':
            {
                unsigned int num = va_arg(args, unsigned int);
                int temp = num;
                int len = 0;

                if (num == 0)
                {
                    buffer[pos] = '0';
                    pos++;
                    count++;
                    break;
                }

                while (temp != 0)
                {
                    temp /= 10;
                    len++;
                }

                int digits[len];
                int i = len - 1;

                while (num != 0)
                {
                    digits[i] = num % 10;
                    num /= 10;
                    i--;
                }
                for (i = 0; i < len; i++)
                {
                    buffer[pos] = digits[i] + '0';
                    pos++;
                    count++;
                }
                break;
            }
            case 'b':
            {
                int num = va_arg(args, int);
                int copy_num = num;
                int c = 0;

                while (copy_num > 0)
                {
                    copy_num = copy_num / 2;
                    c++;
                }

                int *binary = malloc(c * sizeof(int));
                if (binary == NULL)
                {
                    return -1;
                }
                for (int i = c - 1; i >= 0; i--)
                {
                    binary[i] = num % 2;
                    num /= 2;
                }
                for (int i = 0; i < c; i++)
                {
                    buffer[pos] = binary[i] + '0';
                    pos++;
                    count++;
                }
                free(binary);
                break;
            }
            case 'u':
            {
                int number = va_arg(args, int);
                if (number < 0)
                {
                    return -1;
                }
                else if (number == 0)
                {
                    buffer[pos] = '0';
                    pos++;
                    count++;
                }
                else
                {
                    unsigned int temp = number;
                    int len = 0;
                    while (temp != 0)
                    {
                        temp /= 10;
                        len++;
                    }
                    int digits[len];
                    int i = len - 1;
                    while (number != 0)
                    {
                        digits[i] = number % 10;
                        number /= 10;
                        i--;
                    }
                    for (i = 0; i < len; i++)
                    {
                        buffer[pos] = digits[i] + '0';
                        pos++;
                        count++;
                    }
                }
                break;
            }
            case 'o':
            {
                unsigned int number = va_arg(args, unsigned int);
                if (number < 0)
                {
                    return -1;
                }
                else if (number == 0)
                {
                    buffer[pos] = '0';
                    pos++;
                    count++;
                }
                else
                {
                    unsigned int temp = number;
                    int len = 0;

                    while (temp != 0)
                    {
                        temp /= 8;
                        len++;
                    }

                    int digits[len];
                    int i = len - 1;

                    while (number != 0)
                    {
                        digits[i] = number % 8;
                        number /= 8;
                        i--;
                    }

                    for (i = 0; i < len; i++)
                    {
                        buffer[pos] = digits[i] + '0';
                        pos++;
                        count++;
                    }
                }
                break;
            }
            case 'x':
            {
                unsigned int number = va_arg(args, unsigned int);
                if (number < 0)
                {
                    return -1;
                }
                else if (number == 0)
                {
                    buffer[pos] = '0';
                    pos++;
                    count++;
                }
                else
                {
                    unsigned int temp = number;
                    int len = 0;

                    while (temp != 0)
                    {
                        temp /= 16;
                        len++;
                    }

                    char digits[len];
                    int i = len - 1;

                    while (number != 0)
                    {
                        int lon = number % 16;

                        if (lon < 10)
                        {
                            digits[i] = lon + '0';
                        }
                        else
                        {
                            digits[i] = lon - 10 + 'a';
                        }

                        number /= 16;
                        i--;
                    }

                    for (i = 0; i < len; i++)
                    {
                        buffer[pos] = (digits[i]);
                        pos++;
                        count++;
                    }
                }
                break;
            }
            case 'X':
            {
                unsigned int number = va_arg(args, unsigned int);
                if (number <= 1)
                {
                    buffer[pos] = '0';
                    pos++;
                    count++;
                }
                else if (number == 0)
                {
                    buffer[pos] = '0';
                    pos++;
                    count++;
                }
                else
                {
                    unsigned int temp = number;
                    int len = 0;

                    while (temp != 0)
                    {
                        temp /= 16;
                        len++;
                    }

                    char digits[len];
                    int i = len - 1;

                    while (number != 0)
                    {
                        int lon = number % 16;

                        if (lon < 10)
                        {
                            digits[i] = lon + '0';
                        }
                        else
                        {
                            digits[i] = lon - 10 + 'A';
                        }

                        number /= 16;
                        i--;
                    }

                    for (i = 0; i < len; i++)
                    {
                        buffer[pos] = (digits[i]);
                        pos++;
                        count++;
                    }
                }
                break;
            }
            case 'p':
            {
                void *ptr = va_arg(args, void *);
                unsigned long address = (unsigned long)ptr;
                int len = sizeof(address) * 2;
                buffer[pos] = '0';
                buffer[pos + 1] = 'x';
                count += 2;
                pos += 2;

                for (int i = len - 1; i >= 0; i--)
                {
                    int digit = (address >> (i * 4)) & 0xF;
                    buffer[pos] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
                    count++;
                    pos++;
                }
                break;
            }
            case 'S':
            {
                char *str = va_arg(args, char *);
                for (int i = 0; str[i] != '\0'; i++)
                {
                    if (str[i] < 32 || str[i] >= 127)
                    {
                        buffer[pos] = '\\';
                        buffer[pos + 1] = 'x';
                        pos += 2;
                        unsigned int number = (unsigned int)str[i];

                        if (number <= 1)
                        {
                            buffer[pos] = '0';
                            pos++;
                            count++;
                        }

                        char digits[2];
                        digits[0] = (number >> 4) & 0xF;
                        digits[1] = number & 0xF;

                        for (int j = 0; j < 2; j++)
                        {
                            if (digits[j] < 10)
                            {
                                buffer[pos] = digits[j] + '0';
                            }
                            else
                            {
                                buffer[pos] = digits[j] - 10 + 'A';
                            }
                            pos++;
                            count++;
                        }
                    }
                    else
                    {
                        buffer[pos] = str[i];
                        pos++;
                        count++;
                    }
                }
                break;
            }
            case 'R':
            {
                char *str = va_arg(args, char *);
                int i = 0;

                while (str[i] != '\0' && pos < 1023)
                {
                    if (str[i] >= 'a' && str[i] <= 'z')
                    {
                        buffer[pos] = ((str[i] - 'a' + 13) % 26) + 'a';
                    }
                    else if (str[i] >= 'A' && str[i] <= 'Z')
                    {
                        buffer[pos] = ((str[i] - 'A' + 13) % 26) + 'A';
                    }
                    else
                    {
                        buffer[pos] = str[i];
                    }
                    pos++;
                    count++;
                    i++;
                }
                break;
            }
            case 'r':
            {
                char *str = va_arg(args, char *);
                int lon = 0;

                while (str[lon] != '\0')
                {
                    lon++;
                }

                for(int i = lon - 1; i >= 0; i--)
                {
                    buffer[pos] = str[i];
                    pos++;
                    count++;
                }
                break;
            }

            default:
            {
                buffer[pos] = '%';
                pos++;
                count++;
                break;
            }
            }
        }
        else
        {
            buffer[pos] = *format;
            pos++;
            count++;
        }
        format++;
    }

    if (pos >= 1023 || *format == '\0')
    {
        buffer[pos] = '\0';

        for (int i = 0; i < pos; i++)
        {
            putchar(buffer[i]);
        }
    }
    va_end(args);
    return count;
}
