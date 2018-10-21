/*Written By: Er. Dapinder Singh Virk
  Email ID: brillosolutions@gmail.com
  Version: 1.0.0
  Date: August 30, 2018
  Outputs: (i)    Temperature in °C, °F and Kelvin units.
           (ii)   Relative Humidity in % unit.
           (iii)  Partial Pressure in mmHg unit.
           (iv)   Dew Point in °C unit.
           (v)    Battery Alert/Status  */
		   
#include <HTU21D.h>
HTU21D ht;
void setup() 
{
  Serial.begin(9600);
  ht.resetDevice();
  ht.mode12rh14t();
  delay(15);
}

void loop() 
{
  ht.beginConversion();
  delay(1000);
  showReadings(ht.getTemperature(), ht.getHumidity(), ht.getBatteryStatus());
}

void showReadings(double Temp, double RH, uint8_t BATT)
{
  Serial.print("Temperature:\t\t");
  Serial.print(Temp);
  Serial.print("°C, ");
  Serial.print(Temp * 1.8 + 32);
  Serial.print("°F, ");
  Serial.print(Temp + 273.15);
  Serial.print("K\n");
  Serial.print("Humidity:\t\t");
  Serial.print(RH);
  Serial.print("%\n");
  Serial.print("Partial Pressure:\t");
  Serial.print(10 * (8.1332 - 1762.39 / (Temp + 235.66)));
  Serial.print("mmHg\n");
  Serial.print("Dew Point:\t\t");
  Serial.print(pow((RH / 100), 0.125) * (112 + 0.9 * Temp) + 0.1 * Temp - 112);
  Serial.print("°C\n");
  Serial.print("Battery Status:\t\t");
  if (BATT == 0)
    Serial.print("OK, BATTERY > 2.25v\n\n");
  else
    Serial.print("NOT OK, BATTERY < 2.25v\n\n");
}
