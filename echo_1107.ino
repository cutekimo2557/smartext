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

bool firedetection = false;  //화재 발생 변수를 설정, 기본값 false

RF24 radio(CEPIN, CSNPIN); // CE, CSN 핀 설정
//const byte address[6] = "00001";

//화재 감지 여부를 전달하는 함수
bool DETERMINATION_FIRED(float DETECTION_FREQ, short SET_CRITICAL_POINT){
  #define LEVELPORT A0
  while (true){
    if (analogRead(LEVELPORT) >= SET_CRITICAL_POINT){return true;}else {return false;}
    delay(DETECTION_FREQ);}}


void setup(){
  radio.begin();
  radio.openWritingPipe(ADDRESS);
  radio.setPALevel(RF24_PA_MIN);  //전송 전력 설정(RF24_PA_LOW of HIGH)
  radio.stopListening();  //모듈을 송신기 상태로 설정한다.
  pinMode(13, OUTPUT);
}

void loop(){
  //const char text[] = "(From) nRF24 Tx: Hello World!";
  //bool firedetection = DETERMINATION_FIRED(2000, 600);

  //if(!firedetection == false){}
  radio.write(&firedetection, sizeof(firedetection));
  delay(1000);
  digitalWrite(13, LOW);  
}