# Práctica 3: Experimentación con Arduino

## Requisito Ampliado 3: Detector de la cantidad de luz

### Identificación de componentes

| Componente | Pin Arduino |
| :--- | :--- |
| **Fotorresistencia (LDR)** | Pin A2 (Analógico) |
| **LED Rojo** | Pin 9 (PWM) |
| **Resistencia 10k$\Omega$** | GND |
| **Resistencia 220$\Omega$**| Pin 9 |

### Esquema de conexiones (Tinkercad)

### Código Fuente Documentado

```cpp
/*
 * Práctica 3 - PDIH
 * Requisito: Detector de cantidad de luz
 * Alumno: ZhiXiang Zhou Wang
 * Descripción: Control de brillo de LED (PWM) basado en sensor LDR.
 */

void setup() {
  // Pin 9 soporta PWM para variar el voltaje del LED
  pinMode(9, OUTPUT); 
  
  // Iniciamos comunicación serie para monitorizar los niveles de luz
  Serial.begin(9600); 
}

void loop() {
  // Leemos el valor del sensor (0 a 1023)
  // Usamos A2 debido a mayor estabilidad en la placa física
  int intensidadLuz = analogRead(A2); 
  
  // Imprimimos el valor bruto para depuración
  Serial.print("Valor LDR: ");
  Serial.println(intensidadLuz);

  /* * Mapeamos el valor:
   * Entrada: 0 - 1023 (Rango del sensor)
   * Salida: 255 - 0 (Invertido para que brille más con menos luz)
   */
  int brilloLED = map(intensidadLuz, 0, 1023, 255, 0);
  
  // Enviamos la señal PWM al LED
  analogWrite(9, brilloLED); 
  
  delay(10); // Pequeña pausa para estabilidad
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

