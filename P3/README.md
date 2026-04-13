# Práctica 3: Experimentación con Arduino

## Requisito 4: Activación del Motor

### Identificación de componentes

| Componente  | Pin Arduino |
| :---  | :--- |
| **Micro Servo SG90** | Pin 8 |
| **Pulsador** | Pin 9 |
| **Resistencia 10kΩ** | GND |

### Esquema de conexiones
![Esquema Servo](img/Requisito_Ampliado_4_Activación_del_motor.png)

### Código Fuente

```cpp
/*
 * Práctica 3 - PDIH
 * Requisito Ampliado 4: Activación del motor
 * Alumno: ZhiXiang Zhou Wang
 * Descripción: El servo avanza mientras se pulsa y retrocede al soltar.
 */

#include <Servo.h>

Servo miServo;       
const int pinBoton = 9;   // Botón conectado al pin 9
int estadoBoton = 0; 

void setup() {
  miServo.attach(8);      // Servomotor conectado al pin 8
  pinMode(pinBoton, INPUT); 
  
  miServo.write(0);       // Iniciamos en 0 grados
  delay(500);             
}

void loop() {

  // MIENTRAS ESTÉ PULSADO: Avanza hacia 180°
  if (digitalRead(pinBoton) == HIGH) {
    if (miServo.read() < 180) { // Si no ha llegado al máximo
      miServo.write(miServo.read() + 2); // Incrementa la posición de 2 en 2
    }
    delay(15); // Pequeña pausa para suavizar el movimiento
  } 
  
  // MIENTRAS ESTÉ SUELTO: Retrocede hacia 0°
  else {
    if (miServo.read() > 0) { // Si no ha llegado al mínimo
      miServo.write(miServo.read() - 2); // Decrementa la posición
    }
    delay(15); // Pequeña pausa para suavizar el movimiento
  }
}
```

### Muestra de funcionamiento 

A continuación se muestra el funcionamiento en el dispositivo físico, demostrando la respuesta del motor al pulsador:

> [\!vçVideo funcionamiento Requisito Ampliado 4]
> **[Haz clic aquí para ver el vídeo de la demostración física](enlace)**

