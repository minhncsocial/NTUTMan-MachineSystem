#pragma once
#include <iostream>

class GameSetting
{
	static GameSetting *_instance;
	int _brightness;
	int _width;
	int _height;
	GameSetting() : _width(786), _height(1300), _brightness(75) {}
public:
	static GameSetting *getInstance() {
		if (_instance == NULL)
			_instance = new GameSetting();
		return _instance;
	}
	void setWidth(int width) { _width = width; }
	void setHeight(int height) { _height = height; }
	void setBrighness(int brightness) { _brightness = brightness; }

	int GetWidth() { return _width;}
	int GetHeight() { return _height;}
	int GetBrightness() { return _brightness;}
	void displaySetting() {
		std::cout << "brightness " << _brightness << std::endl;
		std::cout << "width " << _width << std::endl;
		std::cout << "height " << _height << std::endl;
	}

private:
	/*GameSetting(void);
	~GameSetting(void);*/
};

