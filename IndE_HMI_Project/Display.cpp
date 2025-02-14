////////////////////////////////////////////
// 
// IndE_HMI_Project
// Display.cpp
// Created by: Jonathan Mira-Acosta
// Created on: 02/04/2025
// Creates and Displays the different pages of the GUI
//
////////////////////////////////////////////
#include "Display.h"


Display::Display()
{
	_GetConfig();
	cvui::init(WINDOW_NAME);
	_Button = false;
}

Display::~Display()
{
}

void Display::_GetConfig()
{
	_config.clear();
	std::ifstream file;
	file.open("IndE_HMI.cfg");

	std::string filein;

	int i = 0;
	while (std::getline(file, filein))
	{
		_config.push_back(filein);
		_config.at(i).erase(0, _config_Delete[i]);
		i++;
	}
	_Width = std::stoi(_config.at(_D_Width));
	_Height = std::stoi(_config.at(_D_Height));

	_UI_Canvas = cv::Mat::zeros(_Height, _Width, CV_8UC3);

	file.close();
}

void Display::_DisplayMain(std::string _Time_String, std::string _Date_String, int _Speed, int _Throttle)
{
	//Background Color
	_UI_Canvas = _IndE_Cyan;
	//Top Bar
	_UI_Canvas(cv::Rect(0, 0, _Width, 50)) = _Black;\
	cvui::text(_UI_Canvas, 10, 10, _Date_String, 1, _White);
	cvui::text(_UI_Canvas, 700, 10, _Time_String, 1, _White);

	//Main Text Display
	_Text_Bold(_UI_Canvas, 10, 210, std::to_string(_Speed) + std::string("km"), _Height/100, _Black, _Height/100);
	_Text_Bold(_UI_Canvas, 100, 400, std::to_string(_Throttle) + std::string("%"), _Height/200, _Black, (_Height/400) +1);

	//Indicators
	cvui::text(_UI_Canvas, 950, 150, "Battery Temp", 1, _Black);
	cv::circle(_UI_Canvas, cv::Point(1050, 250), 50, cv::Scalar(128, 128, 128), CVUI_FILLED); //Battery Temp
	cvui::text(_UI_Canvas, 1235, 150, "Charge", 1, _Black);
	cv::circle(_UI_Canvas, cv::Point(1300, 250), 50, cv::Scalar(128, 128, 128), CVUI_FILLED); //Charge
	cvui::text(_UI_Canvas, 950, 400, "Motor Temp", 1, _Black);
	cv::circle(_UI_Canvas, cv::Point(1050, 500), 50, cv::Scalar(128, 128, 128), CVUI_FILLED); //Motor Temp
	cvui::text(_UI_Canvas, 1210, 400, "Emergency", 1, _Black);
	cv::circle(_UI_Canvas, cv::Point(1300, 500), 50, cv::Scalar(128, 128, 128), CVUI_FILLED); //Emergency


	//Buttons
	_Button = cvui::button(_UI_Canvas, _Width - 130, _Height - 100, 130, 100, "Reset Config");
	if (_Button)
	{
		_GetConfig();
	}
	_Button = cvui::button(_UI_Canvas, 0, _Height - 100, 130, 100, "Start/End");
	if (_Button)
	{
		_Record = true;
	}
	cvui::text(_UI_Canvas, 70, 620, "Recording", 1, _Black);
	cv::circle(_UI_Canvas, cv::Point(200, _Height-50), 50, cv::Scalar(128, 128, 128), CVUI_FILLED); //Emergency


	cvui::update();
	cv::imshow(WINDOW_NAME, _UI_Canvas);
}

void Display::_Text_Bold(cv::Mat &_Canvas, int _X, int _Y, std::string _Text, int _Size, int _Color, int _bold)
{
	for (int x = 0; x <= _bold; x++)
	{
		for (int y = 0; y <= _bold; y++)
		{
			cvui::text(_Canvas, _X+x, _Y+y, _Text, _Size, _Color);
		}
	}
}
