#pragma once

/* --- CXX INCLUDES --- */
#include <string>
#include <stack>

#include "LogLibException.hpp"
#include "LogLibLogFile.hpp"

namespace cxx_loglib 
{
	typedef enum 
	{
		NOLOG,
		ERRORS_CXX,
		ERRORS_PRJ,
		EVENTS,
		DEBUG,
		ALL
	} LOG_LEVEL;


	class InFunctionObject 
	{
	public:

		InFunctionObject(const std::string& a_FuncName, const LOG_LEVEL a_FuncLogLevel);
		~InFunctionObject();

		const std::string& getFunctionName() const;
		const LOG_LEVEL getLogLevel() const;

	protected:

		std::string m_FuncName;
		LOG_LEVEL m_FuncLogLevel;
	};


	class Logger 
	{
	protected:

		static Logger* _self;
		Logger();
		~Logger();

#define ERROR_LOGGER_NOT_INITIALIZED() THROW_EXCEPTION("LoggerNotInitializedError", "Logger object wasn't initialized correctly", "")

	public:

		static Logger* getInstance();
		static void deleteInstance();

		void init(const std::string& a_ProgramName, const LOG_LEVEL a_LogLevel, const long a_MaxLogLines=10000, const std::string& a_PathToLogDir = ".");


		const std::string& getProgramName() const;
		const std::string& getPathToLogDir() const;
		const long getMaxLogLines() const;
		const LOG_LEVEL getLogLevel() const;
		const bool isInitialized() const;
		const long getCurrentLine() const;


		void log(const InFunctionObject* a_Function, const std::string& a_Message);
		void log(const InFunctionObject* a_Function, const char* a_Message);

		void logMessage(const InFunctionObject* a_Function, const std::string& a_Message);
		void logMessage(const InFunctionObject* a_Function, const char* a_Message);

		void logFunctionEntry(const InFunctionObject* a_Function);
		void logFunctionReturn(const InFunctionObject* a_Function);

		void printFunctionStack();

	protected:

		std::string m_ProgramName;
		std::string m_PathToLogDir;
		long m_MaxLogLines;
		LOG_LEVEL m_LogLevel;
		bool m_Initialized;
		long m_CurrentLine;

		std::stack<InFunctionObject> m_FunctionStack;

		LogFile* m_LogFilePtr;
	};

}
