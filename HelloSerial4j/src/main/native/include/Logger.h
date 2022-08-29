#ifndef LOGGER

#define LOGGER

#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>
#include<ErrnoUtils.h>

typedef const char* AlertType;

#define INFO ((AlertType) "Info")
#define WARNING ((AlertType) "Warning")
#define OK ((AlertType) "Status Ok")
#define FAILURE ((AlertType) "Failed")
#define SUCCESS ((AlertType) "Succeeded")

#define LOGGER_FORMAT ((const char*) "%s::%s: %s \n\r")

namespace Logger {

    static int loggingEnabled = 0;

    static inline void setLoggingEnabled() {
        Logger::loggingEnabled = 1;
    }

    static inline void setLoggingDisabled() {
        Logger::loggingEnabled = 0;
    }

    static inline int* isLoggingEnabled() {
        return &loggingEnabled;
    }

    static inline int LOG(const char* API_LABEL, AlertType ALERT_TYPE, const char* MSG) {
        if (!*(isLoggingEnabled())) {
            return LOGGER_DISABLED;
        }
        return printf(LOGGER_FORMAT, API_LABEL, ALERT_TYPE, MSG);
    }

    static inline int LOGI(const char* API_LABEL, const char* MSG) {
        return LOG(API_LABEL, INFO, MSG);
    }

    static inline int LOGW(const char* API_LABEL, const char* MSG) {
        return LOG(API_LABEL, WARNING, MSG);
    }

    static inline int LOGF(const char* API_LABEL, const char* MSG) {
        return LOG(API_LABEL, FAILURE, MSG);
    }  

    static inline int LOGS(const char* API_LABEL, const char* MSG) {
        return LOG(API_LABEL, SUCCESS, MSG);
    }   
 
    static inline int LOG_OK(const char* API_LABEL, const char* MSG) {
        return LOG(API_LABEL, OK, MSG);
    }
}

#endif