#include "Log.h"
#include <fstream>
#include <sstream>

std::string intToString(const int argv)
{
	std::ostringstream stringStream;
	stringStream << argv;
	return stringStream.str();
}

std::string doubleToString(const double argv)
{
	std::ostringstream stringStream;
	stringStream << argv;
	return stringStream.str();
}

/*
###############################################################################
Logger class definition
###############################################################################
*/

Logger* Logger::m_instance;

Logger::Logger()
{
	m_filePath = "./results.csv";
}

Logger::~Logger()
{
	m_instance = NULL;
}

Logger* Logger::getInstance()
{
	if (m_instance == NULL)
	{
		m_instance = new Logger();
	}
	return m_instance;
}

void Logger::setFilePath( std::string filePath )
{
	m_filePath = filePath;
}

void Logger::csvLog(std::string argv[], int argc)
{
	std::ofstream outputFile;
	outputFile.open(m_filePath.c_str(), std::ios_base::app);
	std::string outputString = "";
	for (int idx = 0; idx < argc; idx++)
	{
		std::ostringstream stringStream;
		stringStream << argv[idx];
		outputString += stringStream.str() + std::string(",");
	}
	outputFile << outputString << "\n";
	outputFile.close();
}

void Logger::csvLog( double argv[], int argc )
{
	std::ofstream outputFile;
	outputFile.open( m_filePath.c_str(), std::ios_base::app );
	std::string outputString = "";
	for ( int idx = 0; idx < argc; idx++ ) 
	{
		std::ostringstream stringStream;
		stringStream << argv[idx];
		outputString += stringStream.str() + std::string(",");
	}
	outputFile << outputString << "\n";
	outputFile.close();
}

void Logger::insertNewLine()
{
	std::ofstream outputFile;
	outputFile.open(m_filePath.c_str(), std::ios_base::app);
	outputFile << "\n";
	outputFile.close();
}
