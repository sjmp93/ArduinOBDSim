#include <dht11.h>
#include <SoftwareSerial.h>

#define DHT11PIN 4
#define showReceivedCommand  false // Determines if the Arduino serial monitor prints the received request command
#define timeBetweenRequests 1000 //In milliseconds
dht11 DHT11;

SoftwareSerial hc06(0,1);
String cmd="";
int command[12];
char commandChar[12];

void setup()
{
  Serial.begin(9600);
  hc06.begin(9600);
}

// Receives an OBD request command and responses to that request using HC06 Bluetooth module -- PID table https://es.wikipedia.org/wiki/OBD-II_PID
void loop()
{

  int chk = DHT11.read(DHT11PIN);
  int i=0;
  while(hc06.available() > 0){
    command[i] = hc06.read();
    i++;
  }
  for(int j = 0; j < i; j++){
    commandChar[j] = command[j];
  }
  //Use this to debug received commands from Android device  
  if(showReceivedCommand){
    Serial.print("int: ");
    for(int j = 0; j < i; j++){
      Serial.print(command[j]);
      Serial.print(" ");
    }
    Serial.println();
    Serial.print("ascii: ");        //Print received command
    for(int j = 0; j < i; j++){
      Serial.print(commandChar[j]);
      Serial.print(" ");
    }
    Serial.println();
  }
  
  int n = DHT11.temperature; //We use temp readings to simulate OBD values
  //int m = DHT11.humidity;
  byte value[5];
  //ELM send arrays of strings, so we have to Serial.print the response like the following example for 20ºC engine coolant: 41 05 00 3C
  //See PID table https://es.wikipedia.org/wiki/OBD-II_PID 
  if(i == 6){ /* Command received has 6 fields (XX XX/n) where X belongs to Int scope, " " is space and "/n" is carriage return
                                                ^^^^^ ^
                                               (12345 6) */
    // This loop simulates a response to the request command received
    for(int j = 0; j < i - 1; j++){
      if(j == 0){
        Serial.print("4");
      }else{
        Serial.print(commandChar[j]);
      }
    }
    value[2] = (n >> 8) & 0xFFF; //as byte
    value[3] = (n & 0xFF); //as byte
  
    Serial.print(" 0");
    Serial.print(value[2], HEX);
    Serial.print(" ");
    Serial.print(value[3] + 0x28, HEX);
                          //Serial.print(" ");
    Serial.println(cmd+" >");  
  }else{ // dummy response to continue execution on the Android side (it is waiting for any response)
    Serial.println(cmd+"00 00 00 00 >");
  }
  delay(timeBetweenRequests);
}
