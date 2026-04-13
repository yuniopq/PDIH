# Práctica 3: Experimentación con Arduino

## Requisito Ampliado 3: Detector de la cantidad de luz

### Identificación de componentes

| Componente | Pin Arduino |
| :--- | :--- |
| **Fotorresistencia (LDR)** | Pin A2 (Analógico) |
| **LED Rojo** | Pin 9 (PWM) |
| **Resistencia 10k Omnios** | GND |
| **Resistencia 220 Omnios**| Pin 9 |

### Esquema de conexiones (Tinkercad)
![Esquema Fotorresistencia](img/Requisito_Ampliado_3_Detector_de_la_cantidad_de_luz.png)

### Código Fuente Documentado

```cpp
void setup() {
  pinMode(9, OUTPUT); // Pin 9 como salida para el LED
}

void loop() {
  // Lee el nivel de luz del sensor en el pin analógico A2
  int intensidadLuz = analogRead(A2); 

  // Mapea el valor de entrada (0-1023) al rango de salida del LED (255-0)
  // Se invierte (255 a 0) para que el LED brille más cuando hay menos luz
  intensidadLuz = map(intensidadLuz, 0, 1023, 255, 0);

  analogWrite(9, intensidadLuz); // Aplica el brillo resultante al LED

  delay(10); // Pequeña pausa para estabilizar la señal
}
```

### Muestra de funcionamiento (Vídeo)

> [\!TIP]
> **[ Haz clic aquí para ver el vídeo del sensor de luz](enlace)**


## Requisito Ampliado 4: Activación del Motor

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
#include <Servo.h>

Servo miServo;       
const int pinBoton = 9;   // Botón conectado al pin 9
int estadoBoton = 0; 

void setup() {
  miServo.attach(8);      // Servomotor conectado al pin 8
  pinMode(pinBoton, INPUT); 
  
  miServo.write(0);       // Iniciamos en 0 grados
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

> [\!Video funcionamiento Requisito Ampliado 4]
> **[Haz clic aquí para ver el vídeo de la demostración física](enlace)**

