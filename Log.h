#ifndef LOG_H
#define LOG_H

#include <string>

std::string intToString(const int argv);
std::string doubleToString(const double argv);

class Logger
{
public:
	virtual ~Logger();
	static Logger* getInstance();
	void setFilePath( std::string filePath );
	void csvLog( std::string argv[], int argc);
	void csvLog( double argv[], int argc );
	void insertNewLine();
	
private:
	static Logger* m_instance;
	std::string m_filePath;
	Logger();
};

#endif // LOG_H