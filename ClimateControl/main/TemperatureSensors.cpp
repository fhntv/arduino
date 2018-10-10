#include "Arduino.h" 
#include "stdint.h" 
#include "TemperatureSensors.h"
#include <OneWire.h>
#include <DallasTemperature.h>


TemperatureSensors::TemperatureSensors()
{
	m_sensors = new DallasTemperature(new OneWire(SENSORS_BUS_PIN));
}


float TemperatureSensors::getRoomInTemp()
{
	return m_RoomInTemp;
}

float TemperatureSensors::getRoomOutTemp()
{
	return m_RoomOutTemp;
}

float TemperatureSensors::getOtsideInTemp()
{
  return m_OtsideInTemp;
}

float TemperatureSensors::getOtsideOUTTemp()
{
  return m_OtsideOUTTemp;
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
	m_RoomInTemp = m_sensors->getTempC(m_RoomInSensorAddress);
	m_RoomOutTemp = m_sensors->getTempC(m_RoomOutSensorAddress);
  m_OtsideInTemp = m_sensors->getTempC(m_OtsideInSensorAddress);
  m_OtsideOUTTemp = m_sensors->getTempC(m_OtsideOUTSensorAddress);

  
}

void TemperatureSensors::initialize()
{
	m_sensors->begin();
	m_sensors->setResolution(m_RoomInSensorAddress, 9);
	m_sensors->setResolution(m_RoomOutSensorAddress, 9);
  m_sensors->setResolution(m_OtsideInSensorAddress, 9);
  m_sensors->setResolution(m_OtsideOUTSensorAddress, 9);
	m_previousMillis = millis();

   
}

TemperatureSensors::~TemperatureSensors()
{
	
}
