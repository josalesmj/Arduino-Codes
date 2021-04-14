/* This example shows how to get single-shot range
 measurements from the VL53L0X. The sensor can optionally be
 configured with different ranging profiles, as described in
 the VL53L0X API user manual, to get better performance for
 a certain application. This code is based on the four
 "SingleRanging" examples in the VL53L0X API.

 The range readings are in units of mm. */

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;


// Uncomment this line to use long range mode. This
// increases the sensitivity of the sensor and extends its
// potential range, but increases the likelihood of getting
// an inaccurate reading because of reflections from objects
// other than the intended target. It works best in dark
// conditions.

//#define LONG_RANGE


// Uncomment ONE of these two lines to get
// - higher speed at the cost of lower accuracy OR
// - higher accuracy at the cost of lower speed

//#define HIGH_SPEED
#define HIGH_ACCURACY

int ledPin = 12;
int relePin = 11;
int defaultMinRange = 500;
int defaultMaxRange = 550;
int range = 0;
int count = 0;
int lastCall = 0;
void setup(){
  Serial.begin(115200);
  Wire.begin();
  pinMode(ledPin,OUTPUT);
  pinMode(relePin,OUTPUT);
  digitalWrite(relePin, HIGH);
  

  sensor.setTimeout(500);
  if (!sensor.init()){
    Serial.println("Failed to detect and initialize sensor!");
    while (1) {}
  }

#if defined LONG_RANGE
  // lower the return signal rate limit (default is 0.25 MCPS)
  sensor.setSignalRateLimit(0.1);
  // increase laser pulse periods (defaults are 14 and 10 PCLKs)
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodPreRange, 18);
  sensor.setVcselPulsePeriod(VL53L0X::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
  // reduce timing budget to 20 ms (default is about 33 ms)
  sensor.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
  // increase timing budget to 200 ms
  sensor.setMeasurementTimingBudget(200000);
#endif
}

void loop(){
  //if(millis() - lastCall > 50){
    //lastCall = millis();
    range = sensor.readRangeSingleMillimeters();
    Serial.print(range);Serial.print(" mm - Contagem ");Serial.println(count);
    if (sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }

    if(range < defaultMinRange){
      count++;
      digitalWrite(ledPin, HIGH);
      digitalWrite(relePin, LOW);
    }
    else{
      digitalWrite(ledPin, LOW);
      digitalWrite(relePin, HIGH);
    }
    while(range < defaultMinRange){
      Serial.print(range);Serial.print(" < ");Serial.println(defaultMinRange);
      range = sensor.readRangeSingleMillimeters();
    }

    delay(20);
  //}
 
}
