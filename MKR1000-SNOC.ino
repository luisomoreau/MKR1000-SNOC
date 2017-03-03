/*
 * Author: Louis Moreau: https://github.com/luisomoreau
 * Date: 2017/03/03
 * Description:
 * This arduino example will show you how to send a Sigfox message 
 * using the wisol module and the MKR1000 (https://yadom.fr/carte-breakout-sfm10r1.html)
*/


//Set to 0 if you don't need to see the messages in the console
#define DEBUG 1 

//Message buffer
uint8_t msg[12];

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  if(DEBUG){
    Serial.begin(9600);
  }
  
  // open Wisol communication
  Serial1.begin(9600);
  delay(100);
  getID();
  delay(100);
  getPAC();
}

// the loop function runs over and over again forever
void loop() {
  msg[0]=0xCA;
  msg[1]=0xFE;
  sendMessage(msg);
  delay(10*60*1000);
}

void blink(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);    
}

//Get Sigfox ID
String getID(){
  String id = "";
  char output;
  
  Serial1.print("AT$I=10\r");
  while (!Serial1.available()){
     blink();
  }
  
  while(Serial1.available()){
    output = Serial1.read();
    id += output;
    delay(10);
  }
  
  if(DEBUG){
    Serial.println("Sigfox Device ID: ");
    Serial.println(id);
  }
  
  return id;
}


//Get PAC number
String getPAC(){
  String pac = "";
  char output;
  
  Serial1.print("AT$I=11\r");
  while (!Serial1.available()){
     blink();
  }
  
  while(Serial1.available()){
    output = Serial1.read();
    pac += output;
    delay(10);
  }
  
  if(DEBUG){
    Serial.println("PAC number: ");
    Serial.println(pac);
  }
  
  return pac;
}


//Send Sigfox Message
void sendMessage(uint8_t msg[]){

  String status = "";
  char output;

  Serial1.print("AT$SF=");
  for(int i= 0;i<sizeof(msg);i++){
    Serial1.print(String(msg[i], HEX));
  }
  
  Serial1.print("\r");

  while (!Serial1.available()){
     blink();
  }
  while(Serial1.available()){
    output = (char)Serial1.read();
    status += output;
    delay(10);
  }
  if(DEBUG){
    Serial.println();
    Serial.print("Status \t");
    Serial.println(status);
  }
}

