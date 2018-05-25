/////////
#define soilhumsetpoint 70  //soil humidity setpoint (if real value is lower a relay closes its contacts in order to turn on a water valve)
#define DHT11Pin 2
#define igrometerPin 8
////////

#include <Servo.h>  
#include <SimpleDHT.h> 
SimpleDHT11 dht11; //declaring a DHT11 object that will be used to read air humidity and temperature
Servo myServo; //declaring a Servo object that will be used to position the plant in order to follow the sun
String data=""; //string that will store the sensor name and the value in this format sensor<number>-<value>
int val=0; //value of the current sensor

//variables of the sensors
int light1;
int light2;
int light3;
int temper;
int humsoil;
int humair;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); //enabling Serial communication
  pinMode(igrometerPin,OUTPUT); //
  digitalWrite(igrometerPin,LOW);
  myServo.attach(9);
  myServo.write(0);
  pinMode(12,OUTPUT); //relay pin 12
  digitalWrite(12,LOW);
}

void loop() {

  //LIGHT   //READING LIGHT SENSORS VALUE AND SENDING THEM
  val = analogRead(A0);  //reading value
  light1=val;   //storing value
  data= "sensor1-" + (String) val; //building-up of the dataString
  Serial.println(data); //sending dataString
  //Serial.println(light1); //debug purposes
  delay(100);  //sampling time
  val = analogRead(A1);
  light2=val;
  data= "sensor2-" + (String) val;
  Serial.println(data);
  //Serial.println(light2);
  delay(100);
  val = analogRead(A2);
  light3=val;
  data= "sensor3-" + (String) val;
  Serial.println(data);
  //Serial.println(light3);
  delay(100);
  //END LIGHT
  
  ///////////DHT11///////////////////////
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(DHT11Pin, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(100);
    return;
  }
  val = temperature;
  temper = val;
  data= "sensor4-" + (String) val;
  Serial.println(data);
  //Serial.println(temper);
  delay(100);

  val = humidity;
  humair=val;
  
  data= "sensor5-" + (String) val;
  Serial.println(data);
  //Serial.println(humair);
  delay(100);
  /////////////////////END DHT 11


  //READING AND SENDING SOIL HUMIDITY VALUES

  digitalWrite(8,HIGH);
  delay(100);
  val= analogRead(A5);
  val = map(val,400,1023,100,0); // experimental values, they may change in you project
  humsoil = val;
  digitalWrite(8,LOW);
  data="sensor6-" + (String) val;
  Serial.println(data);
  //Serial.println(humsoil);
  delay(100);
  //////////////////////////////////

  ////SERVO CONTROL//////// LIGHT FOLLOWING FEATURE 

  if(light1<light2&&light1<light3){
     myServo.write(0);    
    
    }else if(light2<light1&&light2<light3){
        myServo.write(90);
            }else if(light3<light1&&light3<light2){
              myServo.write(180);
              }else{
                myServo.write(0);
                }
  
   

  ///VALVE CONTROL//////

  if(humsoil<soilhumsetpoint){  
    
      digitalWrite(12,HIGH);
    }else{
      
      digitalWrite(12,LOW);
      }

  
  
}
