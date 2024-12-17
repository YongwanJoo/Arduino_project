#include <Servo.h>//서보 라이브러리 사용
//변수 선언
int FirstSensor = 3;
const int on_off = 4;
int right_pirState = LOW;//오른쪽 센서 초기값 설정
int ENA = 5;
int ENB = 6;
int INA1 = 7;
int INA2 = 8;
int INB3 = 9;
int INB4 = 10;
int servo = 11;
int led = 12;
int res1 = 0;//오른쪽 센서 감지시 초기값 설정
int angle = 0;//서보모터 각도 초기값 설정
int SecondSensor = 13;
int left_pirState = LOW;//왼쪽 센서 초기값 설정
int res2 = 0;//왼쪽 센서 감지시 초기값 설정
Servo myservo;//서보 이름 설정
//버튼 스위치의 정보 저장을 위한 변수 선언 밑 초기값 설정
int val = 0;
int old_val = 0;
int state = 0;

void setup(){
  //입력과 출력 설정
  pinMode(on_off, INPUT);
  pinMode(ENA, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(INB3, OUTPUT);
  pinMode(INB4, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(FirstSensor, INPUT);
  pinMode(SecondSensor, INPUT);
  //센서 감지 확인을 위한 시리얼 모니터 사용
  Serial.begin(9600);
  //서보모터 사용
  myservo.attach(servo);
}
void loop(){
  //변수에 입력신호 저장
  val = digitalRead(on_off);
  res1 = digitalRead(FirstSensor);
  res2 = digitalRead(SecondSensor);

  //버튼 정보 저장
  if((val == HIGH)&&(old_val == LOW)){
    state = 1 - state;
    delay(50); 
  }
  //스위치 유지를 위해 이전 값 저장
  old_val = val;
  //스위치가 켜져있을 시
  if(state == 1){
    if(res1 == HIGH && res2 == LOW){//오른쪽 센서 인식 시
      for(angle = 0; angle < 180; angle = angle + 10){
        myservo.write(angle);
        delay(5);
      }
      for(angle = 180; angle > 0; angle = angle - 10){
        myservo.write(angle);
        delay(5);
      }
     digitalWrite(led, HIGH);
     //오른쪽으로 움직이기 위해 움직일 모터 정하고 한 쪽 방향으로만 설정
     analogWrite(ENA, 255);
     digitalWrite(INA1, LOW);
     digitalWrite(INA2, HIGH);
     digitalWrite(INB3, LOW);
     digitalWrite(INB4, LOW);
     Serial.println("First");//시리얼 통신을 통한 코드 동작 확인

    }
    else if(res1 == LOW && res2 == HIGH){
      for(angle = 0; angle < 180; angle = angle + 10){
        myservo.write(angle);
        delay(5);
      }
      for(angle = 180; angle > 0; angle = angle - 10){
        myservo.write(angle);
        delay(5);
      }
      digitalWrite(led, HIGH);
      
      analogWrite(ENB, 255);
      digitalWrite(INA1, LOW);
      digitalWrite(INA2, LOW);
      digitalWrite(INB3, HIGH);
      digitalWrite(INB4, LOW);
      Serial.println("Second");

    }
    else if(res1 == HIGH && res2 == HIGH){
      for(angle = 0; angle < 180; angle = angle + 10){
        myservo.write(angle);
        delay(5);
      }
      for(angle = 180; angle > 0; angle = angle - 10){
        myservo.write(angle);
        delay(5);
      }
      digitalWrite(led, HIGH);
      
      analogWrite(ENB, 255);
      digitalWrite(INA1, LOW);
      digitalWrite(INA2, HIGH);
      digitalWrite(INB3, HIGH);
      digitalWrite(INB4, LOW);
      Serial.println("Both");

    }
  }
  else{
    res1 = LOW;
    res2 = LOW;
    angle = 0;
    myservo.write(angle);
    digitalWrite(led, LOW);

    analogWrite(ENA,0);
    analogWrite(ENB,0);   
    digitalWrite(INA1, LOW);
    digitalWrite(INA2, LOW);
    digitalWrite(INB3, LOW);
    digitalWrite(INB4, LOW);

  }
}
