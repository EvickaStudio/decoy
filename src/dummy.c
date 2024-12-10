#include <windows.h>

/**
 * @file dummy.c
 * @brief The dummy program that simulates a tool process.
 *
 * This program does essentially nothing but sleep, acting as a decoy. It
 * will never stop until terminated externally.
 */

int main(void)
{
    // Infinite loop, sleeping to simulate a running process
    for (;;)
    {
        Sleep(1000);
    }
    return 0;
}
