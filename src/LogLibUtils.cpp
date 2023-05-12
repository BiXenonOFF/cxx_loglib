#include "LogLibUtils.hpp"

using cxx_loglib::LogLibUtils;


/* --- CXX INCLUDES --- */
#include <ctime>

std::string LogLibUtils::createCurrentTimeString() 
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", ltm);
	return "[" + std::string(buffer) + "]";
}

std::string LogLibUtils::createCurrentTimePrefixString() 
{
	time_t now = time(0);
	tm* ltm = localtime(&now);

	char buffer[20];
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S", ltm);
	return std::string(buffer);
}

std::string LogLibUtils::toParamString(const std::string& a_Key, const std::string& a_Value) { return std::string(a_Key + "=" + a_Value + "|"); }
std::string LogLibUtils::toParamString(const std::string& a_Key, const char* a_Value) { return LogLibUtils::toParamString(a_Key, std::string(a_Value)); }
std::string LogLibUtils::toParamString(const std::string& a_Key, const long long a_Value) { return LogLibUtils::toParamString(a_Key, std::to_string(a_Value)); }
std::string LogLibUtils::toParamString(const std::string& a_Key, const long double a_Value) { return LogLibUtils::toParamString(a_Key, std::to_string(a_Value)); }
std::string LogLibUtils::toParamString(const std::string& a_Key, const bool a_Value) { if (a_Value) return LogLibUtils::toParamString(a_Key, "1"); else return LogLibUtils::toParamString(a_Key, "0"); }
std::string LogLibUtils::toParamString(const std::string& a_Key, const unsigned long long a_Value) { return LogLibUtils::toParamString(a_Key, std::to_string(a_Value)); }
std::string LogLibUtils::toParamString(const std::string& a_Key, const char a_Value) { return LogLibUtils::toParamString(a_Key, std::to_string(a_Value)); }
