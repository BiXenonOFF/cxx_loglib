#pragma once

/* --- CXX INCLUDES --- */
#include <string>

namespace cxx_loglib 
{

	class LogLibUtils 
	{
	public:

		static std::string createCurrentTimeString();
		static std::string createCurrentTimePrefixString();
		
		static std::string toParamString(const std::string& a_Key, const std::string& a_Value);
		static std::string toParamString(const std::string& a_Key, const char* a_Value);
		static std::string toParamString(const std::string& a_Key, const long long a_Value);
		static std::string toParamString(const std::string& a_Key, const long double a_Value);
		static std::string toParamString(const std::string& a_Key, const bool a_Value);
		static std::string toParamString(const std::string& a_Key, const unsigned long long a_Value);
		static std::string toParamString(const std::string& a_Key, const char a_Value);
	};

}
