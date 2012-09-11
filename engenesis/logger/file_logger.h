#ifndef FILE_LOGGER_H_INCLUDED
#define FILE_LOGGER_H_INCLUDED

#include "logger.h"
#include <fstream>

namespace egn
{

    class EGNAPI FileLogger : public ILogger
    {
        public:
            /**
            * @brief Default constructor
            * @param filename The file to write the logs in
            */
            FileLogger(const char* filename);

            /**
            * @brief Destructor
            */
            virtual ~FileLogger();


            /**
            * @brief Returns the ostream to log a message (without prefixe)
            */
            virtual std::ostream& stream();

            /**
            * @brief Returns the ostream to log a message after having prefixed it.
            */
            virtual std::ostream& stream(SeverityInfo severity, const char* file, int line);



        private:
            std::ofstream       _file; ///< Output file

            /**
            * Prevent from copy
            */
            FileLogger(const FileLogger&);

            /**
            * Prevent from copy
            */
            FileLogger& operator=(const FileLogger&);
    };

}

#endif // FILE_LOGGER_H_INCLUDED
