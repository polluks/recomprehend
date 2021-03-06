/*
 * This file is part of Re-Comprehend
 *
 * Ryan Mallon, 2015, <rmallon@gmail.com>
 *
 * To the extent possible under law, the author(s) have dedicated all
 * copyright and related and neighboring rights to this software to
 * the public domain worldwide. This software is distributed without
 * any warranty.  You should have received a copy of the CC0 Public
 * Domain Dedication along with this software. If not, see
 *
 * <http://creativecommons.org/publicdomain/zero/1.0/>.
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stdio.h>

#include "util.h"

static unsigned debug_flags;

void __fatal_error(const char *func, unsigned line, const char *fmt, ...)
{
	va_list args;

	printf("[%s:%d] Fatal error: ", func, line);
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf("\n");

	exit(EXIT_FAILURE);
}

void fatal_strerror(int err, const char *fmt, ...)
{
	va_list args;

	printf("Fatal error: ");
	va_start(args, fmt);
	vprintf(fmt, args);
	va_end(args);
	printf(": %s\n", strerror(err));

	exit(EXIT_FAILURE);
	
}

void *xmalloc(size_t size)
{
	void *p;

	p = malloc(size);
	if (!p)
		fatal_error("Out of memory");

	memset(p, 0, size);
	return p;
}

char *xstrndup(const char *str, size_t len)
{
	char *p;

	p = strndup(str, len);
	if (!p)
		fatal_error("Out of memory");
	return p;
}

void debug_printf(unsigned flags, const char *fmt, ...)
{
	va_list args;

	if (debug_flags & flags) {
		va_start(args, fmt);
		vprintf(fmt, args);
	}
}

void debug_enable(unsigned flags)
{
	debug_flags |= flags;
}

void debug_disable(unsigned flags)
{
	debug_flags &= ~flags;
}

bool debugging_enabled(void)
{
	// FIXME
	return debug_flags;
}
