#include <SimpleDHT.h>
#include <stdint.h>
#include "SparkFunBME280.h"
//Library allows either I2C or SPI, so include both.
#include "Wire.h"
#include "SPI.h"
#include <MQ135.h>
const int gasPin = A0; //GAS sensor output pin to Arduino analog A0 pin
MQ135 mqSensor(A0);
BME280 mySensor;
float resistanceZero = mqSensor.getRZeroAcetone();
float mqSen =  mqSensor.getCorrectedRZeroAcetone(resistanceZero);
float value,lastvalue=20;
int pinDHT11 = 8;
SimpleDHT11 dht11;

void setup()
{
  mySensor.settings.commInterface = I2C_MODE;
  mySensor.settings.I2CAddress = 0x76;
  mySensor.settings.runMode = 3; //Normal mode
  mySensor.settings.tStandby = 0;
  mySensor.settings.filter = 0;
  
  //tempOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.tempOverSample = 1;
  //pressOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
    mySensor.settings.pressOverSample = 1;
  
  //humidOverSample can be:
  //  0, skipped
  //  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
  mySensor.settings.humidOverSample = 1;
  Serial.println(mySensor.begin(), HEX);
  pinMode(11,OUTPUT)  ;
  Serial.begin(9600); //Initialize serial port - 9600 bps
  digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(11, LOW);    // turn the LED off by making the voltage LOW
  delay(1000); 
  digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(11, LOW);
  delay(500);
  digitalWrite(11, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(11, LOW);
  Serial.print("Program Started\n");
  Serial.print("Starting BME280... result of .begin(): 0x");
  
  }
void loop(){

   // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
 
 
  // DHT11 sampling rate is 1HZ.
  delay(1500);
  float resistance = mqSensor.getResistance();
  float acetone = mqSensor.getAcetone(resistance);
  value=acetone;
  if(value>lastvalue)
  {
    value=lastvalue;
    
  }
  lastvalue=value;
  delay(2000); // Print valuez every 2 sec.
  Serial.print("Acetone: ");
  Serial.print(value);
  Serial.println(" PPM");
  Serial.print("Pressure: ");
  Serial.print(mySensor.readFloatPressure(), 2);
  Serial.println(" Pa");
  Serial.print((int)temperature); 
  Serial.print(" *C, "); 
  Serial.print((int)humidity); 
  Serial.println(" H");

  
}

