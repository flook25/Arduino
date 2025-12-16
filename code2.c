#include <SparkFun_VL6180X.h>
#include <Wire.h>

// --- I2C ADDRESS DEFINITIONS ---
#define VL6180X_ADDRESS 0x29          // The default I2C address for all VL6180X sensors
#define SENSOR1_NEW_ADDRESS 0x30      // The new unique address for Sensor 1
#define SENSOR2_NEW_ADDRESS 0x31      // The new unique address for Sensor 2

// --- ARDUINO PIN DEFINITIONS ---
// Assuming 'enable4' controls the XSHUT pin of Sensor 1
// Assuming 'enable5' controls the XSHUT pin of Sensor 2
// The XSHUT pin is active LOW. Setting it LOW puts the sensor in reset.
int SENSOR1_XSHUT = 4;
int SENSOR2_XSHUT = 5;

// --- SENSOR OBJECT DECLARATION ---
// Initialize both sensor objects using the default address (0x29)
// The correct address will be assigned in setup()
VL6180x sensor1(VL6180X_ADDRESS);
VL6180x sensor2(VL6180X_ADDRESS);

VL6180xIdentification identification;

void setup() {
  
  // Set XSHUT pins as outputs
  pinMode (SENSOR1_XSHUT, OUTPUT);
  pinMode (SENSOR2_XSHUT, OUTPUT);
  
  // Start Serial communication
  Serial.begin(9600);
  Wire.begin();
  delay(100); 

  Serial.println("Starting VL6180X Dual Sensor Initialization...");
  
  // --- 1. Isolate and Configure Sensor 1 ---
  // Hold Sensor 2 in reset (LOW) and enable Sensor 1 (HIGH)
  digitalWrite(SENSOR1_XSHUT, HIGH); 
  digitalWrite(SENSOR2_XSHUT, LOW);
  delay(100); 

  // Initialize Sensor 1 (it is the only one active at 0x29)
  if(sensor1.VL6180xInit() != 0) {
    Serial.println("FAILED TO INITALIZE Sensor 1 at 0x29"); 
    while(1); // Halt
  }
  sensor1.VL6180xDefautSettings();
  
  // Change Sensor 1's address to 0x30 so it ignores subsequent 0x29 communication
  sensor1.changeAddress(VL6180X_ADDRESS, SENSOR1_NEW_ADDRESS); 
  Serial.print("Sensor 1 re-addressed to: 0x");
  Serial.println(SENSOR1_NEW_ADDRESS, HEX); 

  // --- 2. Isolate and Configure Sensor 2 ---
  // Hold Sensor 1 in reset (LOW)
  digitalWrite(SENSOR1_XSHUT, LOW);
  // Enable Sensor 2 (HIGH)
  digitalWrite(SENSOR2_XSHUT, HIGH); 
  delay(100); 

  // Initialize Sensor 2 (it is now the only one active at 0x29)
  if(sensor2.VL6180xInit() != 0) {
    Serial.println("FAILED TO INITALIZE Sensor 2 at 0x29");
    while(1); // Halt
  }
  sensor2.VL6180xDefautSettings(); 

  // Change Sensor 2's address to 0x31
  sensor2.changeAddress(VL6180X_ADDRESS, SENSOR2_NEW_ADDRESS); 
  Serial.print("Sensor 2 re-addressed to: 0x");
  Serial.println(SENSOR2_NEW_ADDRESS, HEX); 
    
  // --- 3. Enable Both Sensors for Loop ---
  digitalWrite(SENSOR1_XSHUT, HIGH); 
  digitalWrite(SENSOR2_XSHUT, HIGH); 
  delay(100);
  
  Serial.println("Dual Sensor Initialization SUCCESSFUL.");
  // 
}

void loop() 
{
  String str;

  // Read distances from the uniquely addressed sensors
  uint8_t distance1 = sensor1.getDistance();
  uint8_t distance2 = sensor2.getDistance();

  // Format the output string: #Distance1*Distance2
  str = "#" + String(distance1) + "*" + String(distance2);
  
  Serial.println(str); 
  
  // A small delay is required to prevent I2C flooding
  delay(50); 
}
