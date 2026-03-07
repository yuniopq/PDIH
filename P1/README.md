# PDIH - Práctica 1: Librería de E/S mediante Interrupciones BIOS

Este proyecto consiste en el desarrollo de una librería de funciones de bajo nivel en lenguaje C para sistemas MS-DOS. La librería permite controlar la pantalla (tanto en modo texto como gráfico) y el teclado interactuando directamente con las interrupciones de la BIOS (INT 10h e INT 16h).

## 📂 Estructura del Proyecto

El proyecto se ha estructurado de forma modular para fomentar la reutilización del código:

* **`mi_io.h`**: Archivo de cabecera con los prototipos de todas las funciones implementadas.
* **`mi_io.c`**: Implementación de la librería con el código de las interrupciones BIOS.
* **`main.c`**: Programa principal que implementa un menú interactivo para evaluar las funcionalidades.

## 🛠️ Funciones Implementadas

### Requisitos Mínimos

* **`gotoxy(x, y)`**: Posicionamiento del cursor (INT 10h, AH=02h).
* **`setcursortype(modo)`**: Selección de cursor invisible, normal o grueso (INT 10h, AH=01h).
* **`setvideomode(modo)`**: Cambio de modo de video (INT 10h, AH=00h).
* **`getvideomode()`**: Consulta del modo de video actual (INT 10h, AH=0Fh).
* **`textcolor()` / `textbackground()**`: Gestión de atributos de color.
* **`clrscr()`**: Borrado de pantalla mediante scroll (INT 10h, AH=06h).
* **`cputchar(c)`**: Escritura de carácter con atributo y avance de cursor (INT 10h, AH=09h).
* **`getche()`**: Lectura de teclado con eco (INT 16h, AH=00h).

### Requisitos Ampliados (Extras)

* **Dibujo de recuadros**: `dibujar_cuadrado()` genera ventanas con bordes de la tabla ASCII extendida.
* **Modo Gráfico CGA**: Función `pixel()` y una escena completa (`dibujar_dibujo()`) en modo 320x200.
* **ASCII Art**: `dibujar_gato_gigante()` renderiza arte complejo de 24 líneas gestionando caracteres de escape.

## 🚀 Compilación y Ejecución

Para compilar el proyecto en **DOSBox** con Borland C:

```cmd
c main

```

Para ejecutar el programa:

```cmd
main

```

## 📸 Evidencias de Funcionamiento

### Modo Texto: Recuadros y Colores

Prueba de la función `dibujar_cuadrado()` utilizando bordes ASCII dobles y gestión de color de fondo/texto.

### Modo Gráfico: CGA 320x200

Representación de una escena (casa) utilizando la función `pixel()` en modo gráfico 4.

### ASCII Art: Gato Gigante

Renderizado de arte ASCII complejo mediante el uso de `cputchar()` y posicionamiento dinámico.

---

**Autor:** ZhiXiang Zhou Wang
**Repositorio:** PDIH / P1
