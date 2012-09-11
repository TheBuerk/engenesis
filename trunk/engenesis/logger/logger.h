#ifndef LOGGER_H_INCLUDED
#define LOGGER_H_INCLUDED

#include "../main.h"
#include <ostream>

namespace egn
{
    /**
    * @brief Defines the different level of logging informations
    */
    enum SeverityInfo
    {
        SeverityInformation = 0,
        SeverityWarning,
        SeverityError,
        SeverityFatal,
        SeverityUnknown
    };

    /**
    * @brief Error types
    */
    enum StatusType
    {
        StatusResourceNotFound = -4 ,
        StatusFileNotFound = -3 ,
        StatusGameInitFailed = -2,
        StatusError = -1 ,
        StatusNoError = 0
    };


    /**
    * @class ILogger
    * @brief Interface for any kind of Logger (File, Stream, ...)
    */
    class EGNAPI ILogger
    {
        public:
            /**
            * @brief Destructor
            */
            virtual ~ILogger();

            /**
            * @brief Returns an instance on the actual Logger, or NULL if none has been created
            */
            static ILogger* logger();



            // Pure Virtual

            /**
            * @brief Returns the ostream to log a message (without prefixe)
            */
            virtual std::ostream& stream() = 0;

            /**
            * @brief Returns the ostream to log a message after having prefixed it.
            */
            virtual std::ostream& stream(SeverityInfo severity, const char* file, int line) = 0;


        protected:
            /**
            * Prevent from copy, except for children
            */
            ILogger();

            /**
            * @brief Write the date and file info in the given ostream
            */
            void writeTag(std::ostream& os, SeverityInfo severity, const char* file, int line);

        private:
            static ILogger*  _logger; ///< The logger instance

            /**
            * Prevent from copy
            */
            ILogger(const ILogger&);

            /**
            * Prevent from copy
            */
            ILogger& operator=(const ILogger&);
    };

}

#endif // LOGGER_H_INCLUDED
