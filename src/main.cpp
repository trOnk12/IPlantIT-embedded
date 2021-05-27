#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define ADVERTISMENT_SERVICE_UUID      "84b3571a-98d0-46fe-95c2-bb2fc4b126ad"

#define GENERAL_INFO_SERVICE_UUID "3057b961-e173-4aae-8432-565f123daaa5"
#define DEVICE_NAME_CHARACTERISTIC_UUID "547de50b-14b8-49fc-9c88-deb5b65cf716"


class DeviceNameCallback : public BLECharacteristicCallbacks{
    void onWrite(BLECharacteristic* pCharactersitic){
        Serial.println("Device name set");
    }
};

class ConnectionCallback : public BLEServerCallbacks{
  void onConnect(BLEServer* pServer){
      Serial.println("Device connceted");
  }

  void onDisconnect(BLEServer* pServer){
        Serial.println("Device disconnected");
  }
};

void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE work!");

  BLEDevice::init("I-Plant");
  BLEServer *pServer = BLEDevice::createServer();

  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(ADVERTISMENT_SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);

  pServer->setCallbacks(new ConnectionCallback());

      BLEService *pService = pServer->createService(GENERAL_INFO_SERVICE_UUID);
      BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         DEVICE_NAME_CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
      pCharacteristic->setValue("Hello World says Neil");
      pCharacteristic->setCallbacks(new DeviceNameCallback());
      pService->start();

  BLEDevice::startAdvertising();
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(2000);
       
}
