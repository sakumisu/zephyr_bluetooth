/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_LOGGING_LOG_H_
#define ZEPHYR_INCLUDE_LOGGING_LOG_H_

#include <zephyr.h>

#define LOG_LEVEL_NONE 0U
#define LOG_LEVEL_ERR  1U
#define LOG_LEVEL_WRN  2U
#define LOG_LEVEL_INF  3U
#define LOG_LEVEL_DBG  4U

#define LOG_MODULE_REGISTER(...) 

#ifndef CONFIG_BT_LOG_LEVEL
#define CONFIG_BT_LOG_LEVEL LOG_LEVEL_WRN
#endif
/*
 * The color for terminal (foreground)
 * BLACK    30
 * RED      31
 * GREEN    32
 * YELLOW   33
 * BLUE     34
 * PURPLE   35
 * CYAN     36
 * WHITE    37
 */

/*
 * The color for terminal (foreground)
 * BLACK    30
 * RED      31
 * GREEN    32
 * YELLOW   33
 * BLUE     34
 * PURPLE   35
 * CYAN     36
 * WHITE    37
 */
#define _BT_COLOR_HDR(n) printf("\033[" #n "m")
#define _BT_COLOR_END    printf("\033[0m")

#define bt_print(color_n, fmt, ...)           \
    do {                                         \
        _BT_COLOR_HDR(color_n);               \
        printf(fmt"\r\n", ##__VA_ARGS__); \
        _BT_COLOR_END;                        \
    } while (0)

#if (CONFIG_BT_LOG_LEVEL >= LOG_LEVEL_DBG)
#define LOG_DBG(fmt, ...) bt_print(0, fmt, ##__VA_ARGS__)
#else
#define LOG_DBG(...)  {}
#endif

#if (CONFIG_BT_LOG_LEVEL >= LOG_LEVEL_INF)
#define LOG_INF(fmt, ...) bt_print(32, fmt, ##__VA_ARGS__)
#else
#define LOG_INF(...) {}
#endif

#if (CONFIG_BT_LOG_LEVEL >= LOG_LEVEL_WRN)
#define LOG_WRN(fmt, ...) bt_print(33, fmt, ##__VA_ARGS__)
#else
#define LOG_WRN(...) {}
#endif

#if (CONFIG_BT_LOG_LEVEL >= LOG_LEVEL_ERR)
#define LOG_ERR(fmt, ...) bt_print(31, fmt, ##__VA_ARGS__)
#else
#define LOG_ERR(...) {}
#endif

#define LOG_HEXDUMP_ERR(...) (void) 0
#define LOG_HEXDUMP_WRN(...) (void) 0
#define LOG_HEXDUMP_DBG(...) (void) 0
#define LOG_HEXDUMP_INF(...) (void) 0

static inline char *log_strdup(const char *str)
{
	return (char *)str;
}

static inline void k_oops(void)
{
}

#endif /* ZEPHYR_INCLUDE_LOGGING_LOG_H_ */
