# PDIH - Práctica 5

# Carga de paquetes
library(tuneR)
library(seewave)
library(audio)

# REQUISITOS MÍNIMOS

# 1. Crear dos ficheros de sonido
# Se han generado externamente 

# 2. Leer los dos ficheros de sonido creados y dibujar la forma de onda
nombre <- readWave("nombre.wav")
apellido <- readWave("apellido.wav")

plot(nombre)
plot(apellido)

# 3. Obtener la información de las cabeceras de ambos sonidos
str(nombre)
str(apellido)

# 4. Unir ambos sonidos en uno 
nombre_completo <- pastew(apellido, nombre, at="end", output="Wave")
str(nombre_completo)

# 5. Dibujar la forma de onda de la señal y reproducir el sonido 
plot(nombre_completo, main = "Nombre y Apellido")
listen(nombre_completo)

# 6. Almacenar el sonido como "basico.wav"
writeWave(nombre_completo, "basico.wav")

# REQUISITOS AMPLIADOS

# 7. Filtrar frecuencias entre 10.000Hz y 20.000Hz
filtrado <- bwfilter(nombre_completo, f = 44100, from = 10000, to = 20000, bandpass = FALSE, output = "Wave")

plot(filtrado, main = "10kHz - 20kHz filtrados")
writeWave(filtrado, "filtrado.wav")

# 8. Aplicar el efecto de eco al sonido "basico.wav"
sonido_eco <- echo(nombre_completo, f=44100, amp = c(0.5, 0.2), delay = c(0.5, 0.1), output = "Wave")
writeWave(sonido_eco, "eco.wav")

# Darle la vuelta al sonido (reversa) y almacenarlo como "alreves.wav"
sonido_alreves <- revw(nombre_completo, output = "Wave")
writeWave(sonido_alreves, "alreves.wav")
