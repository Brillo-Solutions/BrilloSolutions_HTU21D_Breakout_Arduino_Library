/*Written By: Er. Dapinder Singh Virk
  Email ID: brillosolutions@gmail.com
  Version: 1.0.0
  Date: August 30, 2018
  Outputs: (i)    Temperature in double.
           (ii)   Relative Humidity in double.
           (iii)  Battery Alert/Status in unsigned char.	*/
#ifndef HTU21D_h
#define HTU21D_h

#include <Arduino.h>
#include <Wire.h>
class HTU21D
{
	private:
		double ucTemp, ucRH;
		uint8_t BATT;
		uint16_t getDeviceData(uint8_t devID, uint8_t mByte)
		{
			int16_t dWord;
			Wire.beginTransmission(devID);
			Wire.write(mByte);
			Wire.endTransmission();
			Wire.requestFrom(devID, 2);
			dWord = Wire.read() << 8 | Wire.read();
			return dWord;
		}
		void writeUserRegister(uint8_t devID, uint8_t uReg, uint8_t rByte)
		{
			Wire.beginTransmission(devID);
			Wire.write(uReg);
			Wire.write(rByte);
			Wire.endTransmission();
		}
	public:
		HTU21D()
		{
			Wire.begin();
		}
		void resetDevice();
		void mode12rh14t();
		void mode8rh12t();
		void mode10rh13t();
		void mode11rh11t();
		void beginConversion();
		double getTemperature();
		double getHumidity();
		uint8_t getBatteryStatus();		
};
#endif