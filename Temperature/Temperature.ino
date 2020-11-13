#include <dht11.h>
#define DHT11PIN 4
#define TO_HEX(i) (i <= 9 ? '0' + i : 'A' - 10 + i)
dht11 DHT11;

#include <SoftwareSerial.h>
SoftwareSerial hc06(0,1);
String cmd="";
byte command[4];
//char[] response = {00h,00h,00h,00h};
void setup()
{
  Serial.begin(9600);
  hc06.begin(9600);
}

void loop()
{
  //Serial.println();

  int chk = DHT11.read(DHT11PIN);

  //Serial.print("Humidity (%): ");
  //Serial.println((float)DHT11.humidity, 2);

  //Serial.print("Temperature (C): ");
  //Serial.println((float)DHT11.temperature, 2);
  //Serial.println(hc06.available());
  /*while(hc06.available()>0){
    cmd+=(char)hc06.read();
  }
  Serial.println(cmd);  
  */
  int i=0;
  while(hc06.available() > 0){
    command[i] = hc06.read();
    i++;
  }
  /*Serial.print(command[0]);
  Serial.print(" ");
  Serial.print(command[1]);
  Serial.print(" ");
  Serial.print(command[2]);
  Serial.print(" ");
  Serial.println(command[3]);*/
  int n = DHT11.temperature;
  byte value[5];
  /*value[0] = 0x41;
  value[1] = 0x05;
  value[2] = (n >> 24) & 0xFF;
  value[3] = (n >> 16) & 0xFF;
*/


  value[0] = 0x41;//as hex
  value[1] = 0x05;//as hex
  value[2] = (n >> 8) & 0xFFF; //as byte
  value[3] = n & 0xFF; //as byte
  value[4] = 0x3E;
 // Serial.print("Response: ");
  //Serial.println(value);
  for(int i = 0; i < 5; i++){
    Serial.write(value[i]);
  }



  
  //if(cmd[0] == )
  /*if(cmd == "OBD"){
    Serial.println((float)DHT11.temperature,2);
  }*/
  /*if(cmd == "0105"){
    Serial.write(""); buffer.get(2) - 40;
  }*/
  cmd = "";
  delay(1000);

}
