#include "CTBot.h"
CTBot myBot;
 
String ssid  = "SAMSUANG"; 
String pass  = "YAMAHAVEGA"; 
String token = "1796393369:AAHSjVVzwJzBCzzglz8k_vzhyeJGRGdtU2o";
 
const int lampu = 2;  
const int buzzer = 4;                        
 
void setup() {
  // initialize the Serial
  Serial.begin(115200);
  Serial.println("Starting TelegramBot...");
 
  // connect the ESP8266 to the desired access point
  myBot.wifiConnect(ssid, pass);
 
  // set the telegram bot token
  myBot.setTelegramToken(token);
 
  // check if all things are ok
  if (myBot.testConnection())
    Serial.println("\ntestConnection OK");
  else
    Serial.println("\ntestConnection NOK");
 
  // set the pin connected to the LED to act as output pin
  pinMode(lampu, OUTPUT);
  digitalWrite(lampu, HIGH); // turn off the led (inverted logic!)
 
}
 
void loop() {
     
  // a variable to store telegram message data
  TBMessage msg;
 
  // if there is an incoming message...
  if (myBot.getNewMessage(msg)) {
    if (msg.text.equalsIgnoreCase("motor aman")) {                   //Perintah dari telegram ke perangkat
      digitalWrite(lampu, HIGH);                              //Lampi dihidupkan
      myBot.sendMessage(msg.sender.id, "motor aman"); //Balasan dari perangkat ke Bot Telegram
    }
    else if (msg.text.equalsIgnoreCase("motor dibegal")) {              //Perintah dari telegram ke perangkat
      digitalWrite(lampu, LOW ); //kontak mati
      digitalWrite(buzzer, HIGH); //buzzer nyala
      myBot.sendMessage(msg.sender.id, "motor sudah di matikan dan buzzer menyala"); //Balasan dari perangkat ke Bot Telegram
    }
    else if (msg.text.equalsIgnoreCase("matikan motor")) {              //Perintah dari telegram ke perangkat
      digitalWrite(lampu, LOW );                              //motor di matikan
      myBot.sendMessage(msg.sender.id, "motor sudah di matikan"); //Balasan dari perangkat ke Bot Telegram
    }
    else {                                                    // otherwise...
      // generate the message for the sender
      String reply;
      reply = (String)"maaf" + msg.sender.username + (String)"perintah tidak tersedia";
      myBot.sendMessage(msg.sender.id, reply);             // and send it
    }
   
  }
  // wait 500 milliseconds
  delay(500);
}
