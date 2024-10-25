#include "DHT.h"
#include <SoftwareSerial.h>

#define DHTPIN 2
#define DHTTYPE DHT11
#define buzzerPin 3  
#define calefactorPin 4
#define ventiladorPin 5

DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial BTSerial(10, 11); // RX, TX para el HC-05

void setup() {
  Serial.begin(9600);  // Inicializa la comunicación serial
  BTSerial.begin(9600); // Inicializa la comunicación Bluetooth
  pinMode(buzzerPin, OUTPUT);
  pinMode(calefactorPin, OUTPUT);
  pinMode(ventiladorPin, OUTPUT);
  dht.begin();

  Serial.println("Iniciando sistema...");
  BTSerial.println("Iniciando comunicación con HC-05...");
}

void loop() {
  delay(2000);

  // Lectura de la temperatura, humedad e índice de calor
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float hif = dht.computeHeatIndex(t, h);

  if (isnan(h) || isnan(t)) {
    Serial.println(F("¡Error al leer del sensor DHT!"));
    BTSerial.println(F("¡Error al leer del sensor DHT!"));
    return;
  }

  // Enviar datos al Serial y al Bluetooth
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.print(" Humedad: ");
  Serial.print(h);
  Serial.print(" IndiceCalor: ");
  Serial.println(hif);

  BTSerial.print("Temperatura: ");
  BTSerial.print(t);
  BTSerial.print(" Humedad: ");
  BTSerial.print(h);
  BTSerial.print(" IndiceCalor: ");
  BTSerial.println(hif); // Esto crea una nueva línea en cada iteración

  // Lógica de control para buzzer, calefactor y ventilador
  if (t >= 30) {
    digitalWrite(buzzerPin, HIGH);
    Serial.println(F("Alerta: Temperatura alta, activando buzzer."));
    BTSerial.println(F("Alerta: Temperatura alta, activando buzzer."));
  } else {
    digitalWrite(buzzerPin, LOW);
    Serial.println(F("Temperatura normal, buzzer apagado."));
    BTSerial.println(F("Temperatura normal, buzzer apagado."));
  }

  if (t >= 30) {
    digitalWrite(ventiladorPin, HIGH);
    digitalWrite(calefactorPin, LOW);
    Serial.println(F("Alerta: Temperatura alta, activando ventilador."));
    BTSerial.println(F("Alerta: Temperatura alta, activando ventilador."));
  }

  if (t <= 20) {
    digitalWrite(calefactorPin, HIGH);
    digitalWrite(ventiladorPin, LOW);
    Serial.println(F("Alerta: Temperatura baja, activando calefactor."));
    BTSerial.println(F("Alerta: Temperatura baja, activando calefactor."));
  }

  if (t <= 30 && t >= 20) {
    digitalWrite(calefactorPin, LOW);
    digitalWrite(ventiladorPin, LOW);
    Serial.println(F("Temperatura estable, apagando todos los sistemas."));
    BTSerial.println(F("Temperatura estable, apagando todos los sistemas."));
  }

  // Enviar y recibir datos desde Bluetooth
  if (BTSerial.available()) {
    char data = BTSerial.read();
    Serial.print("Recibido desde Bluetooth: ");
    Serial.println(data);  // Muestra en el monitor serie lo que se recibe por Bluetooth
  }

  if (Serial.available()) {
    char data = Serial.read();
    BTSerial.write(data);  // Envia lo que se escribe en el monitor serie al Bluetooth
  }
}

