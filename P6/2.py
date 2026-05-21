import cv2
import os

# Rutas dinámicas
dir_actual = os.path.dirname(os.path.abspath(__file__))
ruta_modelo = os.path.join(dir_actual, 'xml', 'haarcascade_frontalface_alt.xml')
# ruta_video = os.path.join(dir_actual, 'video', 'v1.mp4') 
ruta_video = os.path.join(dir_actual, 'video', 'v2.mp4') 

# Cargamos el modelo
modeloCara = cv2.CascadeClassifier(ruta_modelo)

# Abrimos el vídeo
camara = cv2.VideoCapture(ruta_video)

while camara.isOpened():
    ret, img = camara.read()
    
    # Si el vídeo termina o no se lee correctamente, salimos del bucle limpiamente
    if not ret:
        break

    # Convertimos a gris
    gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Detectamos caras
    faces = modeloCara.detectMultiScale(gris, scaleFactor=1.1, minNeighbors=4)

    # Pintamos rectángulos (Rojo)
    for (x, y, w, h) in faces:
        cv2.rectangle(img, (x, y), (x + w, y + h), (0, 0, 255), 3)

    cv2.imshow('Ejercicio 2 - Caras en Video', img)
    
    if cv2.waitKey(1) == 27: # Tecla Esc
        break

camara.release()
cv2.destroyAllWindows()