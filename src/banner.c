#include <stdio.h>
#include "banner.h"
#include "utils.h"

/**
 * @file banner.c
 * @brief Printing banner and menu interfaces.
 *
 * Contains functions to print the initial ASCII banner and the available commands menu.
 */

/**
 * @brief Prints the initial program banner and welcome message.
 */
void printBanner(void)
{
    qprintf("\x1b[35m");
    qprintf("     __                 \n");
    qprintf(" ___/ /__ _______  __ __\n");
    qprintf("/ _  / -_) __/ _ \\/ // /\n");
    qprintf("\\_,_/\\__/\\__/\\___/\\_, / ");
    qprintf("\x1b[0m");
    qprintf("v0.1.0\n");
    qprintf("\x1b[35m");
    qprintf("                 /___/  \n");
    qprintf("\x1b[0m\n");
    qprintf("Welcome to the Decoy Manager!\n");
    qprintf("--------------------------------\n");
    qprintf("This tool launches multiple dummy processes\n");
    qprintf("as known analysis/debugger tool names.\n");
    qprintf("Use it to deter simple malware checks.\n\n");
    qprintf("Each process uses minimal resources.\n\n");
    fflush(stdout);
}

/**
 * @brief Prints the command menu for the interactive mode.
 */
void printMenu(void)
{
    qprintf("Available Commands:\n");
    qprintf("[S] Start all processes\n");
    qprintf("[T] Terminate all processes\n");
    qprintf("[R] Restart all processes\n");
    qprintf("[Q] Quit\n");
    qprintf("--------------------------------\n");
    qprintf("Enter a command: ");
}
