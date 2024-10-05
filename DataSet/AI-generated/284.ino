#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHRS.h>
#include <BLEDevice.h>

// Create an instance of the AHRS
Adafruit_AHRS ahrs;

// BLE initialization variables
BLECharacteristic *pCharacteristic;
bool deviceConnected = false;

// Define BLE Service and Characteristic UUIDs
#define SERVICE_UUID "YOUR_SERVICE_UUID"
#define CHARACTERISTIC_UUID "YOUR_CHARACTERISTIC_UUID"

void setup() {
  Serial.begin(115200);
  Serial.println("AHRS Fusion Example");

  // Initialize the AHRS
  if (!ahrs.begin()) {
    Serial.println("No AHRS detected ... Check your wiring!");
    while (1);
  }

  // Initialize BLE
  BLEDevice::init("AHRS");
  BLEServer *pServer = BLEDevice::createServer();
  pServer->setCallbacks(new BLEServerCallbacks());
  
  BLEService *pService = pServer->createService(SERVICE_UUID);
  pCharacteristic = pService->createCharacteristic(CHARACTERISTIC_UUID, BLERead | BLENotify);
  pService->start();
  
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  Serial.println("BLE Advertising started...");
}

void loop() {
  // Update AHRS readings
  ahrs.update();

  // Read the Euler angles
  float roll = ahrs.getRoll();
  float pitch = ahrs.getPitch();
  float yaw = ahrs.getYaw();

  // Format data for BLE transmission
  String data = String(roll) + "," + String(pitch) + "," + String(yaw);
  pCharacteristic->setValue(data.c_str());
  pCharacteristic->notify();

  // Display angles in Serial Monitor
  Serial.print("Roll: "); Serial.print(roll);
  Serial.print(" Pitch: "); Serial.print(pitch);
  Serial.print(" Yaw: "); Serial.println(yaw);

  delay(100); // Update at 10Hz
}

// Implement BLE server callbacks if needed
class BLEServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  }

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};
