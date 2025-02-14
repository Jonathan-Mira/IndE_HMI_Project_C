////////////////////////////////////////////
// 
// IndE_HMI_Project
// DataLog.cpp
// Created by: Jonathan Mira-Acosta
// Created on: 01/31/2025
// Data Log Object to store the variables and
// export them to a file when requested
//
////////////////////////////////////////////
#include "DataLog.h"

//Constructor
//Does _SetTime() and sets _RecordingStatus to _not_recording
DataLog::DataLog()
{
	_SetTime();
	_RecordingStatus = _not_recording;
	_DataEmpty = true;
}

//Destructor
//Does Nothing
DataLog::~DataLog()
{
}


//Sets the current time and date to _ymd and _hms
//Code was derived from https://stackoverflow.com/questions/77004308/how-do-i-use-stdchrono-to-extract-time-units-out-of-epoch-time 
void DataLog::_SetTime()
{
	const auto now = std::chrono::system_clock::now();
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
	std::chrono::time_point<std::chrono::system_clock> now_ms(ms);
	auto t_local = std::chrono::current_zone()->to_local(now_ms);
	auto t_days = std::chrono::floor<std::chrono::days>(t_local);
	_ymd = std::chrono::year_month_day{t_days};
	_hms = std::chrono::hh_mm_ss <std::chrono::milliseconds>(std::chrono::duration_cast<std::chrono::milliseconds>(t_local - t_days));
}

// Input: sperator - string to sperate the date
// Output: string with format "day/month/year" and sperated by the input string
std::string DataLog::_GetDateString(std::string sperator)
{
	std::string date = std::to_string(int(_ymd.year()));;

	if (unsigned(_ymd.month()) < 10)
	{
		date += sperator + "0" + std::to_string(unsigned(_ymd.month()));
	}
	else
	{
		date += sperator + std::to_string(unsigned(_ymd.month()));
	}

	if (unsigned(_ymd.day()) < 10)
	{	
		date += sperator + "0" + std::to_string(unsigned(_ymd.day()));
	}
	else
	{
		date += sperator + std::to_string(unsigned(_ymd.day()));
	}

		
	return date;
}

// Input: sperator - string to sperate the time
//	      resolution - int to determine the resolution of the time	
// Output: time string with a chosen reusolution and sperated by the input string
std::string DataLog::_GetTimeString(std::string sperator, int resolution)
{
	std::string time;

	time = std::to_string(_hms.hours().count());

	if (resolution >= _minute)
	{
		time += sperator + std::to_string(_hms.minutes().count());

		if (resolution >= _second)
		{
			time += sperator + std::to_string(_hms.seconds().count());
			if (resolution >= _miliseconds)
			{
				time += std::string(".") + std::to_string(_hms.subseconds().count());
			}
		}
	}
	
	return time;
}

//Opens a file with the filename and the current date and time
void DataLog::_OpenFile(std::string filename)
{
	if (_File.is_open())
	{
		_CloseFile();
	}

	_FileName = filename + "_" + _GetDateString("-") + "_" + _GetTimeString("-",_minute) + ".csv";

	_File.open(_FileName, std::ios::out);

	if (_File.is_open())
	{
		_RecordingStatus = _recording;
		_File << "Date,Time,Speed,RPM,Throttle,Motor Temp,Battery Life,Battery Temp\n";
		_ExportData();
	}
	else
	{
		std::cout << "Error: Could not open file" << std::endl;
		_RecordingStatus = _record_error;
	}

}

//Exports the data to the file
void DataLog::_ExportData()
{
	if (_File.is_open())
	{

		if (_DataEmpty)
		{
			_DataEmpty = false;
			_File << _GetDateString("/") << "," << _GetTimeString(":", _miliseconds) << "," << _GetValString(_Speed) << ","
				<< _GetValString(_RPM) << "," << _GetValString(_Throttle) << "," << _GetValString(_Motor_Temp) << ","
				<< _GetValString(_Battery_Life) << "," << _GetValString(_Battery_Temp) << "\n";
		}
		else
		{
			_File << _GetDateString("/") << "," << _GetTimeString(":", _miliseconds) << "," << std::to_string(_Speed) << ","
				<< std::to_string(_RPM) << "," << std::to_string(_Throttle) << "," << std::to_string(_Motor_Temp) << ","
				<< std::to_string(_Battery_Life) << "," << std::to_string(_Battery_Temp) << "\n";
		}
	}
	else
	{
		std::cout << "Error: Could not write to file" << std::endl;
		_RecordingStatus = _record_error;
	}
}

//Closes the file
void DataLog::_CloseFile()
{
	_File.close();
	_RecordingStatus = _not_recording;
}

//Check if the value is empty and return "N/A" if it is or the value as a string
std::string DataLog::_GetValString(float value)
{


	if (std::to_string(value).empty())
	{
		_DataEmpty = true;
		return std::string("N/A");
	}
	else
	{
		return std::to_string(value);
	}
}

