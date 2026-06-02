#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

// Log dosyasının yolu
#define LOG_FILE_PATH "/home/alp/Desktop/Rulman_System/rulman_env/log.txt"
#define MAX_LOG_DAYS 30

// Fonksiyon prototipleri
void log_result(const char* label, float confidence);
void check_and_clean_logs();

#endif
