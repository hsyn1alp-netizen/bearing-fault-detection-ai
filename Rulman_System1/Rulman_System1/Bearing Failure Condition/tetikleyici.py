import subprocess
import os

CURRENT_DIR = "/home/alp/Desktop/Rulman_System/codegen/lib/myNeuralNetworkFunction"
EXE_PATH = "./model_exe"

def analiz():
    print("Sistem baslatildi. Analiz ediliyor...")
    try:
        # Döngü (while) kaldırıldı, sadece bir kez çalışır.
        process = subprocess.Popen(
            [EXE_PATH],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            encoding='utf-8',
            cwd=CURRENT_DIR
        )
        stdout, stderr = process.communicate()

        if stdout:
            print(stdout)
        if stderr:
            print(f"C Hatasi: {stderr}")

    except Exception as e:
        print(f"Hata: {e}")

if __name__ == "__main__":
    analiz()
