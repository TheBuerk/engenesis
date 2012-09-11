#ifndef LOGGER_MACROS_H_INCLUDED
#define LOGGER_MACROS_H_INCLUDED

#define LOG \
  egn::ILogger::logger()->stream(egn::SeverityInformation, __FILE__, __LINE__)

#define ILOG \
  egn::ILogger::logger()->stream(egn::SeverityInformation, __FILE__, __LINE__)

#define WLOG \
  egn::ILogger::logger()->stream(egn::SeverityWarning, __FILE__, __LINE__)

#define ELOG \
  egn::ILogger::logger()->stream(egn::SeverityError, __FILE__, __LINE__)

#define FLOG \
  egn::ILogger::logger()->stream(egn::SeverityFatal, __FILE__, __LINE__)



#endif // LOGGER_MACROS_H_INCLUDED
