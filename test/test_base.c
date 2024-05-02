#include <stdio.h>

#include <logger.h>

int main(void) {
    Logger file_log;
    LOG_INIT(&file_log, "bin/test_base.log", NULL, 0, LOG_LEVEL_INFO, 0, NULL, "test base logger");
    LOG_EVENT(&file_log, LOG_LEVEL_FATAL, "this is a fatal event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_ERROR, "this is an error event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_WARN, "this is a warn event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_INFO, "this is an info event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_DEBUG, "this is a debug event to a file");
    LOG_EVENT(&file_log, LOG_LEVEL_TRACE, "this is a trace event to a file");

    LOG_EVENT(NULL, LOG_LEVEL_FATAL, "this is a fatal event to stdout");
    LOG_EVENT(NULL, LOG_LEVEL_ERROR, "this is an error event to stdout");
    LOG_EVENT(NULL, LOG_LEVEL_WARN, "this is a warn event to stdout");
    LOG_EVENT(NULL, LOG_LEVEL_INFO, "this is an info event to stdout");
    LOG_EVENT(NULL, LOG_LEVEL_DEBUG, "this is a debug event to stdout");
    LOG_EVENT(NULL, LOG_LEVEL_TRACE, "this is a trace event to a file");

    file_log.max_logging_level = LOG_LEVEL_DISABLE;

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