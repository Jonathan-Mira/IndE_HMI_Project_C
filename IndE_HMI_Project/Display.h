////////////////////////////////////////////
// 
// IndE_HMI_Project
// Display.h
// Created by: Jonathan Mira-Acosta
// Created on: 02/04/2025
// Creates and Displays the different pages of the GUI
//
////////////////////////////////////////////

enum {_Display=0, _D_Width, _D_Height};
#pragma once
#include <fstream>
#include <vector>
#include <string>

// Add simple GUI elements
#include "cvui.h"

// Include the OpenCV library
#include "opencv2/opencv.hpp"


#define WINDOW_NAME "CVUI Test"
const int _config_Delete[3] = { 0, 7, 8 };

#define _Black 0x000000
#define _White 0xFFFFFF
#define _Grey  0x808080
const cv::Scalar _IndE_Cyan = cv::Scalar(200, 200, 50);

class Display
{
public:
	Display();
	~Display();
	void _GetConfig();
	void _DisplayMain(std::string _Time_String, std::string _Date_String, int _Speed, int _Throttle);
	std::vector<std::string> _config;
	bool _Record;

private:
	int _Width;
	int _Height;
	cv::Mat _UI_Canvas;
	bool _Button;
	void _Text_Bold(cv::Mat& _Canvas, int _X, int _Y, std::string _Text, int _Size, int _Color, int _bold);

};

