#ifndef CONFIG_H
#define CONFIG_H

/**
 * @file config.h
 * @brief Configuration constants and settings for the Decoy application.
 */

// Version information
#define DECOY_VERSION_MAJOR 0
#define DECOY_VERSION_MINOR 1
#define DECOY_VERSION_PATCH 0
#define DECOY_VERSION_STRING "0.1.0"

// Application limits
#define MAX_PROCESSES 64
#define MAX_PATH_SAFE 260  // Windows MAX_PATH with safety margin

// Decoy identifier used in version information
#define DECOY_IDENTIFIER_UUID "0193b58d-cf59-703c-afda-a8c62c43f6b0"

// Directory and file names
#define PROCESSES_DIR "processes"
#define DUMMY_EXECUTABLE "dummy.exe"

// Process management timeouts (in milliseconds)
#define PROCESS_WAIT_TIMEOUT 2000
#define PROCESS_SLEEP_INTERVAL 1000

#endif // CONFIG_H