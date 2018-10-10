#include "Arduino.h" 
#include "stdint.h" 
#include "TemperatureSensors.h"
#include <OneWire.h>
#include <DallasTemperature.h>


TemperatureSensors::TemperatureSensors()
{
	m_sensors = new DallasTemperature(new OneWire(SENSORS_BUS_PIN));
}


float TemperatureSensors::getCoolantTemp()
{
	return m_coolantTemp;
}

float TemperatureSensors::getInsideTemp()
{
	return m_insideTemp;
}

float TemperatureSensors::getBoardTemp()
{
	return m_boardTemp;
}

void TemperatureSensors::refreshSensorValues()
{
	unsigned long currentMillis = millis();

	if (currentMillis - m_previousMillis < SENSORS_REFRESH_INTERVAL) 
	{
		return;
	}

	m_previousMillis = currentMillis;
	m_sensors->requestTemperatures();
	m_coolantTemp = m_sensors->getTempC(m_coolantSensorAddress);
	m_insideTemp = m_sensors->getTempC(m_insideSensorAddress);
	m_boardTemp = m_sensors->getTempC(m_boardSensorAddress);
}

void TemperatureSensors::initialize()
{
	m_sensors->begin();
	m_sensors->setResolution(m_coolantSensorAddress, 9);
	m_sensors->setResolution(m_insideSensorAddress, 9);
	m_sensors->setResolution(m_boardSensorAddress, 9);
	m_previousMillis = millis();
}

TemperatureSensors::~TemperatureSensors()
{
	
}
