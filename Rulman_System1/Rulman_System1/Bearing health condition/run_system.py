import random
import os
import subprocess

def create_vibration_data(filename="titresimverisi.txt", count=100):
    with open(filename, "w") as f:
        for _ in range(count):
            rms = random.uniform(0.00001, 0.1)
            kurtosis = random.uniform(2.8, 3.5)
            p2p = random.uniform(0.00001, 0.1)
            f.write(f"{rms:.6f}, {kurtosis:.6f}, {p2p:.6f}\n")
    print(f"[BILGI] Veriler '{filename}' dosyasina yazildi.")

def run_full_system():
    print("[SISTEM] C kodlari derleniyor...")
    compile_cmd = "gcc Main.c rulman_modeli_final.c logger.c -o rulman_analiz -lm"
    if subprocess.run(compile_cmd, shell=True).returncode == 0:
        print("[SISTEM] Derleme basarili. Analiz baslatiliyor...\n")
        subprocess.run("./rulman_analiz", shell=True)
    else:
        print("[HATA] Derleme sirasinda bir sorun olustu!")

if __name__ == "__main__":
    create_vibration_data()
    run_full_system()
