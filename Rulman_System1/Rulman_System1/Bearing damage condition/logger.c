#include "logger.h"
#include <sys/stat.h>

void log_result(const char* label, float confidence) {
    // Önce eski kayıtları temizle
    check_and_clean_logs();

    FILE *file = fopen(LOG_FILE_PATH, "a");
    if (file == NULL) {
        perror("Log dosyasi acilamadi");
        return;
    }

    time_t rawtime;
    struct tm *timeinfo;
    char time_buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(time_buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    fprintf(file, "[%s] [C-LOGGER] [%s] Confidence: %%%.2f\n", time_buffer, label, confidence);
    fclose(file);
}

void check_and_clean_logs() {
    struct stat attr;
    if (stat(LOG_FILE_PATH, &attr) == 0) {
        time_t now = time(NULL);
        // 30 gün = 30 * 24 * 60 * 60 saniye
        double diff = difftime(now, attr.st_mtime);

        if (diff > (MAX_LOG_DAYS * 24 * 60 * 60)) {
            // 1 ayı geçtiyse dosyayı sil veya sıfırla
            remove(LOG_FILE_PATH); 
            // Veya sadece içini boşaltmak istersen: fclose(fopen(LOG_FILE_PATH, "w"));
        }
    }
}
