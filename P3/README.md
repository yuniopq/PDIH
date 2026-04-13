# Práctica 3: Experimentación con Arduino

## Requisito 4: Activación del Motor

### Identificación de componentes

| Componente  | Pin Arduino |
| :---  | :--- |
| **Micro Servo SG90** | Pin 8 (PWM) |
| **Pulsador** | Pin 9 |
| **Resistencia 10kΩ** | GND |


### Código Fuente

```cpp
/*
 * Práctica 3 - PDIH
 * Requisito Ampliado 4: Activación del motor
 * Alumno: ZhiXiang Zhou Wang
 * Descripción: Control bidireccional de un servo mediante pulsador.
 */

#include <Servo.h>

Servo miServo;        // Objeto para controlar el motor
const int pinBoton = 9;   // Botón configurado en el pin 9
int estadoBoton = 0; 

void setup() {
  miServo.attach(8);      // Servomotor conectado al pin 8
  pinMode(pinBoton, INPUT); 
  
  miServo.write(0);       // Posición inicial de reposo
  delay(500);             // Tiempo para que el motor se estabilice
}

void loop() {
  // Leemos el estado del pulsador en cada ciclo
  estadoBoton = digitalRead(pinBoton); 

  // Lógica de avance: Mientras se detecte pulsación (HIGH)
  if (estadoBoton == HIGH) {
    if (miServo.read() < 180) { 
      miServo.write(miServo.read() + 2); // Incremento constante de ángulo
    }
    delay(15); // Suavizado del movimiento
  } 
  
  // Lógica de retroceso: Al soltar el pulsador (LOW)
  else {
    if (miServo.read() > 0) { 
      miServo.write(miServo.read() - 2); // Decremento constante de ángulo
    }
    delay(15); // Suavizado del movimiento
  }
}
```

### Muestra de funcionamiento 

A continuación se muestra el funcionamiento en el dispositivo físico, demostrando la respuesta del motor al pulsador:

> [\!vçVideo funcionamiento Requisito Ampliado 4]
> **[Haz clic aquí para ver el vídeo de la demostración física](enlace)**

