#include <Arduino_LSM6DSOX.h>
//Include libreria
#include <ArduinoBLE.h>

// Servizio BLE viene identificato con un UUID a 128 bit
BLEService accService("a193e278-ac42-474f-8c83-358c4b6a29ec");

// Dichiarazione delle caratteristiche con permessi Read, Indicate e Notify
/*BLEFloatCharacteristic axesX("60cfcb89-e01d-410d-ac17-c13d827f1ff0", BLERead|BLEIndicate|BLENotify);
BLEFloatCharacteristic axesY("60cfcb89-e01d-410d-ac17-c13d827f1ff1", BLERead|BLEIndicate|BLENotify);
BLEFloatCharacteristic axesZ("60cfcb89-e01d-410d-ac17-c13d827f1ff2", BLERead|BLEIndicate|BLENotify);*/

// Per testing usando la NRF Connect APP
BLEStringCharacteristic axesX("60cfcb89-e01d-410d-ac17-c13d827f1ff0", BLERead|BLEIndicate|BLENotify,20);
BLEStringCharacteristic axesY("60cfcb89-e01d-410d-ac17-c13d827f1ff1", BLERead|BLEIndicate|BLENotify,20);
BLEStringCharacteristic axesZ("60cfcb89-e01d-410d-ac17-c13d827f1ff2", BLERead|BLEIndicate|BLENotify,20);

float Ax, Ay, Az;
uint32_t updateValue = 0;

void setup() {
  Serial.begin(9600);
  while(!Serial);

  //Inizializzazione del BLE
  if (!BLE.begin()) {
    Serial.println("starting Bluetooth® Low Energy module failed!");
    while (1);
  }

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println("Hz");
  Serial.println();

  // Configurazione del nome del dispositivo da mostrare via BLE
  BLE.setLocalName("Accelerometer");
  // Aggiunta del servizio al messaggio di advertisement
  // N.B. il device potrebbe avere più servizi, ma esporne solo alcuni
  BLE.setAdvertisedService(accService);

  // Aggiunta delle caratteristiche al servizio BLE
  accService.addCharacteristic(axesX);
  accService.addCharacteristic(axesY);
  accService.addCharacteristic(axesZ);

  // Aggiunta del servizio all'oggetto BLE.
  // Questo permette alla libreria di interagire con il servizio e le sue caratteristiche
  BLE.addService(accService);

  // Start dell'invio dei messaggi di advertisement
  BLE.advertise();

  Serial.println("Started");
}


void loop() {
  // Controlla se c'è un device connesso
  BLEDevice central = BLE.central();

  // se un dispositivo central è connesso:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());

    // while il central rimane connesso:
    while (central.connected()) {
      // Business logic: 1) leggi i dati dell'IMU ogni 1 sec 2) inviali
      if(millis() - updateValue > 1000){
        if (IMU.accelerationAvailable()) {
          IMU.readAcceleration(Ax, Ay, Az);

          Serial.println("Accelerometer data: ");
          Serial.print(Ax);
          Serial.print('\t');
          Serial.print(Ay);
          Serial.print('\t');
          Serial.println(Az);
          Serial.println();
          // Se il central si è sottoscritto alla caratteristica
          if(axesX.subscribed()){
            //axesX.writeValue(Ax); //Da usare con le caratteristiche di tipo float
            axesX.writeValue(String(Ax));
          }

          if(axesY.subscribed()){
            //axesY.writeValue(Ay); //Da usare con le caratteristiche di tipo float
            axesY.writeValue(String(Ay));
          }

          if(axesZ.subscribed()){ 
            //axesZ.writeValue(Az); //Da usare con le caratteristiche di tipo float
            axesZ.writeValue(String(Az));
          }

        }
        updateValue = millis();
      }
    }

    // when the central disconnects, print it out:
    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}