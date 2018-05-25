import processing.serial.*;
Serial myPort; //declaration of Serial Port 

public static String data = ""; //string in which is stored the value of the sensor that we are reading
public static char topic = ' '; //char in which is stored the number of the topic where we have to send the sensor value
import mqtt.*;
public static String lastData;
MQTTClient client;

void setup() {
  
  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
  myPort = new Serial(this, portName, 9600);
  myPort.bufferUntil('\n');  //this is used to buffer the char received via serial in order to build a proper readable string
  client = new MQTTClient(this);
  client.connect("mqtt://8cabd9bb:22b0690c80529823@broker.shiftr.io", "homeClient");  // ( broker namespace token, clientName) (see more shiftr.io and how it works in the README)
  
  // client.unsubscribe("/example"); to subscribe in order to receive messages from mqtt
 
  
}

void draw() {
    delay(100);//sampling time (same as arduino sketch time)
    
    
  switch(topic){ //switch function used to send datas in the proper topic
    
    case '1':
    client.publish("/data/telegram/light/sensor-1",data);
    break;
    
    case '2':
    client.publish("/data/telegram/light/sensor-2",data);
    break;
    
    case '3':
    client.publish("/data/telegram/light/sensor-3",data);
    break;
    
    case '4':
    client.publish("/data/telegram/temperature",data);
    break;
    
    case '5':
    client.publish("/data/telegram/humidity/air",data);
    break;
    
    case '6':
    client.publish("/data/telegram/humidity/soil",data);
    break;
    
    
    
  
  
  
  }
  
  
}



  void serialEvent(Serial p) { //method called when a serial string is received
  String inString = p.readString();  //received string, format : sensor<number>-<data>
  topic = inString.toCharArray()[6]; //in this way we can read <number> and use it to recognize the proper topic
  data = inString.substring(8); //in this way we can read the data to send in the topic labeled with <number> 
    
}


void messageReceived(String topic, byte[] payload) { //method called when a String is received from MQTT
  println("new message: " + topic + " - " + new String(payload));
  lastData= new String(payload);
   
}
