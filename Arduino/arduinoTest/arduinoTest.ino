#include <SoftwareSerial.h>


const int btRX = 3;
const int btTX = 4;

//Esto es para revisar los sensores cada 30 segundos y no saturar el sistema eléctrico del arduino
unsigned long previousSensorReadMillis = 0;  // El tiempo en el que se tomó la última medición
const long intervalSensorRead = 30000;

//Esto es para asegurarse que los ventiladores se apaguen luego de 30 segundos de encendidos
//unsigned long previousFanOnTimeMillis = 0;  // El tiempo en el que se encendió por últma vez el ventilador
//const long intervalFanOn = 250000;

//Esto es para asegurarse que los ventiladores se apaguen luego de 30 segundos de encendidos
//unsigned long previousLightOnTimeMillis = 0;  // El tiempo en el que se se encendió por últma vez la luz
//const long intervalLightOn = 5000;

//Esto es para asegurarse que los ventiladores se apaguen luego de 30 segundos de encendidos
unsigned long previousWaterOnTimeMillis = 0;  // El tiempo en el que se se encendió por últma vez el agua
const long intervalWaterOn = 2000;

//Variables para guardar el estado de los periféricos
bool isFanOn = false;
bool isLightOn = false;
bool isWaterOn = false;

//Variables para guardar la lectura de los sensores
float currentTemperature = 0;
float currentAirHumidity = 0;
float currentSoilHumidity = 0;
float currentLightIntensity = 0;

float upperAcceptedTemperatureValue = 30;
float lowerAcceptedTemperatureValue = 20;

float lowerAcceptedSoilHumidityValue = 20;



SoftwareSerial HM10(btRX, btTX);  // RX, TX

const char TURN_FAN_ON_OFF = '1';
const char TURN_LIGHT_ON_OFF = '2';
const char TURN_WATER_ON_OFF = '3';



void setup() {
  // Se abren las comunicaciones del bluetooth:
  Serial.begin(9600);
  Serial.println("HM-10 started at 9600");
  HM10.begin(9600);
  HM10.println("HM-10 connected at 9600");
}

void loop() {  // run over and over
  //Leer datos entrantes desde la aplicación
  unsigned long currentMillis = millis();




  //Revisa si la aplicación hizo alguna petición y la procesa
  while (HM10.available()) {
    char charIn = HM10.read();
    processManualDataIn(charIn, currentMillis);
  }

  currentTemperature = readTemperature();
  currentAirHumidity = readAirHumidity();
  currentSoilHumidity = readSoilHumidity();
  currentLightIntensity = readLightIntensity();

  if (!isFanOn) {
    if (currentTemperature >= upperAcceptedTemperatureValue) {
      turnFanOn();
    }
  }
  else{
    if (currentTemperature < upperAcceptedTemperatureValue){
      turnFanOff();
    }
  }
  if (!isLightOn) {
    if (currentTemperature <= lowerAcceptedTemperatureValue) {
      turnLightOn();
    }
  }
  else{
    if (currentTemperature > lowerAcceptedTemperatureValue){
      turnLightOff();
    }
  }

  if (!isWaterOn) {
    if (currentSoilHumidity <= lowerAcceptedSoilHumidityValue) {
      turnWaterOn(currentMillis);
    }
  }
  else{
    if ((currentMillis - previousWaterOnTimeMillis) >= intervalWaterOn){
      turnWaterOff();
    }
  }


  //Revisa si el ventilador lleva más tiempo encendido del permitido
  /*if (isFanOn && (currentMillis - previousFanOnTimeMillis) >= intervalFanOn) {
    turnFanOff();
  }

  //Revisa si la luz lleva más tiempo encendida del permitido
  if (isLightOn && (currentMillis - previousLightOnTimeMillis) >= intervalLightOn) {
    turnLightOff();
  }

  //Revisa si el agua lleva más tiempo encendida del permitido
  if (isWaterOn && (currentMillis - previousWaterOnTimeMillis) >= intervalWaterOn) {
    turnWaterOff();
  }*/

  char buffer[10];
  String outputStr = "";
  //Revisa si los sensores deben revisarse y si las mediciones están en los rangos aceptados

  if (!((currentMillis - previousSensorReadMillis) >= intervalSensorRead)) {
    outputStr += "NM/NM/NM/NM/";
  } else {

    dtostrf(currentTemperature, 6, 2, buffer);
    outputStr += buffer;
    outputStr += "/",

      dtostrf(currentAirHumidity, 6, 2, buffer);
    outputStr += buffer;
    outputStr += "/";

    dtostrf(currentSoilHumidity, 6, 2, buffer);
    outputStr += buffer;
    outputStr += "/";

    dtostrf(currentLightIntensity, 6, 2, buffer);
    outputStr += buffer;
    outputStr += "/";
  }

  if (isFanOn) {
    outputStr += "T/";
  } else {
    outputStr += "F/";
  }

  if (isLightOn) {
    outputStr += "T/";
  } else {
    outputStr += "F/";
  }

  if (isWaterOn) {
    outputStr += "T";
  } else {
    outputStr += "F";
  }

  //Escribir datos
  if (Serial.available()) {
    HM10.print(outputStr);
  }
}


//TODO: Función para procesar los datos entrantes
void processManualDataIn(char messageIn, unsigned long currentMillis) {
  if (messageIn == TURN_FAN_ON_OFF) {
    if (isFanOn) {
      turnFanOff();
    } else {
      turnFanOn();
    }
  }

  if (messageIn == TURN_LIGHT_ON_OFF) {
    if (isLightOn) {
      turnLightOff();
    } else {
      turnLightOn();
    }
  }

  if (messageIn == TURN_WATER_ON_OFF) {
    if (isWaterOn) {
      turnWaterOff();
    } else {
      turnWaterOn(currentMillis);
    }
  }
}

//TODO: Función para encender el ventilador
void turnFanOn() {
  /*Código empieza aquí*/

  /*Código termina aquí*/

  //Cambia el valor de la variable isFanOn
  isFanOn = true;
  //previousFanOnTimeMillis = currentMillis;
}

//TODO: Función para apagar el ventilador
void turnFanOff() {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  isFanOn = false;
}


//TODO: Función para encender la luz
void turnLightOn() {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  isLightOn = true;
  //previousLightOnTimeMillis = currentMillis;
}

//TODO: Función para apagar la luz
void turnLightOff() {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  isLightOn = false;
}


//TODO: Función para encender el agua
void turnWaterOn(unsigned long currentMillis) {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  isWaterOn = true;
  previousWaterOnTimeMillis = currentMillis;
}

//TODO: Función para apagar el ague
void turnWaterOff() {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  isWaterOn = false;
}


//TODO: Función para leer el sensor de temperatura
float readTemperature() {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  return 0;
}

//TODO: Función para leer el sensor de humedad del aire
float readAirHumidity() {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  return 0;
}

//TODO: Función para leer el sensor de humedad de la tierra
float readSoilHumidity() {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  return 0;
}

//TODO: Función para leer el sensor de luminosidad
float readLightIntensity() {
  /*Código empieza aquí*/

  /*Código termina aquí*/
  return 0;
}
