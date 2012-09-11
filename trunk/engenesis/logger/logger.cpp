#include "logger.h"
#include <ctime>


using namespace egn;

ILogger* ILogger::_logger = NULL;


ILogger::ILogger()
{
    _logger = this;
}


ILogger::~ILogger()
{
    if(_logger == this)
        _logger = NULL;
}


ILogger* ILogger::logger()
{
    return _logger;
}


void ILogger::writeTag(std::ostream& os, SeverityInfo severity, const char* file, int line)
{
    const std::tm* tm; // Time structure pointer
    std::time_t now;

    // Get current timestamp
    now = std::time(NULL);

    // Convert current time to local time
    tm = std::localtime(&now);

    // Output time with US format
    os << tm->tm_year + 1900 << "-";
    os.fill('0');
    os.width(2);
    os << tm->tm_mon + 1 << "-";
    os.fill('0');
    os.width(2);
    os << tm->tm_mday << " ";
    os.fill('0');
    os.width(2);
    os << tm->tm_hour + 1 << ":";
    os.fill('0');
    os.width(2);
    os << tm->tm_min << ":";
    os.fill('0');
    os.width(2);
    os << tm->tm_sec << " ";

    // Output the seveity, represented by a caracter
    switch(severity)
    {
        case SeverityInformation:
            os << "I";
            break;

        case SeverityWarning:
            os << "W";
            break;

        case SeverityError:
            os << "E";
            break;

        case SeverityFatal:
            os << "F";
            break;

        case SeverityUnknown:
        default:
            os << "?";
            break;
    }

    // Output file and line
    os << " " << file << ":" << line << " ";
}
