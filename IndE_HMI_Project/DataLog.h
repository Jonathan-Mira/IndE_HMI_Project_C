////////////////////////////////////////////
// 
// IndE_HMI_Project
// DataLog.h
// Created by: Jonathan Mira-Acosta
// Created on: 01/31/2025
// Data Log Object to store the variables and
// export them to a file when requested
//
////////////////////////////////////////////

enum { _day = 0, _month, _year };
enum { _hour = 0, _minute, _second, _miliseconds};
enum { _not_recording = 0, _recording, _record_error};

#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>

class DataLog
{
public:
	DataLog();
	~DataLog();

	// Data points around the IndE 
	float _Speed;
	float _RPM;
	float _Throttle;
	float _Motor_Temp;
	float _Battery_Life;
	float _Battery_Temp;

	// Time and Date variables and functions
	void _SetTime(); //Set the current time and date to _ymd and _hms << Required C++20 or later to work
	std::string _GetDateString(std::string sperator); //Outputs string with format "day/month/year" and sperated by the input string
	std::string _GetTimeString(std::string sperator, int resolution); //Output time string with a chosen reusolution and sperated by the input string
	
	// Functions for exporting the data
	void _OpenFile(std::string filename);
	void _ExportData();
	void _CloseFile();
	int _RecordingStatus; 
	std::string _GetValString(float value); //Check if the value is empty and return "N/A" if it is or the value as a string 

private:
	std::string _FileName;
	std::ofstream _File;
	std::chrono::year_month_day _ymd;
	std::chrono::hh_mm_ss <std::chrono::milliseconds> _hms;
	bool _DataEmpty;

};

