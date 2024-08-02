#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>
#include <stdarg.h>
#include <stdio.h>

#ifndef CAT
    #define CAT_(X, Y) X##Y
    #define CAT(X, Y) CAT_(X, Y)
#endif

#define CATD_(left, right, delim) left##delim##right
#define CATD(left, right, delim) CATD_(left, right, delim)

#ifndef CAT3
    #define CAT3_(X, Y, Z) X##Y##Z
    #define CAT3(X, Y, Z) CAT3_(X, Y, Z)
#endif

#ifndef VARIADIC_SIZE
    #define VARIADIC_SIZE(...) VARIADIC_SIZE_(__VA_ARGS__, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, UNUSED)
    #define VARIADIC_SIZE_(_1, _2, _3, _4, _5, _6, _7, _8, _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, _21, _22, _23, _24, _25, _26, _27, _28, _29, _30, _31, _32, _33, _34, _35, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, size, ...) size
#endif

/* begin horrifying macro magic that allows one to compare logging levels so that MAX_LOGGING_LEVEL and DISABLE_LOGGING remove logs */
#define T_AT_0(_0, ...) _0
#define T_AT_1(_0,_1,...) _1
#define T_AT_2(_0,_1,_2,...) _2
#define T_AT_3(_0,_1,_2,_3,...) _3
#define T_AT_4(_0,_1,_2,_3,_4,...) _4
#define T_AT_5(_0,_1,_2,_3,_4,_5,...) _5
#define T_AT_6(_0,_1,_2,_3,_4,_5,_6,...) _6
#define T_AT_7(_0,_1,_2,_3,_4,_5,_6,_7,...) _7
#define T_AT_8(_0,_1,_2,_3,_4,_5,_6,_7,_8,...) _8
#define T_AT_9(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,...) _9
#define T_AT_10(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,...) _10
#define T_INSPECT_0(...) T_AT_0(__VA_ARGS__, UNUSED)
#define T_INSPECT_1(...) T_AT_1(__VA_ARGS__, UNUSED)
#define T_INSPECT_2(...) T_AT_2(__VA_ARGS__, UNUSED)
#define T_INSPECT_3(...) T_AT_3(__VA_ARGS__, UNUSED)
#define T_INSPECT_4(...) T_AT_4(__VA_ARGS__, UNUSED)
#define T_INSPECT_5(...) T_AT_5(__VA_ARGS__, UNUSED)
#define T_INSPECT_6(...) T_AT_6(__VA_ARGS__, UNUSED)
#define T_INSPECT_7(...) T_AT_7(__VA_ARGS__, UNUSED)
#define T_INSPECT_8(...) T_AT_8(__VA_ARGS__, UNUSED)
#define T_INSPECT_9(...) T_AT_9(__VA_ARGS__, UNUSED)
#define T_INSPECT_10(...) T_AT_10(__VA_ARGS__, UNUSED)

#define LOGGER_REP_0(x) x
#define LOGGER_REP_1(x) x, x
#define LOGGER_REP_2(x) x, x, x
#define LOGGER_REP_3(x) x, x, x, x
#define LOGGER_REP_4(x) x, x, x, x, x
#define LOGGER_REP_5(x) x, x, x, x, x, x
#define LOGGER_REP_6(x) x, x, x, x, x, x, x
#define LOGGER_REP_7(x) x, x, x, x, x, x, x, x
#define LOGGER_REP_8(x) x, x, x, x, x, x, x, x, x
#define LOGGER_REP_9(x) x, x, x, x, x, x, x, x, x, x
#define LOGGER_REP_10(x) x, x, x, x, x, x, x, x, x, x, x

/* the magic: if x <= the last number in the macro name, the result of the macro is 1 else 0 */
#define LOGGER_LESS_THAN_EQ_0(x) T_INSPECT_1(CAT(LOGGER_REP_, x)(0), LOGGER_REP_0(1))
#define LOGGER_LESS_THAN_EQ_1(x) T_INSPECT_2(CAT(LOGGER_REP_, x)(0), LOGGER_REP_1(1))
#define LOGGER_LESS_THAN_EQ_2(x) T_INSPECT_3(CAT(LOGGER_REP_, x)(0), LOGGER_REP_2(1))
#define LOGGER_LESS_THAN_EQ_3(x) T_INSPECT_4(CAT(LOGGER_REP_, x)(0), LOGGER_REP_3(1))
#define LOGGER_LESS_THAN_EQ_4(x) T_INSPECT_5(CAT(LOGGER_REP_, x)(0), LOGGER_REP_4(1))
#define LOGGER_LESS_THAN_EQ_5(x) T_INSPECT_6(CAT(LOGGER_REP_, x)(0), LOGGER_REP_5(1))
#define LOGGER_LESS_THAN_EQ_6(x) T_INSPECT_7(CAT(LOGGER_REP_, x)(0), LOGGER_REP_6(1))
#define LOGGER_LESS_THAN_EQ_7(x) T_INSPECT_8(CAT(LOGGER_REP_, x)(0), LOGGER_REP_7(1))
#define LOGGER_LESS_THAN_EQ_8(x) T_INSPECT_9(CAT(LOGGER_REP_, x)(0), LOGGER_REP_8(1))
#define LOGGER_LESS_THAN_EQ_9(x) T_INSPECT_10(CAT(LOGGER_REP_, x)(0), LOGGER_REP_9(1))

/* the magic: returns the lower of the last number in the macro name and x */
#define LOGGER_LOWER_0(x) T_INSPECT_1(CAT(LOGGER_REP_, x)(0), LOGGER_REP_0(x))
#define LOGGER_LOWER_1(x) T_INSPECT_2(CAT(LOGGER_REP_, x)(1), LOGGER_REP_1(x))
#define LOGGER_LOWER_2(x) T_INSPECT_3(CAT(LOGGER_REP_, x)(2), LOGGER_REP_2(x))
#define LOGGER_LOWER_3(x) T_INSPECT_4(CAT(LOGGER_REP_, x)(3), LOGGER_REP_3(x))
#define LOGGER_LOWER_4(x) T_INSPECT_5(CAT(LOGGER_REP_, x)(4), LOGGER_REP_4(x))
#define LOGGER_LOWER_5(x) T_INSPECT_6(CAT(LOGGER_REP_, x)(5), LOGGER_REP_5(x))
#define LOGGER_LOWER_6(x) T_INSPECT_7(CAT(LOGGER_REP_, x)(6), LOGGER_REP_6(x))
#define LOGGER_LOWER_7(x) T_INSPECT_8(CAT(LOGGER_REP_, x)(7), LOGGER_REP_7(x))
#define LOGGER_LOWER_8(x) T_INSPECT_9(CAT(LOGGER_REP_, x)(8), LOGGER_REP_8(x))
#define LOGGER_LOWER_9(x) T_INSPECT_10(CAT(LOGGER_REP_, x)(9), LOGGER_REP_9(x))

// disable at the logger level
#define LOG_LEVEL_DISABLE 0
// errors that cause crashes
#define LOG_LEVEL_FATAL 1
// errors that likely, eventually cause crashes
#define LOG_LEVEL_ERROR 2
// warnings of bad or undesirable uses
#define LOG_LEVEL_WARN 3
// high level runtime sequences. Never put these as part of calculations, 
// e.g. in initialization/destruction stages or starting major activities
#define LOG_LEVEL_INFO 4
// detailed control flow. Put these at all sequences not covered above, but not
// calculations
#define LOG_LEVEL_DEBUG 5
// most detailed control flow. Put these in calculations
#define LOG_LEVEL_TRACE 6
// DO NOT USE. for macros
// not currently used but eventually to signal that it should grab logging level from a different logger
#define LOG_LEVEL_NOT_SET 7

#ifndef DEFAULT_LOGGING_LEVEL
    #define DEFAULT_LOGGING_LEVEL CAT(LOGGER_LOWER_, LOG_LEVEL_WARN)(MAX_LOGGING_LEVEL)
#endif 

// The MAX_LOGGING_LEVEL and DISABLE_LOGGING modify this
#define LOG_EVENT_(pLogger, level, ...)

// disable logging globally, this turns logging macros so that they are no cost
#if defined(DISABLE_LOGGING) || (defined(MAX_LOGGING_LEVEL) && MAX_LOGGING_LEVEL == LOG_LEVEL_DISABLE)
    #ifndef MAX_LOGGING_LEVEL
        #define MAX_LOGGING_LEVEL LOG_LEVEL_DISABLE
    #endif
    // main logging macro. Should never be called directly
    #define LOG_EVENT_0(pLogger, level, ...) do {} while (0)
    #define LOG_EVENT_1(pLogger, level, ...) do {} while (0)
    #define LOG_INIT(...) do {} while (0)
    #define LOG_DEST(pLogger) do {} while (0)
    #define APP_LOGGER NULL
#else 
    #ifndef MAX_LOGGING_LEVEL
        #define MAX_LOGGING_LEVEL LOG_LEVEL_INFO
    #endif
    // main logging macro. Should never be called directly
    #define LOG_EVENT_0(pLogger, level, ...) do {} while (0)
    #define LOG_EVENT_1(pLogger, level, ...) Logger_log(pLogger, __FILE__, __func__, __LINE__, level, VARIADIC_SIZE(__VA_ARGS__), __VA_ARGS__)
    #define LOG_INIT(...) Logger_init(__VA_ARGS__)
    #define LOG_DEST(pLogger) Logger_dest(pLogger)
    #define APP_LOGGER &base_logger
#endif

#define LOG_EVENT(pLogger, level, ...) CAT(LOG_EVENT_, CATD(LOGGER_LESS_THAN_EQ,MAX_LOGGING_LEVEL,_)(level))(pLogger, level, __VA_ARGS__)

#ifndef MAX_NAME_SIZE
    #define MAX_NAME_SIZE 256
#endif

typedef struct Logger Logger;

typedef int log_func(struct Logger * logger, char * buffer, size_t buffer_size, va_list args);

struct Logger {
    FILE * stream;
    char const * format; // null-terminated string
    char * buffer;
    size_t buffer_size;
    log_func * log;
    char const * name;
    unsigned char min_narg;
    unsigned char max_logging_level;
};

#define DEFAULT_LOGGER_BUFFER_SIZE 1024

#define DEFAULT_LOGGER_INIT { \
    .max_logging_level = DEFAULT_LOGGING_LEVEL, \
    .stream = NULL, \
    .format = "%s", /* this is a default format which just accepts the char * buffer modified after call to .log */ \
    .buffer = NULL, \
    .buffer_size = 0, \
    .min_narg = 1, \
    .log = &base_logger_log, \
    .name = "base_logger" \
}

extern struct Logger base_logger;

// for future use
size_t logger_required_args(char const * format, size_t format_size);

int base_logger_log(struct Logger * logger, char * buffer, size_t buffer_size, va_list args);

int Logger_init(struct Logger * logger, char const * filename, char const * format, size_t buffer_size, unsigned char max_logging_level, unsigned char min_narg, log_func * log, char const * name);

void Logger_dest(struct Logger * logger);

void Logger_log(struct Logger * logger, char const * file, char const * func, size_t line, int level, size_t n, ...);

unsigned char Logger_level_to_uchar(char const * level, size_t length);

void Logger_tear_down(void); // clean up the module

/*
LOG_EVENT(&base_logger, LOG_LEVEL_DISABLE, "test");
LOG_EVENT(&base_logger, LOG_LEVEL_FATAL, "test");
LOG_EVENT(&base_logger, LOG_LEVEL_ERROR, "test");
LOG_EVENT(&base_logger, LOG_LEVEL_WARN, "test");
LOG_EVENT(&base_logger, LOG_LEVEL_INFO, "test");
LOG_EVENT(&base_logger, LOG_LEVEL_DEBUG, "test");
LOG_EVENT(&base_logger, LOG_LEVEL_TRACE, "test");
*/

#endif // LOGGER_H

