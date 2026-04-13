void setup() {
  pinMode(9, OUTPUT);
}

void loop() {
  int intensidadLuz = analogRead(A2); 
  
  
  intensidadLuz = map(intensidadLuz, 0, 1023, 255, 0);
  analogWrite(9, intensidadLuz); 
  
  delay(10); 
}