#include "LogLibLogFile.hpp"
#include "LogLibUtils.hpp"
#include "LogLibException.hpp"

using cxx_loglib::LogFile;
using cxx_loglib::LogLibUtils;
using cxx_loglib::CustomException;

LogFile::LogFile(const std::string& a_ProgramName, const std::string& a_PathToLogDir, const bool a_TimePrefix = true, const bool a_IgnoreErrors = false)
{
	this->m_ProgramName = a_ProgramName;
	this->m_PathToLogDir = a_PathToLogDir;
	this->m_TimePrefix = a_TimePrefix;
	this->m_IgnoreErrors = a_IgnoreErrors;
	this->m_isError = false;

	if (m_TimePrefix)
		this->m_Filename = a_PathToLogDir + m_ProgramName + LogLibUtils::createCurrentTimePrefixString() + ".log";
	else
		this->m_Filename = a_PathToLogDir + m_ProgramName + ".log";

	std::string sWhatMsg;

	try 
	{
		m_File.open(m_Filename, std::ios_base::out);
		if (!m_File.is_open())
			THROW_EXCEPTION("FileNotOpened", "File {Filename} wasn't opened", LogLibUtils::toParamString("Filename", m_Filename));
	}
	catch (CustomException e)
	{
		sWhatMsg = "Code=" + e.getExceptionCode() + " Text=" + e.getExceptionText() + " Params=" + e.getExceptionParams() + " File=" + e.getFile() + " Line=" + e.getLine();
		this->m_isError = true;
	}
	catch (std::exception e) 
	{
		sWhatMsg = e.what();
		this->m_isError = true;
	}

	if (!this->m_IgnoreErrors)
		throw std::exception(sWhatMsg.c_str());
}

LogFile::~LogFile() 
{
	if (this->m_File.is_open())
		this->m_File.close();
}

const bool LogFile::isOpen() const { return this->m_File.is_open(); }
const bool LogFile::isError() const { return this->m_isError; }
const bool LogFile::getIgnoreErrors() const { return this->m_IgnoreErrors; }
void LogFile::setIgnoreErrors(const bool a_IgnoreErrors) { this->m_IgnoreErrors = a_IgnoreErrors; }


const std::string& LogFile::getProgramName() const { return this->m_ProgramName; }
const std::string& LogFile::getFilename() const { return this->m_Filename; }
const std::string& LogFile::getPathToLogDir() const { return this->m_PathToLogDir; }

void LogFile::write(const std::string& a_Message) 
{
	if (!this->m_File.is_open()) 
	{
		if (this->m_IgnoreErrors)
			return;

		THROW_EXCEPTION("FileNotOpened", "File {Filename} wasn't opened", LogLibUtils::toParamString("Filename", m_Filename));
	}

	if (this->m_TimePrefix)
	{
		std::string sTimeString = LogLibUtils::createCurrentTimeString().c_str();
		this->m_File.write(sTimeString.c_str(), sizeof(sTimeString.c_str()));
		this->m_File.write("\t", sizeof("\t"));
	}

	this->m_File.write(a_Message.c_str(), sizeof(a_Message.c_str()));
	this->m_File.flush();
}

void LogFile::write(const char* a_Message) 
{
	if (!this->m_File.is_open())
	{
		if (this->m_IgnoreErrors)
			return;

		THROW_EXCEPTION("FileNotOpened", "File {Filename} wasn't opened", LogLibUtils::toParamString("Filename", m_Filename));
	}

	if (this->m_TimePrefix)
	{
		std::string sTimeString = LogLibUtils::createCurrentTimeString().c_str();
		this->m_File.write(sTimeString.c_str(), sizeof(sTimeString.c_str()));
		this->m_File.write("\t", sizeof("\t"));
	}

	this->m_File.write(a_Message, sizeof(a_Message));
	this->m_File.flush();
}

void LogFile::writeLine(const std::string& a_Message) 
{
	this->write(a_Message);
	this->write("\n");
}

void LogFile::writeLine(const char* a_Message) 
{
	this->write(a_Message);
	this->write("\n");
}
