/*Written By: Er. Dapinder Singh Virk
  Email ID: brillosolutions@gmail.com
  Version: 1.0.0
  Date: August 30, 2018
  Outputs: (i)    Temperature in double.
           (ii)   Relative Humidity in double.
           (iii)  Battery Alert/Status in unsigned char.	*/
#include <HTU21D.h>

#define DEV_ADDR 0x40
#define TEMP_MEAS_HOLD 0xE3
#define HUMI_MEAS_HOLD 0xE5
#define TEMP_MEAS_NO_HOLD 0xF3
#define HUMI_MEAS_NO_HOLD 0xF5
#define DEV_SOFT_RESET 0xFE
#define WRITE_USER_REG 0xE6
#define READ_USER_REG 0xE7
#define RES_12RH_14T 0x02
#define RES_8RH_12T 0x03
#define RES_10RH_13T 0x82
#define RES_11RH_11T 0x83

void HTU21D::resetDevice()
{
	Wire.beginTransmission(DEV_ADDR);
	Wire.write(DEV_SOFT_RESET);
	Wire.endTransmission();
}

void HTU21D::mode12rh14t()
{
	writeUserRegister(DEV_ADDR, WRITE_USER_REG, RES_12RH_14T);
}

void HTU21D::mode8rh12t()
{
	writeUserRegister(DEV_ADDR, WRITE_USER_REG, RES_8RH_12T);
}

void HTU21D::mode10rh13t()
{
	writeUserRegister(DEV_ADDR, WRITE_USER_REG, RES_10RH_13T);
}

void HTU21D::mode11rh11t()
{
	writeUserRegister(DEV_ADDR, WRITE_USER_REG, RES_11RH_11T);
}

void HTU21D::beginConversion()
{
	for (int k = 0; k <= 1; k++)
	{
		Wire.beginTransmission(DEV_ADDR);
		if (k < 1)
			Wire.write(TEMP_MEAS_HOLD);
		else
			Wire.write(HUMI_MEAS_HOLD);
		Wire.endTransmission();
	}
}

double HTU21D::getTemperature()
{
  double mTemp;
  ucTemp = getDeviceData(DEV_ADDR, TEMP_MEAS_HOLD);
  mTemp = -46.85 + 175.72 * ucTemp / pow(2, 16);
  return mTemp;
}

double HTU21D::getHumidity()
{
  double mRH;
  ucRH = getDeviceData(DEV_ADDR, HUMI_MEAS_HOLD);
  mRH = -6 + 125 * ucRH / pow(2, 16);
  return mRH;
}

uint8_t HTU21D::getBatteryStatus()
{
  Wire.beginTransmission(DEV_ADDR);
  Wire.write(READ_USER_REG);
  Wire.endTransmission();
  Wire.requestFrom(DEV_ADDR, 1);
  BATT = Wire.read();
  if ((BATT & 0xF0) == 0)
	  return 0x00;
  else
	  return 0x01;
}