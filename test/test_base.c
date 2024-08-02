#include <stdio.h>

#include <logger.h>

int main(void) {
    Logger file_log;
    char * buf = NULL;
    switch (MAX_LOGGING_LEVEL) {
        case LOG_LEVEL_DISABLE: {
            buf = "LOG_LEVEL_DISABLE";
            break;
        }
        case LOG_LEVEL_FATAL: {
            buf = "LOG_LEVEL_FATAL";
            break;
        }
        case LOG_LEVEL_ERROR: {
            buf = "LOG_LEVEL_ERROR";
            break;
        }
        case LOG_LEVEL_WARN: {
            buf = "LOG_LEVEL_WARN";
            break;
        }
        case LOG_LEVEL_INFO: {
            buf = "LOG_LEVEL_INFO";
            break;
        }
        case LOG_LEVEL_DEBUG: {
            buf = "LOG_LEVEL_DEBUG";
            break;
        }
        case LOG_LEVEL_TRACE: {
            buf = "LOG_LEVEL_TRACE";
            break;
        }
    }
    printf("max logging level set to %s\n", buf);
    LOG_INIT(&file_log, "bin/test_base.log", NULL, 0, LOG_LEVEL_INFO, 0, NULL, "test base logger");
    LOG_EVENT(&file_log, LOG_LEVEL_FATAL, "this is a fatal event to a file & stderr");
    LOG_EVENT(&file_log, LOG_LEVEL_ERROR, "this is an error event to a file & stderr");
    LOG_EVENT(&file_log, LOG_LEVEL_WARN, "this is a warn event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_INFO, "this is an info event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_DEBUG, "this is a debug event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_TRACE, "this is a trace event to a file");

    LOG_EVENT(NULL, LOG_LEVEL_FATAL, "this is a fatal event to stdout && stderr");
    LOG_EVENT(NULL, LOG_LEVEL_ERROR, "this is an error event to stdout && stderr");
    LOG_EVENT(NULL, LOG_LEVEL_WARN, "this is a warn event to stdout");
    LOG_EVENT(NULL, LOG_LEVEL_INFO, "this is an info event to stdout");
    LOG_EVENT(NULL, LOG_LEVEL_DEBUG, "this is a debug event to stdout");
    LOG_EVENT(NULL, LOG_LEVEL_TRACE, "this is a trace event to a stdout");

    file_log.max_logging_level = LOG_LEVEL_DISABLE;

    // none of these should ever be logged anywhere
    LOG_EVENT(&file_log, LOG_LEVEL_FATAL, "this is a disabled fatal event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_ERROR, "this is a disabled error event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_WARN, "this is a disabled warn event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_INFO, "this is a disabled info event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_DEBUG, "this is a disabled debug event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_TRACE, "this is a disabled trace event to a file");

    LOG_DEST(&file_log);
    LOG_DEST(APP_LOGGER);

    return 0;
}