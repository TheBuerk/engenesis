#include "file_logger.h"


using namespace egn;


FileLogger::FileLogger(const char* filename) : ILogger()
{
    _file.open(filename);
    if(!_file.is_open())
    {
        exit(StatusFileNotFound);
    }
}


FileLogger::~FileLogger()
{
    if(_file.is_open())
    {
        _file.close();
    }
}


std::ostream& FileLogger::stream()
{
    std::ostream* result = NULL;
    if(_file.is_open())
    {
        result = &_file;
    }

    return *result;
}


std::ostream& FileLogger::stream(SeverityInfo severity, const char* file, int line)
{
    std::ostream* result = NULL;
    if(_file.is_open())
    {
        result = &_file;
        writeTag(_file, severity, file, line);
    }

    return *result;
}
