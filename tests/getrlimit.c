/*
 * Copyright (c) 2016-2018 The strace developers.
 * All rights reserved.
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#include "tests.h"
#include <asm/unistd.h>

#ifdef __NR_getrlimit

# define NR_GETRLIMIT	__NR_getrlimit
# define STR_GETRLIMIT	"getrlimit"
# include "xgetrlimit.c"

#else

SKIP_MAIN_UNDEFINED("__NR_getrlimit")

#endif
