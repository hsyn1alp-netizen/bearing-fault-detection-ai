#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include "logger.h"
#define LOG_FILE "/home/alp/Desktop/Rulman_System/Rulman_healt/rulman_logs.txt"
#define MAX_SANIYE (30 * 24 * 60 * 60)
void log_sonuc(double rms, double kurtosis, double p2p, double saglik) {
    struct stat attr; time_t simdi = time(NULL);
    if (stat(LOG_FILE, &attr) == 0) { if (difftime(simdi, attr.st_mtime) > MAX_SANIYE) remove(LOG_FILE); }
    FILE *f = fopen(LOG_FILE, "a"); if (f == NULL) return;
    char zaman_st[25]; strftime(zaman_st, 25, "%Y-%m-%d %H:%M:%S", localtime(&simdi));
    fprintf(f, "[%s] | RMS: %.6f | Kurt: %.6f | P2P: %.6f | Saglik: %.2f\n", zaman_st, rms, kurtosis, p2p, saglik);
    fclose(f);
}
