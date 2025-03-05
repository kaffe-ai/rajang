/**
 * @authors
 * Odin Bjerke <odin.bjerke@uit.no>
 *
 * @brief Defines printf-like macros. Optional meta-information and color-coded output.
 *
 * @details
 * Defines the following macros:
 * - pr_error(fmt, ...)
 * - pr_warn(fmt, ...)
 * - pr_info(fmt, ...)
 * - pr_debug(fmt, ...)
 * - assert(assertion)
 * - assertf(assertion, fmt, ...)
 * - PANIC(fmt, ...)
 *
 * @note
 * if NDEBUG is defined, asserts and non-error prints will do nothing, and their invocations are optimized
 * away by the compiler.
 */

#ifndef PRINTING_H
#  define PRINTING_H

#  include <stdio.h>
#  include <stdlib.h>
#  include <sys/cdefs.h>

enum {
    LOG_LEVEL_PANIC = 0, /* minimum log level. only prints on PANIC. */
    LOG_LEVEL_ERROR,     /* enable pr_error */
    LOG_LEVEL_WARN,      /* enable pr_warn (+ pr_error) */
    LOG_LEVEL_INFO,      /* enable pr_info (+ pr_error, pr_warn) */
    LOG_LEVEL_DEBUG      /* enable pr_debug (+ pr_error, pr_warn, pr_info) */
};

/*************/
/** OPTIONS **/
/*************/

#  ifndef LOG_LEVEL
/* default log level.  */
#    define LOG_LEVEL LOG_LEVEL_DEBUG
#  endif

/* define to remove colors */
// #define PRINTING_NCOLOR

/* define to remove meta info (e.g. file/line) */
// #define PRINTING_NMETA

/* target for pr_info */
#  define INFO_STREAM stderr

/********************/
/** END OF OPTIONS **/
/********************/

/**** regular ansi colors ****/

#  define ANSI_COLOR_RESET "\033[0m"
#  define ANSI_COLOR_BLA   "\033[0;30m"
#  define ANSI_COLOR_RED   "\033[0;31m"
#  define ANSI_COLOR_GRE   "\033[0;32m"
#  define ANSI_COLOR_YEL   "\033[0;33m"
#  define ANSI_COLOR_BLU   "\033[0;34m"
#  define ANSI_COLOR_PUR   "\033[0;35m"
#  define ANSI_COLOR_CYA   "\033[0;36m"
#  define ANSI_COLOR_WHI   "\033[0;37m"


#  ifdef PRINTING_NCOLOR
#    define COLOR_RESET
#    define COLOR_PR_ERROR
#    define COLOR_PR_WARN
#    define COLOR_PR_DEBUG
#    define COLOR_PR_INFO
#  else
#    define COLOR_RESET    ANSI_COLOR_RESET
#    define COLOR_PR_ERROR ANSI_COLOR_RED
#    define COLOR_PR_WARN  ANSI_COLOR_PUR
#    define COLOR_PR_DEBUG ANSI_COLOR_YEL
#    define COLOR_PR_INFO  ANSI_COLOR_WHI
#  endif /* PRINTING_NCOLOR */

#  ifdef PRINTING_NMETA
#    define META_FILE_LINE_FMT  "%s%s"
#    define META_FILE_LINE_ARGS "", ""
#    define META_FUNC_FMT       "%s"
#    define META_FUNC_ARGS      ""
#    define COLOR_META
#  else
#    define META_FILE_LINE_FMT  "[%s:%d] "
#    define META_FILE_LINE_ARGS __FILE__, __LINE__
#    define META_FUNC_FMT       "%s > "
#    define META_FUNC_ARGS      __func__
#    ifdef PRINTING_NCOLOR
#      define COLOR_META
#    else
#      define COLOR_META ANSI_COLOR_CYA
#    endif /* PRINTING_NCOLOR */
#  endif   /* PRINTING_NMETA */

/* wrap fprintf, only print if log level is sufficient */
#  define do_print_if_lvl(lvl, f, fmt, ...)     \
        do {                                    \
            if (lvl <= LOG_LEVEL) {             \
                fprintf(f, fmt, ##__VA_ARGS__); \
            } else {                            \
                ((void) 0);                     \
            }                                   \
        } while (0)

/* similar to pr_error, but aborts program execution */
#  define PANIC(fmt, ...)                                                              \
        do {                                                                           \
            do_print_if_lvl(LOG_LEVEL_PANIC, stderr,                                   \
                            COLOR_META META_FILE_LINE_FMT META_FUNC_FMT COLOR_PR_ERROR \
                            "[PANIC] " fmt COLOR_RESET,                                \
                            META_FILE_LINE_ARGS, META_FUNC_ARGS, ##__VA_ARGS__);       \
            abort();                                                                   \
        } while (0)

#  ifdef NDEBUG

#    define pr_error(fmt, ...) do_print_if_lvl(LOG_LEVEL_ERROR, stderr, fmt, ##__VA_ARGS__)
#    define pr_warn(fmt, ...)  ((void) 0)
#    define pr_debug(fmt, ...) ((void) 0)
#    define pr_info(fmt, ...)  ((void) 0)

#  else

/* print error. Output is prefixed with file/line and function name (Unless PRINTING_NMETA is defined). */
#    define pr_error(fmt, ...)                                                       \
          do_print_if_lvl(LOG_LEVEL_ERROR, stderr,                                   \
                          COLOR_META META_FILE_LINE_FMT META_FUNC_FMT COLOR_PR_ERROR \
                          "[error] " fmt COLOR_RESET,                                \
                          META_FILE_LINE_ARGS, META_FUNC_ARGS, ##__VA_ARGS__)

/* print warning. Output is prefixed with file/line (Unless PRINTING_NMETA is defined). */
#    define pr_warn(fmt, ...)                                                                       \
          do_print_if_lvl(LOG_LEVEL_WARN, stderr,                                                   \
                          COLOR_META META_FILE_LINE_FMT COLOR_PR_WARN "[warning] " fmt COLOR_RESET, \
                          META_FILE_LINE_ARGS, ##__VA_ARGS__)

/* print debug message. Output is prefixed with file/line and function name (Unless PRINTING_NMETA is
 * defined). */
#    define pr_debug(fmt, ...)                                                                        \
          do_print_if_lvl(LOG_LEVEL_DEBUG, stderr,                                                    \
                          COLOR_META META_FILE_LINE_FMT META_FUNC_FMT COLOR_PR_DEBUG fmt COLOR_RESET, \
                          META_FILE_LINE_ARGS, META_FUNC_ARGS, ##__VA_ARGS__)

/* print info message */
#    define pr_info(fmt, ...) \
          do_print_if_lvl(LOG_LEVEL_INFO, INFO_STREAM, COLOR_PR_INFO fmt COLOR_RESET, ##__VA_ARGS__)


#  endif /* NDEBUG */

#endif /* PRINTING_H */


/* --- intentionally outside of include guard for per-include control --- */

#ifdef assert
#  undef assert
#endif /* assert */

#ifdef assertf
#  undef assertf
#endif /* assertf */

#ifdef NDEBUG

#  define assert(assertion)            ((void) 0)
#  define assertf(assertion, fmt, ...) ((void) 0)

#else

#  define assert(assertion)                                 \
      do {                                                  \
          if (assertion) {                                  \
              ((void) 0);                                   \
          } else {                                          \
              PANIC("assertion `%s` failed\n", #assertion); \
              abort();                                      \
          }                                                 \
      } while (0)

#  define assertf(assertion, fmt, ...)                                         \
      do {                                                                     \
          if (assertion) {                                                     \
              ((void) 0);                                                      \
          } else {                                                             \
              PANIC("assertion `%s` failed: " fmt, #assertion, ##__VA_ARGS__); \
              abort();                                                         \
          }                                                                    \
      } while (0)

#endif /* NDEBUG */

