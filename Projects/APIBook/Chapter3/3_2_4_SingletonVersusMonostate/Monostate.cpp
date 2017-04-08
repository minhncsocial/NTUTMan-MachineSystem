#include "StdAfx.h"
#include "Monostate.h"

int Rectangle::sHeight = 600;
int Rectangle::sWidth = 800;


int Temperature::sTemperature = 37;
int Temperature::GetTemperature() const
{
	return sTemperature;
}

void Temperature::SetTemperature(int temperature) const
{
	sTemperature = temperature;
}




