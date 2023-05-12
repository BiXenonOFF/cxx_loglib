#include "LogLibLogger.hpp"

using cxx_loglib::InFunctionObject;
using cxx_loglib::Logger;
using cxx_loglib::LOG_LEVEL;

/* --- CXX INCLUDES --- */
#include <vector>


InFunctionObject::InFunctionObject(const std::string& a_FunctionName, const LOG_LEVEL a_FunctionLogLevel) 
{
	this->m_FuncName = a_FunctionName;
	this->m_FuncLogLevel = a_FunctionLogLevel;
	Logger::getInstance()->logFunctionEntry(this);
}

InFunctionObject::~InFunctionObject() 
{
	Logger::getInstance()->logFunctionReturn(this);
}

const std::string& InFunctionObject::getFunctionName() const { return this->m_FuncName; }
const LOG_LEVEL InFunctionObject::getLogLevel() const { return this->m_FuncLogLevel; }


Logger::Logger() 
{
	this->m_CurrentLine = -1;
	this->m_Initialized = false;
	this->m_LogFilePtr = nullptr;
	this->m_LogLevel = LOG_LEVEL::NOLOG;
	this->m_MaxLogLines = 0;
	this->m_PathToLogDir = "";
	this->m_ProgramName = "";
}

Logger::~Logger() {}

Logger* Logger::getInstance() 
{
	if (!_self) 
		_self = new Logger();

	return _self;
}

void Logger::deleteInstance() 
{
	if (_self)
	{
		delete _self->m_LogFilePtr;
		delete _self;
		_self = nullptr;
	}
}

void Logger::init(const std::string& a_ProgramName, const LOG_LEVEL a_LogLevel, const long a_MaxLogLines, const std::string& a_PathToLogDir) 
{
	this->m_ProgramName = a_ProgramName;
	this->m_LogLevel = a_LogLevel;
	this->m_MaxLogLines = a_MaxLogLines;
	this->m_PathToLogDir = a_PathToLogDir;
	this->m_LogFilePtr = new LogFile(this->m_ProgramName, this->m_PathToLogDir);
	this->m_CurrentLine = 0;
	this->m_Initialized = true;
}


const std::string& Logger::getProgramName() const 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();

	return this->m_ProgramName;
}

const std::string& Logger::getPathToLogDir() const 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();
	return this->m_PathToLogDir;
}

const long Logger::getMaxLogLines() const 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();
	return this->m_MaxLogLines;
}
const LOG_LEVEL Logger::getLogLevel() const 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();
	return this->m_LogLevel;
}
const bool Logger::isInitialized() const 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();
	return this->m_LogLevel;
}
const long Logger::getCurrentLine() const 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();
	return this->m_CurrentLine;
}


void Logger::log(const InFunctionObject* a_Function, const std::string& a_Message)
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();

	if (a_Function->getLogLevel() > this->m_LogLevel)
		return;

	std::string sLine = "";
	for (int i = 0; i < this->m_FunctionStack.size(); i++) 
	{
		if (i > 0)
			sLine += "|\t";
		else 
			sLine += "\t";
	}

	sLine += a_Function->getFunctionName();
	sLine += " ";
	sLine += a_Message;

	this->m_LogFilePtr->writeLine(sLine);
}

void Logger::log(const InFunctionObject* a_Function, const char* a_Message) 
{
	this->log(a_Function, std::string(a_Message));
}


void Logger::logMessage(const InFunctionObject* a_Function, const std::string& a_Message) 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();

	if (a_Function->getLogLevel() > this->m_LogLevel)
		return;

	std::string sLine = "";
	for (int i = 0; i < this->m_FunctionStack.size(); i++)
	{
		if (i > 0)
			sLine += "|\t";
		else
			sLine += "\t";
	}

	sLine += a_Function->getFunctionName();
	sLine += ">>";
	sLine += a_Message;

	this->m_LogFilePtr->writeLine(sLine);
}

void Logger::logMessage(const InFunctionObject* a_Function, const char* a_Message) 
{
	this->logMessage(a_Function, std::string(a_Message));
}

void Logger::logFunctionEntry(const InFunctionObject* a_Function) 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();
	if (a_Function->getLogLevel() > this->m_LogLevel)
		return;

	std::string sLine = "";
	for (int i = 0; i < this->m_FunctionStack.size(); i++)
	{
		if (i > 0)
			sLine += "|\t";
		else
			sLine += "\t";
	}

	sLine += a_Function->getFunctionName();
	
	this->m_FunctionStack.emplace(a_Function->getFunctionName());
}

void Logger::logFunctionReturn(const InFunctionObject* a_Function) 
{
	if (!m_Initialized)
		ERROR_LOGGER_NOT_INITIALIZED();

	if (a_Function->getLogLevel() > this->m_LogLevel)
		return;
	
	if (a_Function->getFunctionName() == this->m_FunctionStack.top().getFunctionName()) 
	{
		this->m_FunctionStack.pop();
	}
}


void Logger::printFunctionStack() 
{
	std::vector<InFunctionObject*> vStackSave;

	std::string sResult = "";

	while (this->m_FunctionStack.size() > 0) 
	{
		sResult += this->m_FunctionStack.top().getFunctionName() + "\n";
		vStackSave.emplace_back(this->m_FunctionStack.top());
		this->m_FunctionStack.pop();
	}

	this->m_LogFilePtr->write("---- CALL STACK ----\n");
	this->m_LogFilePtr->write(sResult);
	this->m_LogFilePtr->writeLine("---- END STACK ----");

	for (auto iter = vStackSave.rbegin(); iter != vStackSave.rend(); iter++) 
	{
		this->m_FunctionStack.emplace(*iter);
	}
}

