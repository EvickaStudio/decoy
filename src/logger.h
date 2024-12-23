#pragma once

#include <stdio.h>

#define STATUS_SUCCESS (NTSTATUS)0x00000000L
#define OKAY(MSG, ...) printf("[+] " MSG "\n", ##__VA_ARGS__)
#define INFO(MSG, ...) printf("[*] " MSG "\n", ##__VA_ARGS__)
#define WARN(MSG, ...) fprintf(stderr, "[-] " MSG "\n", ##__VA_ARGS__)
#define PRINT_ERROR(FUNCTION_NAME, NTSTATUS_ERROR)                        \
    do                                                                    \
    {                                                                     \
        fprintf(stderr,                                                   \
                "[!] [" FUNCTION_NAME "] [%s:%d] failed, error: 0x%lx\n", \
                __FILE__, __LINE__, NTSTATUS_ERROR);                      \
    } while (0)
