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

//화재 감지 여부를 전달하는 함수
bool DETERMINATION_FIRED(float DETECTION_FREQ, short SET_CRITICAL_POINT){
  #define LEVELPORT A0

  static unsigned long echo_previousMillis = 0;
  const unsigned long echo_delaymillis = DETECTION_FREQ;
  bool DET_FIRED = false;

  unsigned long echo_currmillis = millis();
  if(echo_currmillis - echo_previousMillis >= echo_delaymillis){echo_previousMillis = echo_currmillis;
    if(analogRead(LEVELPORT) >= SET_CRITICAL_POINT){DET_FIRED = true;}else DET_FIRED = false;return DET_FIRED;}}

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(ADDRESS);
  radio.setPALevel(RF24_PA_MAX);  //전송 전력 설정(RF24_PA_LOW of HIGH)
  radio.stopListening();  //모듈을 송신기 상태로 설정한다.

  pinMode(LEVELPORT, OUTPUT);
}

void loop(){
  
  bool firedetection = DETERMINATION_FIRED(100, 300);  //화재 발생 변수를 설정, 기본값 false
  Serial.println(firedetection);
  radio.write(&firedetection, sizeof(firedetection));
  delay(300);
  }