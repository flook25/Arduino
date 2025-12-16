#include <SparkFun_VL6180X.h>
#include <Wire.h>

#define VL6180X_ADDRESS 0x29
#define NEWVL6180X_ADDRESS 0x30

int enable4 = 4;
int enable5 = 5;

VL6180xIdentification identification;

VL6180x sensor2(VL6180X_ADDRESS);
VL6180x sensor1(VL6180X_ADDRESS);

void setup() {


  pinMode (enable4, OUTPUT);
  pinMode (enable5, OUTPUT);
  
  Serial.begin(9600);
  Wire.begin();
  delay(1000);
  
//  digitalWrite(enable2, HIGH);
//  digitalWrite(enable3, LOW);

  digitalWrite(enable4, HIGH);
  digitalWrite(enable5, LOW);
  
  sensor1.getIdentification(&identification);

 if(sensor1.VL6180xInit() != 0)
 {
    Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
 }
  sensor1.VL6180xDefautSettings();
  delay(1000);
  sensor1.changeAddress(VL6180X_ADDRESS,NEWVL6180X_ADDRESS); 
    
  digitalWrite(enable5,HIGH);  
  sensor2.getIdentification(&identification);
  if(sensor2.VL6180xInit() != 0)
  {
    Serial.println("FAILED TO INITALIZE Sensor 2"); //Initialize device and check for errors
  }
  sensor2.VL6180xDefautSettings(); //Load default settings to get started.
    
  delay(1000); // delay 1s  
  sensor2.changeAddress(VL6180X_ADDRESS,NEWVL6180X_ADDRESS2);  
  
}

void loop() 
{

//Get Distance and report in mm

    String str;
    //uint8_t

//  Serial.print("Distance measured sensor 1(mm) = "); 
//  Serial.println(sensor1.getDistance());
//  Serial.print("Distance measured sensor 2(mm) = "); 
//  Serial.println(sensor2.getDistance());
//  Serial.print("Distance measured sensor 3(mm) = "); 
//  Serial.println(sensor3.getDistance()); 
//  Serial.print("Distance measured sensor 4(mm) = "); 
//  Serial.println(sensor4.getDistance()); 
//  delay(50); 

//String myString = String(myByteArray);
    str = "#"+ String(sensor1.getDistance())+ "*"+ String(sensor2.getDistance())+ "*" + String(sensor3.getDistance())+ "*" + String(sensor4.getDistance());
    Serial.println(str); 

  
}
