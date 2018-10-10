#pragma once

#define SENSOR_RESOLUTION 9
#define SENSORS_REFRESH_INTERVAL 5000
#define SENSORS_BUS_PIN 6

#define FIRST_SENSOR_ADDRESS {0x28, 0xFF, 0xC0, 0xA6, 0x71, 0x15, 0x3, 0x7F}
#define SECOND_SENSOR_ADDRESS {0x28, 0xFF, 0x92, 0xC4, 0x71, 0x15, 0x3, 0xFE}
#define THIRD_SENSOR_ADDRESS {0x28, 0xFF, 0x6E, 0x9D, 0x71, 0x15, 0x3, 0x32}
#define FOTH_SENSOR_ADDRESS {0x28, 0xFF, 0x6E, 0x9D, 0x71, 0x15, 0x3, 0x32}

#include <inttypes.h>
#include <DallasTemperature.h>


class TemperatureSensors
{
private:
	DeviceAddress m_coolantSensorAddress = FIRST_SENSOR_ADDRESS;
	DeviceAddress m_insideSensorAddress = SECOND_SENSOR_ADDRESS;
	DeviceAddress m_boardSensorAddress = THIRD_SENSOR_ADDRESS;
	uint8_t m_oneWirePin;

	float m_coolantTemp = 0.0;
	float m_insideTemp = 0.0;
	float m_boardTemp = 0.0;

	DallasTemperature* m_sensors;
	unsigned long m_previousMillis = 0;

public:
	TemperatureSensors();

	float getCoolantTemp();
	float getInsideTemp();
	float getBoardTemp();

	void refreshSensorValues();
	void initialize();

	~TemperatureSensors();
};
