import tensorflow as tf
import cv2
import numpy as np
from collections import deque
import os
import ctypes
import time

# --- C LOGGER ENTEGRASYONU ---
try:
    lib_path = os.path.abspath("./logger.so")
    _lib = ctypes.CDLL(lib_path)
    _lib.log_result.argtypes = [ctypes.c_char_p, ctypes.c_float]
    
    def c_logger(label, score):
        _lib.log_result(label.encode('utf-8'), ctypes.c_float(score))
except Exception as e:
    def c_logger(label, score): pass

class_names = ['cizik', 'hasarli', 'kirli', 'normal', 'pasli']

def run_test():
    model_path = "/home/alp/Desktop/Rulman_System/rulman_env/model_saved"
    model = tf.saved_model.load(model_path)
    infer = model.signatures["serving_default"]

    pred_buffer = deque(maxlen=5)
    CONF_THRESHOLD = 35 
    
    # STABİLİZASYON DEĞİŞKENLERİ
    last_logged_label = None        
    current_stable_label = None     
    stable_start_time = None        
    STABLE_DURATION = 3             

    cap = cv2.VideoCapture(0, cv2.CAP_V4L2)
    if not cap.isOpened(): return

    # Hata almamak için başlangıç değeri
    display_text = "Analiz basliyor..."

    while True:
        # CPU'yu %100 yapmaması için her döngü başında kısa bir ara (0.1 sn = 10 FPS)
        time.sleep(0.1) 

        ret, frame = cap.read()
        if not ret: break

        img = cv2.resize(frame, (224,224))
        img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
        img = np.expand_dims(img, axis=0)
        img = tf.keras.applications.efficientnet.preprocess_input(img).astype(np.float32)

        input_tensor = tf.convert_to_tensor(img)
        try:
            preds_dict = infer(keras_tensor_3411=input_tensor)
        except:
            input_name = list(infer.structured_input_signature[1].keys())[0]
            preds_dict = infer(**{input_name: input_tensor})

        preds = list(preds_dict.values())[0].numpy()
        pred_buffer.append(preds)
        avg_preds = np.mean(pred_buffer, axis=0)

        idx = np.argmax(avg_preds)
        score = np.max(avg_preds) * 100
        final_label = class_names[idx]
        display_text = f"{final_label}: %{score:.1f}"

        # 3 SANİYE SABİT KALMA KONTROLÜ
        if score >= CONF_THRESHOLD:
            if final_label != current_stable_label:
                current_stable_label = final_label
                stable_start_time = time.time()
            else:
                elapsed_time = time.time() - stable_start_time
                if elapsed_time >= STABLE_DURATION and final_label != last_logged_label:
                    c_logger(final_label, score)
                    last_logged_label = final_label
        else:
            current_stable_label = None
            stable_start_time = None

        # EKRAN ÇIKTISI
        color = (0,255,0) if final_label == "normal" else (0,0,255)
        cv2.putText(frame, display_text, (20,40), cv2.FONT_HERSHEY_SIMPLEX, 0.8, color, 2)
        cv2.imshow("Rulman Analiz", frame)

        if cv2.waitKey(1) & 0xFF == ord('q'): break

    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    run_test()
