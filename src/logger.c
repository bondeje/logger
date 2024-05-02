#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <logger.h>

struct Logger base_logger = DEFAULT_LOGGER_INIT;

size_t logger_required_args(char const * format, size_t format_size) {
    return 0;
}

int base_logger_log(struct Logger * logger, char * buffer, size_t buffer_size, va_list args) {
    char const * message = va_arg(args, char const *); // this should use vsnprintf to populate the buffer
    return vsnprintf(buffer, buffer_size, message, args);
}

int Logger_init(struct Logger * logger, char const * filename, char const * format, size_t buffer_size, unsigned char max_logging_level, unsigned char min_narg, log_func * log, char const * name) {

    if (!format) {
        format = "%s";
    }
    logger->format = format;

    if (!buffer_size) {
        buffer_size = DEFAULT_LOGGER_BUFFER_SIZE;
    }
    logger->buffer = malloc(sizeof(char) * buffer_size);
    if (!logger->buffer) {
        goto fail_buffer_alloc;
    }
    logger->buffer_size = buffer_size;
    logger->max_logging_level = max_logging_level > MAX_LOGGING_LEVEL ? MAX_LOGGING_LEVEL : max_logging_level;

    if (!min_narg) {
        min_narg = 1;
    }
    logger->min_narg = min_narg;

    if (!log) {
        log = &base_logger_log;
    }
    logger->log = log;

    if (!name) {
        name = "unnamed";
    }
    logger->name = name;

    if (!filename || !strcmp(filename, "stdout")) {
        logger->stream = stdout;
    } else if (!strcmp(filename, "stderr")) {
        logger->stream = stderr;
    } else {

        FILE * file = fopen(filename, "rb");
        if (!file) {
            goto fail_fopen;
        }
        long file_size = ftell(file);
        if (file_size < 0) {
            goto fail_ftell;
        }
        if (fseek(file, 0, SEEK_END)) {
            goto fail_fseek;
        }
        file_size = ftell(file) - file_size;

        logger->stream = freopen(filename, "ab+", file);
        if (file_size) {
            fprintf(logger->stream, "\nlogging started for %s at {need to add date time}\n", logger->name);
        } else {
            fprintf(logger->stream, "logging started for %s at {need to add date time}\n", logger->name);
        }        
    }
    return 0;
fail_fseek:
fail_ftell:
fail_fopen:
    free(logger->buffer);
    logger->buffer = NULL;
fail_buffer_alloc:
    logger->buffer_size = 0;
    return 1;
}

void Logger_dest(struct Logger * logger) {
    if (logger->stream && logger->stream != stdout && logger->stream != stderr) {
        fclose(logger->stream);
        logger->stream = NULL;
    }
    if (logger->buffer) {
        free(logger->buffer);
        logger->buffer = NULL;
        logger->buffer_size = 0;
    }
}

void Logger_log(struct Logger * logger, char const * file, char const * func, size_t line, int level, size_t n, ...) {
    if (!logger) {
        logger = &base_logger;
    }
    if (logger->stream == NULL) { // initialize logger to system level logger to stdout
        // initialize the logger to stdin with default parameters
        LOG_INIT(logger, NULL, NULL, 0, MAX_LOGGING_LEVEL, 1, NULL, logger->name);
        
        // post to the base_logger that an uninitialized logger was triggered
        if (logger->stream == NULL) {
            LOG_EVENT(&base_logger, LOG_LEVEL_INFO, "%d - %s - failed to initialized logger %s with default parameters", LOG_LEVEL_INFO, base_logger.name, logger->name);
            return;
        } else {
            LOG_EVENT(&base_logger, LOG_LEVEL_INFO, "%d - %s - initialized logger %s with default parameters", LOG_LEVEL_INFO, base_logger.name, logger->name);
        }
        
    }
    if (level <= logger->max_logging_level && level) {
        if (logger->min_narg > n) {
            LOG_EVENT(&base_logger, LOG_LEVEL_WARN, "%d - %s - malformed LOG_EVENT. Logger %s expected at least %zu args and received %zu. file: %s, function: %s, line: %s\n", LOG_LEVEL_WARN, base_logger.name, logger->name, logger->min_narg, n, file, line, func);
        }
        // need to allocate and initialize a buffer based on the logger data (format string to determine which metadata is needed and a minimum buffer_size)
        va_list args;
        va_start(args, n);
        int written = logger->log(logger, logger->buffer, logger->buffer_size-2, args);
        // TODO: need to check for errors in written

        // this is not necessarily the place I want to put them.
        if (logger->buffer[written-1] != '\n') {
            logger->buffer[written++] = '\n';
        }        
        logger->buffer[written++] = '\0';
        fprintf(logger->stream, logger->format, logger->buffer);
        if (logger->stream != stdout && (level == LOG_LEVEL_ERROR || level == LOG_LEVEL_WARN || level == LOG_LEVEL_ERROR)) {
            fprintf(stdout, logger->format, logger->buffer);
        }
        va_end(args);
    }    
}