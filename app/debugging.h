#define LOGGER_ACTIVE 1
#define LOGGER_INACTIVE 0

#ifndef LOGGER_STATUS
/**
 * Change the value before including the header file
 * to choose if logging is on or off.
 * Ac tive by default
 */
#define LOGGER_STATUS LOGGER_ACTIVE
#endif

// Remove previous defintion
#undef LOG
#if LOGGER_STATUS == LOGGER_ACTIVE
    /** Logger active - will print line into the console */
    #define LOG(...) puts(__VA_ARGS__)

    #define LOG_PATH()
#else
    /** Logger inactive - will be replaced by empty space */
    #define LOG(...);
#endif

// remove the define for the next include
#undef LOGGER_STATUS
