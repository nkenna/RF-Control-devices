#include <VirtualWire.h>

const int RF_TX_PIN = 8;
const int pinLed_ON_OFF = 2;
const int pinRelay_ON_OFF = 3;
int pinLed = 4;

char payload[6] = "";

int led_on_off_Value = 0;
int relay_on_off_Value = 0; 

void setup() {
  // put your setup code here, to run once:
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(RF_TX_PIN);
  vw_setup(2000);

  pinMode(pinLed_ON_OFF, INPUT);
  pinMode(pinRelay_ON_OFF, INPUT);
  pinMode(pinLed, OUTPUT);
  Serial.begin(9600);

 
}

void loop() {
  // put your main code here, to run repeatedly:
  led_on_off_Value = digitalRead(pinLed_ON_OFF);
  relay_on_off_Value = digitalRead(pinRelay_ON_OFF);

  if(led_on_off_Value == HIGH){
    digitalWrite(pinLed, led_on_off_Value);
    strcpy(payload, "@ABC$");

    if(strlen(payload) > 0){
      sendPayload(payload);
      }
  
    digitalWrite(pinLed, LOW);
  }

 

   if(relay_on_off_Value == HIGH){
    digitalWrite(pinLed, relay_on_off_Value);
    strcpy(payload, "@FON$");
    
    if(strlen(payload) > 0){
      sendPayload(payload);
      }
   digitalWrite(pinLed, LOW);
    
  }
  

 strcpy(payload, "");
 resetLoads();

}

void sendPayload(char payload[]){
  vw_send((uint8_t *)payload, strlen(payload));
  Serial.println(payload);
  vw_wait_tx();
  delay(400);
}

void resetLoads(){
  led_on_off_Value = 0;
  relay_on_off_Value = 0;
}

