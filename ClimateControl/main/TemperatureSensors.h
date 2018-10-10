#pragma once

#define SENSOR_RESOLUTION 9
#define SENSORS_REFRESH_INTERVAL 5000
#define SENSORS_BUS_PIN 7

#define FIRST_SENSOR_ADDRESS  {0x28, 0x61, 0x64, 0x11, 0x8C, 0x68, 0x00, 0xA6}
#define SECOND_SENSOR_ADDRESS {0x28, 0x61, 0x64, 0x11, 0x8C, 0x6E, 0x20, 0x2F}
#define THIRD_SENSOR_ADDRESS  {0x28, 0x61, 0x64, 0x11, 0x8C, 0x69, 0xF2, 0xAA}
#define FOURTH_SENSOR_ADDRESS {0x28, 0x61, 0x64, 0x11, 0x8C, 0x69, 0x96, 0xAE}

#include <inttypes.h>
#include <DallasTemperature.h>


class TemperatureSensors
{
private:
	DeviceAddress m_RoomInSensorAddress = FIRST_SENSOR_ADDRESS;
	DeviceAddress m_RoomOutSensorAddress = SECOND_SENSOR_ADDRESS;
  DeviceAddress m_OtsideInSensorAddress = THIRD_SENSOR_ADDRESS;
  DeviceAddress m_OtsideOUTSensorAddress = FOURTH_SENSOR_ADDRESS;
	uint8_t m_oneWirePin;

	float m_RoomInTemp = 0.0;
	float m_RoomOutTemp = 0.0;
  float m_OtsideInTemp = 0.0;
  float m_OtsideOUTTemp = 0.0;

	DallasTemperature* m_sensors;
	unsigned long m_previousMillis = 0;

public:
	TemperatureSensors();

	float getRoomInTemp();
	float getRoomOutTemp();
	float getOtsideInTemp();
  float getOtsideOUTTemp();


	void refreshSensorValues();
	void initialize();

	~TemperatureSensors();
};
