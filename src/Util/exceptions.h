/**
 * exceptions.h
 *
 *
 * Copyright(c) 2001 Thiago Maia, Andre Senna
 * All rights reserved.
 */

#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string>
#include <stdarg.h>
#include <string.h>

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define TRACE_INFO " ("__FILE__":"TOSTRING(__LINE__)")"

/**
 * Base exception class from which all other exceptions should inheritates.
 */
class StandardException{
 
    private:
        /**
         * c-string error message
         */
        char * message;

    protected:

        /**
         * Parse error message substituting scape characters like (%s, %d, etc)
         * with their corresponding values. 
         */
        void parseErrorMessage(const char* fmt, va_list ap);

    public:

        /**
         * Construtor and destructor.
         */
        StandardException();
        ~StandardException();
        
        /**
         * Get error message.
         * @return A c-string representing the error message. If no message have
         * been created just return an empty string.
         */
	    const char* getMessage();
        
        /**
         * Set the error message.
         * @param A c-string representing the error message. The caller is
         * responsable to free the memory allocated in the c-string parameter.
         */
        void setMessage(const char *);

}; // StandardException

/**
 * Generic exception to be called in runtime, whenever an unexpected condition
 * is detected.
 */
class RuntimeException : public StandardException {
    
    public:

        /**
         * Generic exception to be called in runtime, whenever an unexpected
         * condition is detected.
         *
         * @param Exception message in printf standard format.
         */
        RuntimeException(const char*, const char*, ...);

        /**
         * Default constructor used for inheritance 
         */
        RuntimeException();

        /**
         * Destructor
         */
        ~RuntimeException();

}; // RuntimException

/**
 * Exception to be thrown when a XML operation (processing, creation) fails.
 */
class XMLException : public RuntimeException {

    public:

        /**
         * Constructor
         *
         * @param Trace information (filename:line-number). Use TRACE_INFO
         * macro.
         * @param Exception message in printf standard format.
         */
        XMLException(const char*, const char*, ...);

}; // XMLException

/**
 * Exception to be thrown when an I/O operation (reading, writing, open) fails.
 */
class IOException : public RuntimeException {

    public:

        /**
         * Constructor
         *
         * @param Trace information (filename:line-number). Use TRACE_INFO
         * macro.
         * @param Exception message in printf standard format.
         */
        IOException(const char*, const char*, ...);

}; // IOException

/**
 * Exception to be thrown when a Combo operation (parsing, executing) fails.
 */
class ComboException : public RuntimeException {

    public:

        /**
         * Constructor
         *
         * @param Trace information (filename:line-number). Use TRACE_INFO
         * macro.
         * @param Exception message in printf standard format.
         */
        ComboException(const char*, const char*, ...);

}; // ComboException

/**
 * Exception to be thrown when an out of range index is used.
 */
class IndexErrorException : public RuntimeException {

    public:

        /**
         * Constructor
         *
         * @param Trace information (filename:line-number). Use TRACE_INFO
         * macro.
         * @param Exception message in printf standard format.
         */
        IndexErrorException(const char*, const char*, ...);

}; // IndexErrorException

/**
 * Exception to be thrown when an invalid parameter is used within a function or
 * an object initalization.
 */
class InvalidParamException : public RuntimeException {

    public:

        /**
         * Constructor
         *
         * @param Trace information (filename:line-number). Use TRACE_INFO
         * macro.
         * @param Exception message in printf standard format.
         */
        InvalidParamException(const char*, const char*, ...);

}; // InvalidParamException

/**
 * Exception to be thrown when a consistence check (equals to, different, etc)
 * fails.
 */
class InconsistenceException : public RuntimeException {

    public:

        /**
         * Constructor
         *
         * @param Trace information (filename:line-number). Use TRACE_INFO
         * macro.
         * @param Exception message in printf standard format.
         */
        InconsistenceException(const char*, const char*, ...);

}; // InconsistenceException

/**
 * Exception to be called when an unrecoverable error has occured. When catching
 * such exception all state savings should be done.
 */
class FatalErrorException : public StandardException {

    public:
        
        /**
         * Constructor
         *
         * @param Trace information (filename:line-number). Use TRACE_INFO
         * macro.
         * @param Exception message in printf standard format.
         */
        FatalErrorException(const char*, const char*, ...);

}; // FatalErrorException

/**
 * Exception to be called when a network error  has occured. When catching
 * such exception all state savings should be done.
 */
class NetworkException : public StandardException {

    public:
        
        /**
         * Constructor
         *
         * @param Trace information (filename:line-number). Use TRACE_INFO
         * macro.
         * @param Exception message in printf standard format.
         */
        NetworkException(const char*, const char*, ...);

}; // NetworkException


/**
 * Exception to be called when an assertion fails to pass a casset function.
 */
class AssertionException {

    public:

        AssertionException(const char*, ...);
        AssertionException(const char* fmt, va_list ap);
};

/**
 * cassert complet with message and trace info
 */
void cassert(const char * trace,  bool condition, const char * msg, ...);

/**
 * cassert without message. Just trace information
 */
void cassert(const char * trace, bool condition);

#endif
