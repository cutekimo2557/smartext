#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//NRF24와 연결할 핀을 연결할 코드이다.
//9번 핀은 CE, 10번 핀은 CSN, 11번 핀은 MOSI, 12번 핀은 MISO, 13번 핀은 SCK
//NRF 모듈이 외부 간섭으로 부터 신호가 불안정할 경우 VCC, GND에 10uF 연결

#define CEPIN 9
#define CSNPIN 10

//ADDRESS는 NRF 모듈의 통신 주소이다. 송 수신 모두 동일한 값이어야함.
#define ADDRESS 0xF0F0F0E1LL

RF24 radio(CEPIN, CSNPIN); // CE, CSN 핀 설정
//const byte address[6] = "00001";

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, ADDRESS);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening(); //모듈을 수신기 상태로 설정한다.
}

void loop(){
  if(radio.available()){
    //char text[32] = "";
    //radio.read(&text, sizeof(text));
    //Serial.println(text);
    bool firedetection = false;
    radio.read(&firedetection, sizeof(firedetection));
    Serial.println(firedetection);
    delay(1000);
  }
}