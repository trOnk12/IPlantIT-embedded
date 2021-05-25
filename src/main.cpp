#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#define SERVICE_UUID        "84b3571a-98d0-46fe-95c2-bb2fc4b126ad"
#define CHARACTERISTIC_UUID "547de50b-14b8-49fc-9c88-deb5b65cf716"


class WiFiSSIDCallback : public BLECharacteristicCallbacks{
    void onWrite(BLECharacteristic* pCharactersitic){
    
        Serial.println("Characteristic defined! Now you can read it in your phone!");
    }
};

void setup() {
  Serial.begin(9600);
  Serial.println("Starting BLE work!");

  BLEDevice::init("I-Plant");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  pCharacteristic->setValue("Hello World says Neil");
  pCharacteristic->setCallbacks(new WiFiSSIDCallback());
  pService->start();
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("Characteristic defined! Now you can read it in your phone!");
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(2000);
}
