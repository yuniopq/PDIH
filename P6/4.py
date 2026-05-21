import cv2
import os

dir_actual = os.path.dirname(os.path.abspath(__file__))
ruta_caras = os.path.join(dir_actual, 'xml', 'haarcascade_frontalface_alt.xml')
ruta_cuerpos = os.path.join(dir_actual, 'xml', 'haarcascade_fullbody.xml')
ruta_video = os.path.join(dir_actual, 'video', 'v3.mp4') 

# Cargamos ambos modelos
modeloCara = cv2.CascadeClassifier(ruta_caras)
modeloCuerpo = cv2.CascadeClassifier(ruta_cuerpos)

camara = cv2.VideoCapture(ruta_video)

while camara.isOpened():
    ret, img = camara.read()
    if not ret:
        break

    img = cv2.resize(img, (0, 0), fx=0.5, fy=0.5)

    gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # 1. Detectar y pintar cuerpos 
    cuerpos = modeloCuerpo.detectMultiScale(gris, scaleFactor=1.1, minNeighbors=3)
    for (cx, cy, cw, ch) in cuerpos:
        cv2.rectangle(img, (cx, cy), (cx + cw, cy + ch), (255, 0, 0), 2)

    # 2. Detectar y pintar caras simultáneamente (Rectángulo Rojo) 
    caras = modeloCara.detectMultiScale(gris, scaleFactor=1.1, minNeighbors=4)
    for (fx, fy, fw, fh) in caras:
        cv2.rectangle(img, (fx, fy), (fx + fw, fy + fh), (0, 0, 255), 2)

    cv2.imshow('Ejercicio 4 - Cuerpos y Caras Simultaneos', img)
    if cv2.waitKey(1) == 27:
        break

camara.release()
cv2.destroyAllWindows()