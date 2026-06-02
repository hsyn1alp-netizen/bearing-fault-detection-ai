#include <stdio.h>
#include <stdlib.h>
#include "logger.h"
extern void hesapla_rulman_saglik(double *input, double *output);
int main() {
    double min_vals[3] = {0.0411, 2.8005, 0.0050}, max_vals[3] = {0.5522, 35.6083, 8.4410};
    double girilen_rms, girilen_kurtosis, girilen_p2p, input_for_ai[3], saglik_sonucu;
    FILE *file = fopen("titresimverisi.txt", "r"); if (file == NULL) return 1;
    while (fscanf(file, "%lf, %lf, %lf", &girilen_rms, &girilen_kurtosis, &girilen_p2p) != EOF) {
        input_for_ai[0] = (girilen_rms - min_vals[0]) / (max_vals[0] - min_vals[0]);
        input_for_ai[1] = (girilen_kurtosis - min_vals[1]) / (max_vals[1] - min_vals[1]);
        input_for_ai[2] = (girilen_p2p - min_vals[2]) / (max_vals[2] - min_vals[2]);
        for(int i = 0; i < 3; i++) { if(input_for_ai[i] > 1.0) input_for_ai[i] = 1.0; if(input_for_ai[i] < 0.0) input_for_ai[i] = 0.0; }
        hesapla_rulman_saglik(input_for_ai, &saglik_sonucu);
        double yuzde = saglik_sonucu * 100.0; if(yuzde > 100.0) yuzde = 100.0; if(yuzde < 0.0) yuzde = 0.0;
        log_sonuc(girilen_rms, girilen_kurtosis, girilen_p2p, yuzde);
        printf("%.6f\t%.6f\t%.6f\t%%%.2f\n", girilen_rms, girilen_kurtosis, girilen_p2p, yuzde);
    }
    fclose(file); return 0;
}
