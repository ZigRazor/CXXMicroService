#ifndef __MICROSERVICE_LOGGER_H__
#define __MICROSERVICE_LOGGER_H__

#ifdef MS_LOGGER
#include <log4cxx/logger.h>
#include <log4cxx/xml/domconfigurator.h>
#include <sys/time.h>
#include <unistd.h>
#else
#include <iostream>
#endif // LOGGER


#ifdef MS_LOGGER
#define MICROSERVICE_LOG_LOGGER  log4cxx::LoggerPtr
#else
#define MICROSERVICE_LOG_LOGGER  void*
#endif // LOGGER

#ifdef MS_LOGGER
#define MICROSERVICE_LOG_CHECK_CONFIG_FILE_PERIOD 3000
#else
#define MICROSERVICE_LOG_CHECK_CONFIG_FILE_PERIOD
#endif // MS_LOGGER

#ifdef MS_LOGGER
#define MICROSERVICE_LOG_TRACE TRACE
#define MICROSERVICE_LOG_DEBUG DEBUG
#define MICROSERVICE_LOG_INFO  INFO
#define MICROSERVICE_LOG_WARN  WARN
#define MICROSERVICE_LOG_ERROR ERROR
#define MICROSERVICE_LOG_FATAL FATAL
#else
#define MICROSERVICE_LOG_TRACE "TRACE"
#define MICROSERVICE_LOG_DEBUG "DEBUG"
#define MICROSERVICE_LOG_INFO  "INFO"
#define MICROSERVICE_LOG_WARN  "WARN"
#define MICROSERVICE_LOG_ERROR "ERROR"
#define MICROSERVICE_LOG_FATAL "FATAL"
#endif // MS_LOGGER


#ifdef MS_LOGGER
#define MICROSERVICE_LOG_INIT(xmlConfigFile) {                                   \
    struct timeval t;                                                   \
    gettimeofday (&t, NULL);                                            \
    struct tm* time = localtime(&(t.tv_sec));                           \
    char date_str[32];                                                  \
    strftime(date_str, sizeof(date_str), "%Y-%m-%d_%H:%M:%S", time);    \
    char buffer[64];                                                    \
    sprintf ( buffer, "%s_%d", date_str, getpid() );                    \
    setenv( "MICROSERVICE_LOG_PID_DATE", buffer, 1 );                            \
    log4cxx::xml::DOMConfigurator::configureAndWatch( xmlConfigFile,MICROSERVICE_LOG_CHECK_CONFIG_FILE_PERIOD ); }
#else
#define MICROSERVICE_LOG_INIT(xmlConfigFile)
#endif // MS_LOGGER

#ifdef MS_LOGGER
#define MICROSERVICE_LOG_GET_LOGGER( logger, loggerName ) logger = log4cxx::Logger::getLogger( loggerName )
#else
#define MICROSERVICE_LOG_GET_LOGGER( logger, loggerName ) logger = nullptr
#endif // MS_LOGGER

#define MICROSERVICE_LOG(level, logger, msg) MICROSERVICE_LOG_HELPER(level, logger, msg)

// for internal use only
#ifdef MS_LOGGER
#define MICROSERVICE_LOG_HELPER(level, logger, msg) LOG4CXX_##level( logger, msg )
#else
#define MICROSERVICE_LOG_HELPER(level, logger, msg) std::cout << level << " " << msg << std::endl;
#endif // MS_LOGGER

#endif // __MICROSERVICE_LOGGER_H__

