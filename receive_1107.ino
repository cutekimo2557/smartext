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


//상태를 변경하는 간격들을 나타내는 변수들, 함수들 안에서 선언될 예정.(ms 단위로 작성하도록)
//const unsigned long led_interval = 1000;
//const unsigned long speaker_interval = 1000;
//const unsigned long nRF_interval = 1000;


//화재 감지기로부터 화재 감지 여부를 전달받는 함수
bool RECEIVE_ALERT(float RECEIVE_FREQ){
  if(radio.available()){
    bool firedetection = false;
    radio.read(&firedetection, sizeof(firedetection));
    Serial.println(firedetection);
    delay(RECEIVE_FREQ);
    return firedetection;
  }
}

//소화기 받침대의 스피커를 작동하는 함수(기본값은 테스트 레벨로)
void SPEAKER(float DELAY_MILIS_SPEAKER, bool ARAM_SWITCH, bool ISTEST = true){
  #define LOW_LEVEL 0
  #define TEST_LEVEL 128
  #define ALERT_LEVEL 255
  #define ARAM_OUTPUT_PIN 5

  //주의: delay() 함수를 사용하는 것은 재고해 볼 필요가 있음.
  /*if(ISTEST == true){
    do{
      analogWrite(ARAM_OUTPUT_PIN, TEST_LEVEL);
      delay(DELAY_MILIS_SPEAKER);
      analogWrite(ARAM_OUTPUT_PIN, LOW_LEVEL);
      delay(DELAY_MILIS_SPEAKER);
    }while((ARAM_SWITCH == false));}
  else{
    do{
      analogWrite(ARAM_OUTPUT_PIN, TEST_LEVEL);
      delay(DELAY_MILIS_SPEAKER);
      analogWrite(ARAM_OUTPUT_PIN, LOW_LEVEL);
      delay(DELAY_MILIS_SPEAKER);
    }while(ARAM_SWITCH == false);}*/
}

//소화기 받침대의 LED를 작동하는 함수
void BLINK_LED(float BLINK_FREQ, long DELAY_MILIS_LED, bool LED_SWITCH){
  #define LED_OUTPUT_PIN 6

  const unsigned long led_interval = DELAY_MILIS_LED;
  static long prev_milis = 0;
  const unsigned long curr_milis = millis();

    if ((curr_milis - prev_milis >= led_interval)) {
    prev_milis = curr_milis;
    digitalWrite(LED_OUTPUT_PIN, !digitalRead(LED_OUTPUT_PIN));}

  //주의: delay() 함수를 사용하는 것은 재고해 볼 필요가 있음.
  /*do{
    digitalWrite(LED_OUTPUT_PIN, HIGH);
    delay(DELAY_MILIS_LED);
    digitalWrite(LED_OUTPUT_PIN, LOW);
    delay(DELAY_MILIS_LED);
  }while(LED_SWITCH == false);    */
}

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, ADDRESS);
  radio.setPALevel(RF24_PA_MIN);
  //모듈을 수신기 상태로 설정한다.
  radio.startListening(); 
}

void loop(){
}