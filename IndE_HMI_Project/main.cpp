////////////////////////////////////////////
// 
// IndE_HMI_Project
// main.cpp
// Created by: Jonathan Mira-Acosta
// Created on: 01/31/2025
// The main will link the GUI and Data Log Object
// with the CANBus input
//
////////////////////////////////////////////

// Include the OpenCV library
#include "opencv2/opencv.hpp"

// Add simple GUI elements
#define CVUI_DISABLE_COMPILATION_NOTICES
#define CVUI_IMPLEMENTATION
//#include "cvui.h"

#include "Display.h"
#include "DataLog.h"





void main()
{

	// Create the objects
	DataLog DataLog;
	Display Display;

	while (1)
	{
		DataLog._SetTime();
		Display._DisplayMain(DataLog._GetTimeString(":", _minute), DataLog._GetDateString("/"), DataLog._Speed, DataLog._Throttle);
		if (cv::waitKey(30) == 27)
		{
			break;
		}
	}
}
