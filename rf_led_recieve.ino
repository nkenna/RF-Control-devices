#include <VirtualWire.h>
const int RF_RX_PIN = 11;


int relayPin = 4; //attach relay to pin D4
int ledPin = 5; //attach relay to pin D5
int errorLED = 13;

boolean led = false;
boolean relay = false;
boolean ledState = true;

void setup() {
  // put your setup code here, to run once:
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(RF_RX_PIN);
  vw_setup(2000);
  vw_rx_start();

  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(errorLED, OUTPUT);

  relay = false;
  led = false;
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t buf [VW_MAX_MESSAGE_LEN];
  uint8_t buflen = VW_MAX_MESSAGE_LEN;
  
  if(vw_get_message(buf, &buflen))  { 
    delay(500); 
    Serial.println((char *) buf);
    payloadDecode ( (char *) buf); 
    delay(500);   
    } 

    if(led == true)  { 
      
        ledState = !ledState;
        Serial.println(led);
        digitalWrite(ledPin, led);
     
//      if (digitalRead(ledPin) == LOW ){
//        digitalWrite(ledPin, HIGH);
//      }
      
      }else{
        digitalWrite(ledPin, led);
      }


      if(relay == true){
        Serial.println(relay);
        digitalWrite(relayPin, relay);
      }else{
        Serial.println(relay);
        digitalWrite(relayPin, relay);
      }

      
      
//if(led == false)  { 
//  digitalWrite(ledPin, LOW);
//  }
  
if(relay == true)  { 
  digitalWrite(relayPin, HIGH);
  }
  
if(relay == false)  { 
  digitalWrite(relayPin, LOW);
  }

  delay(400);
}


void payloadDecode(char msg[]) { 
  if (strlen(msg) == 0)   { 
    
    ErrorLED(); 
    return;
    }
      
if ( compareMessage(msg, '@') == false || compareMessage(msg, '$') == false)  { 
  //Serial.println(msg);
  ErrorLED(); 
  return;
  }
    
char cTag[5] =""; 
int index =0; 
int iLoop = IndexOf(msg,'@');

if(iLoop == -1) { 
  //Serial.println(msg);
  ErrorLED(); 
  return; 
  }
  
 iLoop++;

while (iLoop < strlen(msg)) {
  
  if(msg[iLoop] == '$')   { 
    break;   
    } else   {
      cTag[index] = msg[iLoop]; 
    //  Serial.println(msg);
      index++;

 }
   iLoop ++; 
   }
   
 String sTag = String(cTag);

if (sTag.equals("ABC"))   {
  //Serial.println(msg);
  led = !led;   
  }
  
if (sTag.equals("BOFF"))   {
  //Serial.println(msg);
  led = false; 
  }
  
if (sTag.equals("FON"))   { 
  //Serial.println(msg);    
  relay = !relay;   
  }
  
if (sTag.equals("FOFF"))   {   
  //Serial.println(msg);  
  relay = false;   
  }
   
}

int IndexOf(char msg[], char tag) { 
  if (strlen(msg) ==0) {
    return false;
  }
    
    boolean bFlag = false; 
    int iIndex = -1;
    
for( int i=0; i<strlen(msg); i++)  { 
  if(msg[i]== tag)    
    iIndex = i;
    }

return iIndex;
}


boolean compareMessage (char msg[], char tag) { 
  if (strlen(msg) ==0){
    return false;  
  }
  
  boolean bFlag = false;

//Serial.println(msg);

for( int i=0; i<strlen(msg); i++)  { 
  if(msg[i]== tag)    
  bFlag = true;  
  }
  
return bFlag;
}



void ErrorLED() {
  digitalWrite(errorLED, HIGH); 
  delay(500); 
  digitalWrite(errorLED, LOW);
}

