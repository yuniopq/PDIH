import cv2
import os

dir_actual = os.path.dirname(os.path.abspath(__file__))

ruta_modelo_gato = os.path.join(dir_actual, 'xml', 'haarcascade_frontalcatface_extended.xml')
ruta_video = os.path.join(dir_actual, 'video', 'gato.mp4')

# Creamos la ventana y le decimos que permita cambiar el tamaño
cv2.namedWindow('Ejercicio 3 - Detector de Gatos', cv2.WINDOW_NORMAL)

# Cargamos el clasificador de gatos
modeloGato = cv2.CascadeClassifier(ruta_modelo_gato)

# Abrimos el flujo de vídeo
camara = cv2.VideoCapture(ruta_video)

print("Ejecutando detector de gatos... Pulsa 'Esc' en la ventana de vídeo para salir.")

while camara.isOpened():
    ret, img = camara.read()
    
    # Si se acaba el vídeo, cerramos el bucle limpiamente
    if not ret:
        break

    img = cv2.resize(img, (0, 0), fx=0.35, fy=0.35)

    # Convertimos el frame a escala de grises
    gris = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

    # Detectamos las caras de los gatos 
    gatos = modeloGato.detectMultiScale(gris, scaleFactor=1.1, minNeighbors=6)

    # Pintamos los rectángulos 
    for (x, y, ancho, alto) in gatos:
        cv2.rectangle(img, (x, y), (x + ancho, y + alto), (0, 255, 0), 3)

    # Mostramos el resultado en tiempo real
    cv2.imshow('Ejercicio 3 - Detector de Gatos', img)
    
    # Espera 1 milisegundo entre frames. Si pulsas 'Esc' (código 27), se cierra.
    if cv2.waitKey(1) == 27:
        break

# Liberamos recursos
camara.release()
cv2.destroyAllWindows()