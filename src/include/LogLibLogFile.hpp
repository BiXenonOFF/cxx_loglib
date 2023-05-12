#pragma once

#include <fstream>

namespace cxx_loglib 
{
	class LogFile 
	{
	public:
		
		LogFile(const std::string& a_ProgramName, const std::string& a_PathToLogDir, const bool a_TimePrefix = true, const bool a_IgnoreErrors = false);
		~LogFile();
		
		const bool isOpen() const;
		const bool isError() const;

		const bool getIgnoreErrors() const;
		void setIgnoreErrors(const bool a_IgnoreErrors);

		const std::string& getProgramName() const;
		const std::string& getPathToLogDir() const;
		const std::string& getFilename() const;

		void write(const std::string& a_Message);
		void write(const char* a_Message);

		void writeLine(const std::string& a_Message);
		void writeLine(const char* a_Message);

	protected:

		std::string m_ProgramName;
		std::string m_PathToLogDir;
		std::string m_Filename;

		std::fstream m_File;
		bool m_IgnoreErrors;
		bool m_TimePrefix;
		bool m_isError;
	};
}
