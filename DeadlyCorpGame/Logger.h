#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <chrono>
#include <ctime>





/// <summary>
/// Class for logging msgs to console.
/// Used for debuging purposes.
/// </summary>
class Logger
{
public:
	/// <summary>
	/// Sets the logger instance's active state.
	/// </summary>
	/// <param name="state"></param>
	static bool setActive(bool state) { isActive = state; return isActive; };
	/// <summary>
	/// Method for logging errors to console
	/// </summary>
	static void logError(std::string msg)  
	{ 
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		if(isActive)
			std::cout << "ERROR: " << msg << " " << std::ctime(&time) << std::endl;
	};
	/// <summary>
	/// Method for logging warnings to console
	/// </summary>
	static void logWarning(std::string msg) 
	{ 
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		if (isActive)
			std::cout << "WARNING: " << msg << " " << std::ctime(&time) << std::endl;
	};
	/// <summary>
	/// Method for logging debug msgs to console
	/// </summary>
	static void logDebug(std::string msg) 
	{ 
		auto time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		if(isActive)
			std::cout << "DEBUG: " << msg << " " << std::ctime(&time) << std::endl;
	};

private:
	/// <summary>
	/// controls whether or not the msgs print to console. init as false.
	/// </summary>
	static inline bool isActive = false;
	
};
#endif