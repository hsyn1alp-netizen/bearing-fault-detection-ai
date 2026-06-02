#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <math.h>
#include <string.h>
#include "myNeuralNetworkFunction.h"
#include "myNeuralNetworkFunction_initialize.h"
#include "myNeuralNetworkFunction_terminate.h"
#include "logger.h"

#define MAX_LINES 10000

int main() {
    setlocale(LC_ALL, "");
    myNeuralNetworkFunction_initialize();

    double input_data[1024] = {0.0};
    double output_results[10];
    double all_data[MAX_LINES];
    int total_count = 0;
    char line[512]; 

    const char *ariza_aciklamalari[] = {
        "Normal: Sistem saglikli calisiyor.",
        "Bilya Arizasi (Hafif)", "Bilya Arizasi (Orta)", "Bilya Arizasi (Agir)",
        "Ic Bilezik Arizasi (Hafif)", "Ic Bilezik Arizasi (Orta)", "Ic Bilezik Arizasi (Agir)",
        "Dis Bilezik Arizasi (Hafif)", "Dis Bilezik Arizasi (Orta)", "Dis Bilezik Arizasi (Agir)"
    };

    // VERİ YOLU BURADA GÜNCELLENDİ
    FILE *file = fopen("/home/alp/Desktop/Rulman_System/titresimverisi.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "HATA: titresimverisi.txt bulunamadi!\n");
        return 1;
    }

    while (total_count < MAX_LINES && fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ", \t\r\n");
        if (token != NULL) {
            all_data[total_count] = atof(token);
            total_count++;
        }
    }
    fclose(file);

    if (total_count < 100) {
        fprintf(stderr, "HATA: Yetersiz veri!\n");
        return 1;
    }

    for (int i = 0; i < 100; i++) {
        input_data[i] = all_data[total_count - 100 + i];
    }

    myNeuralNetworkFunction(input_data, output_results);

    int en_yuksek_index = 0;
    double max_olasilik = -1.0;
    for (int i = 0; i < 10; i++) {
        if (isnan(output_results[i])) output_results[i] = 0.0;
        if (output_results[i] > max_olasilik) {
            max_olasilik = output_results[i];
            en_yuksek_index = i;
        }
    }

    log_olustur(en_yuksek_index, ariza_aciklamalari[en_yuksek_index], max_olasilik * 100);

    printf("\n--- RULMAN ANALIZ RAPORU ---\n");
    printf("Durum               : %s\n", ariza_aciklamalari[en_yuksek_index]);
    printf("Guven Orani         : %%%.2f\n", max_olasilik * 100);
    printf("----------------------------\n");
    fflush(stdout); 

    myNeuralNetworkFunction_terminate();
    return 0;
}
