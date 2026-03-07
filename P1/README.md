# Práctica 1: Librería de Entrada/Salida para MS-DOS

Este repositorio contiene la implementación de una librería de funciones de bajo nivel en lenguaje C para el control de la consola y gráficos básicos en entornos MS-DOS, utilizando interrupciones de la BIOS (INT 10h e INT 16h).

## 📂 Estructura del Proyecto

* **mi_io.h**: Cabecera con los prototipos de las funciones y definiciones.
* **mi_io.c**: Implementación de la librería con llamadas a interrupciones.
* **main.c**: Programa de prueba con menú interactivo para evaluar todas las funciones.

## 🛠️ Funciones Implementadas

### Requisitos Mínimos
* `gotoxy(x, y)`: Posiciona el cursor en pantalla.
* `setcursortype(modo)`: Cambia la apariencia del cursor (Invisible, Normal, Grueso).
* `setvideomode(modo)`: Cambia entre modo texto y gráfico.
* `getvideomode()`: Obtiene el modo de video actual.
* `textcolor(color)` / `textbackground(color)`: Define los colores actuales.
* `clrscr()`: Borra la pantalla con el color de fondo actual.
* `cputchar(c)`: Escribe un carácter con el atributo de color actual y avanza el cursor.
* `getche()`: Lee una tecla y la muestra por pantalla (echo).

### Requisitos Ampliados (Extras)
* **Dibujo de recuadros**: `dibujar_cuadrado()` permite crear ventanas con bordes ASCII en modo texto.
* **Modo Gráfico**: Función `pixel()` para dibujar puntos en modo CGA y `dibujar_dibujo()` para crear una escena gráfica.
* **ASCII Art**: Función `dibujar_gato_gigante()` que imprime arte ASCII complejo respetando colores.

## 🚀 Compilación y Ejecución

Para compilar el proyecto en DOSBox con el compilador Borland C, utiliza el script proporcionado:

```cmd
c main
