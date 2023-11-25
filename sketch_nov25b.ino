#include <TimerOne.h>
int temp;
int Status = HIGH;
int bit_1=LOW;
int bit_2=LOW;


void setup() {
  Timer1.initialize(250000); // Creating timer interrupt for every 250ms
  Timer1.attachInterrupt(Toggle_LED); // Executing this fucntion for every 250ms
  pinMode( 13, OUTPUT);
  Serial.begin(9600);
}

void loop() {

}

void Toggle_LED(){
  temp=analogRead(A0)*4.88/10; // we are converting ADC value to mV and LM35 has 10mv/C variation
  Serial.println(temp);
  if(temp<30){
    Status = !Status; // Changing status of inbuilt LED from HIGH to LOW or LOW to HIGH
    digitalWrite(13, Status); 
  }
  else{
    /*
    ->We are creating interrput of only 250ms but we are supposed to change the LED status for every 500ms.
    ->For temp < 30, LED status is 1 (High) or 0 (LOW) i.e, two bits.
    ->We are assigning bit_1 as 1st bit and bit_2 as 2nd bit.
    ->For temp > 30, we are assigning the bit_1 as LED status, 00,01 has LOW and 10,11 has HIGH.Thus, it takes two cycles (250ms+ 250ms) to change the status of LED.
    */
    digitalWrite(13, bit_1); // 
    if(bit_2==HIGH){
      bit_1=!bit_1;
    }
    bit_2=!bit_2;
  }
}