// ================================================ //

#include "LogImpl.hpp"

// ================================================ //

LogImpl::LogImpl(void)
	: m_file()
{
	m_file.open("ExtMF.log", std::ios::out);
	if(!m_file.is_open()){
		throw std::exception("Failed to open log file");
	}

	this->logTime(false, true);
	this->logMessage(" Log created for Extreme Metal Fighter\n");
}

// ================================================ //

LogImpl::~LogImpl(void)
{
	m_file.close();
}

// ================================================ //

void LogImpl::logMessage(const std::string& str)
{
	this->logTime();
	m_file << str << std::endl;

#ifdef _DEBUG
	printf("%s\n", str.c_str());
#endif
}

// ================================================ //

void LogImpl::logTime(const bool time, const bool date)
{
#ifdef __WIN32__
	SYSTEMTIME st;
	GetLocalTime(&st);
	if(date){
		m_file << "[" << st.wMonth << "/" << st.wDay << "/" << st.wYear << "] ";
	}
	if(time){
		if(st.wHour < 10) m_file << "0";
		m_file << st.wHour << ":";
		if(st.wMinute < 10) m_file << "0";
		m_file << st.wMinute << ":";
		if(st.wSecond < 10) m_file << "0";
		m_file << st.wSecond << ": ";
	}
#elif __linux__
	;
#elif __APPLE__
	;
#endif
}

// ================================================ //