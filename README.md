# Demo il BLE con Arduino @WeMake
Lo sketch utilizzato in questa demo permette di leggere i dati dell'accelerometro della RP2040 tramite uno smartphone con il BLE.
## Prerequisito
1. Possedere una [Arduino Nano RP2040 Connect](https://store.arduino.cc/products/arduino-nano-rp2040-connect)
## Per compilare lo sketch
1. Scarica e installa l' [Arduino IDE](https://www.arduino.cc/en/software) oppure se hai un account Arduino puoi utilizzare il Cloud Editor
2. Installa l'Arduino Core per Arduino Nano RP2040 *Arduino MBed OS Nano Boards*
3. Installa la libreria *ArduinoBLE*
4. Apri lo sketch *demo* e upload!

## Test
1. Installa sul tuo smartphone l'app nRF Connect
2. Carica lo sketch sulla board e apri il serial monitor
3. Apri l'app nRF Connect e connettiti al dispositivo chiamato *accelerometer*
4. Apri il servizio con ID `a193e278-ac42-474f-8c83-358c4b6a29ec`
5. Sottoscrivi alle caratteristiche (click sul pulsante delle due frecce in senso opposto)
6. inizierai a vedere i dati dell'accelerometro sul tuo smartphone