#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CEPIN 9
#define CSNPIN 10
#define ADDRESS 0xF0F0F0E1LL

RF24 radio(CEPIN, CSNPIN);

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, ADDRESS);
  radio.setPALevel(RF24_PA_MAX);
  radio.startListening();
  pinMode(A0, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  static unsigned long lastBlinkTime = 0;
  static bool fireDetected = false;

  if (radio.available()) {
    bool currentFireState;
    radio.read(&currentFireState, sizeof(currentFireState));
    Serial.println(currentFireState);

    // 불이 감지되면 상태를 업데이트하고 깜빡거릴 시간을 초기화
    if (currentFireState) {
      fireDetected = true;
      lastBlinkTime = millis();
    }
  }

  //최근 10초 동안 한 번이라도 True 신호가 감지되면 실행되는 코드임.
  if (fireDetected && (millis() - lastBlinkTime <= 10000)) {
 
    if ((millis() - lastBlinkTime) % 600 < 500) {
      digitalWrite(8, HIGH);  
    } else {
      digitalWrite(8, LOW);   
    }
  } else {

    digitalWrite(8, HIGH);
    fireDetected = false;  
  }

  delay(100); 
}