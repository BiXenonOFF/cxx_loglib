#include "LogLibException.hpp"

using namespace cxx_loglib;

CustomException::CustomException(const std::string& a_ExceptionCode, const std::string& a_ExceptionText, const std::string& a_ExceptionParams, const bool a_Fatal, const std::string& a_File, const std::string& a_Line)
{
	this->m_ExceptionCode = a_ExceptionCode;
	this->m_ExceptionText = a_ExceptionText;
	this->m_ExceptionParams = a_ExceptionParams;
	this->m_Fatal = a_Fatal;
	this->m_File = a_File;
	this->m_Line = a_Line;
}

const char* CustomException::what() 
{
	return this->m_ExceptionCode.c_str();
}

const std::string& CustomException::getExceptionCode() const { return this->m_ExceptionCode; }
const std::string& CustomException::getExceptionText() const { return this->m_ExceptionText; }
const std::string& CustomException::getExceptionParams() const { return this->m_ExceptionParams; }

const bool CustomException::isFatal() const { return this->m_Fatal; }

const std::string& CustomException::getFile() const { return this->m_File; }
const std::string& CustomException::getLine() const { return this->m_Line; }
