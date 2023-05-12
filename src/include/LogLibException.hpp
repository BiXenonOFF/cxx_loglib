#pragma once

/* --- CXX INCLUDES --- */
#include <exception>
#include <string>

namespace cxx_loglib 
{

	class CustomException : std::exception 
	{
	public:
		CustomException(const std::string& a_ExceptionCode, const std::string& a_ExceptionText = "", const std::string& a_ExceptionParams = "", const bool a_Fatal = false, const std::string& a_File = "", const std::string& a_Line = "");
		const char* what();

		const std::string& getExceptionCode() const;
		const std::string& getExceptionText() const;
		const std::string& getExceptionParams() const;
		const bool isFatal() const;
		const std::string& getFile() const;
		const std::string& getLine() const;

	protected:

		std::string m_ExceptionCode;
		std::string m_ExceptionText;
		std::string m_ExceptionParams;
		std::string m_File;
		std::string m_Line;
		bool m_Fatal;
	};


#define THROW_EXCEPTION(CODE,TEXT,PARAMS) throw CustomException(CODE,TEXT,PARAMS, false, __FILE__, std::to_string(__LINE__))
#define THROW_EXCEPTION_FATAL(CODE,TEXT,PARAMS) throw CustomException(CODE,TEXT,PARAMS, true, __FILE__, std::to_string(__LINE__))
}
