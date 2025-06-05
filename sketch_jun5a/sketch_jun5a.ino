#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

BLECharacteristic* pCharacteristic;

// BLE 데이터 수신 콜백
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic) {
    std::string value = std::string((char*)pCharacteristic->getData(), pCharacteristic->getLength());

    if (value.length() > 0) {
      Serial.print("📡 수신: ");
      Serial.println(value.c_str());

      // 여기에 명령 분기 처리
      if (value == "U") {
        Serial.println("↑ 앞으로 이동");
      } else if (value == "D") {
        Serial.println("↓ 뒤로 이동");
      } else if (value == "L") {
        Serial.println("← 좌회전");
      } else if (value == "R") {
        Serial.println("→ 우회전");
      } else if (value == "X") {
        Serial.println("✖ X 버튼");
      } else if (value == "O") {
        Serial.println("◯ O 버튼");
      }
      // 기타 필요한 처리 추가
    }
  }
};

// BLE 연결/해제 콜백
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("📲 BLE 연결됨");
  }

  void onDisconnect(BLEServer* pServer) {
    Serial.println("🔌 BLE 연결 끊김");
  }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init("ESP32_JOYSTICK");
  BLEServer* pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  // 표준 SPP 호환 UUID 사용 (많은 BLE 앱과 호환)
  BLEService* pService = pServer->createService(BLEUUID((uint16_t)0xFFE0));

  pCharacteristic = pService->createCharacteristic(
    BLEUUID((uint16_t)0xFFE1),
    BLECharacteristic::PROPERTY_WRITE
  );

  pCharacteristic->setCallbacks(new MyCallbacks());
  pService->start();
  pServer->getAdvertising()->start();

  Serial.println("✅ BLE Joystick Receiver Started");
}

void loop() {
  // 실시간 제어는 콜백 안에서 처리됨
}
