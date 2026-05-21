import cv2

# Cargamos nuestro modelo classificador
modelo = cv2.CascadeClassifier('xml/haarcascade_frontalface_alt.xml')

# Cargamos la imagen
img = cv2.imread('img/einstein_plank.jpg')
imagen = cv2.cvtColor(img, cv2.COLOR_BGR2GRAY)

# scaleFactor es el factor de escala: si lo hacemos más cercano a 1.0
# tardará un poco más de tiempo, pero será más fiable (no se le
# escaparán algunas caras).
# minNeighbors indica la calidad de las detecciones: un valor elevado
# resulta en menos detecciones, pero con más fiabilidad.

# Buscamos los rostros:
rostros = modelo.detectMultiScale(imagen, scaleFactor=1.5, minNeighbors=6)

# recorremos el array 'rostros' y dibujamos los rectángulos
for (x, y, ancho, alto) in rostros:
	cv2.rectangle(img, (x, y), (x+ancho, y+alto), (0, 0, 255), 3)

# Abrimos una ventana con el resultado:
cv2.imshow('Output', img)

print("\nMostrando resultado. Pulsa cualquier tecla para salir.\n")
cv2.waitKey(0)

cv2.destroyAllWindows()