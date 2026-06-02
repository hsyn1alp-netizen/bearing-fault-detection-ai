#include <math.h>

// Aktivasyon fonksiyonu
double tansig_func(double x) {
    return 2 / (1 + exp(-2*x)) - 1;
}

// Yapay Sinir Ağı Hesaplama Motoru
void hesapla_rulman_saglik(double *input, double *output) {
    double hidden[10];
    
    // Gizli Katman (Hidden Layer) Hesaplamaları
    hidden[0] = tansig_func((-1.815430 * input[0]) + (0.054064 * input[1]) + (0.407224 * input[2]) + -0.999865);
    hidden[1] = tansig_func((1.729022 * input[0]) + (0.089006 * input[1]) + (-0.200956 * input[2]) + 1.006582);
    hidden[2] = tansig_func((-1.560181 * input[0]) + (0.763057 * input[1]) + (0.736242 * input[2]) + 0.045660);
    hidden[3] = tansig_func((1.865161 * input[0]) + (-1.379364 * input[1]) + (-0.947013 * input[2]) + -0.624208);
    hidden[4] = tansig_func((-2.924080 * input[0]) + (0.752042 * input[1]) + (6.851312 * input[2]) + 4.565685);
    hidden[5] = tansig_func((-1.085037 * input[0]) + (1.236608 * input[1]) + (0.898873 * input[2]) + 1.053821);
    hidden[6] = tansig_func((0.722483 * input[0]) + (-1.448269 * input[1]) + (-1.025662 * input[2]) + -1.661321);
    hidden[7] = tansig_func((0.577545 * input[0]) + (0.279976 * input[1]) + (0.574322 * input[2]) + -0.415186);
    hidden[8] = tansig_func((-0.259721 * input[0]) + (-0.416581 * input[1]) + (-0.357108 * input[2]) + 0.702822);
    hidden[9] = tansig_func((1.248041 * input[0]) + (-0.596961 * input[1]) + (-0.321519 * input[2]) + 0.351520);

    // Çıkış Katmanı (Output Layer) Hesaplaması
    *output = (0.393844 * hidden[0]) + (-0.582636 * hidden[1]) + (0.068010 * hidden[2]) + (-0.117978 * hidden[3]) + (1.078335 * hidden[4]) + (-0.018479 * hidden[5]) + (0.083193 * hidden[6]) + (-0.217280 * hidden[7]) + (0.188637 * hidden[8]) + (0.010478 * hidden[9]) + 0.086065;
}