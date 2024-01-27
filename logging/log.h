/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_INCLUDE_LOGGING_LOG_H_
#define ZEPHYR_INCLUDE_LOGGING_LOG_H_

#include <zephyr.h>

#define LOG_ERR(fmt, ...) printf(fmt"\r\n", ##__VA_ARGS__)
#define LOG_WRN(fmt, ...) printf(fmt"\r\n", ##__VA_ARGS__)
#define LOG_DBG(fmt, ...) 
#define LOG_INF(fmt, ...) printf(fmt"\r\n", ##__VA_ARGS__)

#define LOG_HEXDUMP_ERR(...) (void) 0
#define LOG_HEXDUMP_WRN(...) (void) 0
#define LOG_HEXDUMP_DBG(...) (void) 0
#define LOG_HEXDUMP_INF(...) (void) 0

#define LOG_MODULE_REGISTER(...)

static inline char *log_strdup(const char *str)
{
	return (char *)str;
}

static inline void k_oops(void)
{
}

#endif /* ZEPHYR_INCLUDE_LOGGING_LOG_H_ */
