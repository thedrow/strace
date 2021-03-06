/*
 * Copyright (c) 2004 Ulrich Drepper <drepper@redhat.com>
 * Copyright (c) 2005-2015 Dmitry V. Levin <ldv@altlinux.org>
 * Copyright (c) 2015-2018 The strace developers.
 * All rights reserved.
 *
 * SPDX-License-Identifier: LGPL-2.1-or-later
 */

#include "defs.h"
#include <fcntl.h>

SYS_FUNC(mq_open)
{
	printpath(tcp, tcp->u_arg[0]);
	tprints(", ");
	/* flags */
	tprint_open_modes(tcp->u_arg[1]);
	if (tcp->u_arg[1] & O_CREAT) {
		/* mode */
		tprints(", ");
		print_numeric_umode_t(tcp->u_arg[2]);
		tprints(", ");
		printmqattr(tcp, tcp->u_arg[3], false);
	}
	return RVAL_DECODED | RVAL_FD;
}

SYS_FUNC(mq_timedsend)
{
	printfd(tcp, tcp->u_arg[0]);
	tprints(", ");
	printstrn(tcp, tcp->u_arg[1], tcp->u_arg[2]);
	tprintf(", %" PRI_klu ", %u, ", tcp->u_arg[2],
		(unsigned int) tcp->u_arg[3]);
	print_timespec(tcp, tcp->u_arg[4]);
	return RVAL_DECODED;
}

SYS_FUNC(mq_timedreceive)
{
	if (entering(tcp)) {
		printfd(tcp, tcp->u_arg[0]);
		tprints(", ");
	} else {
		if (syserror(tcp))
			printaddr(tcp->u_arg[1]);
		else
			printstrn(tcp, tcp->u_arg[1], tcp->u_rval);
		tprintf(", %" PRI_klu ", ", tcp->u_arg[2]);
		printnum_int(tcp, tcp->u_arg[3], "%u");
		tprints(", ");
		/*
		 * Since the timeout parameter is read by the kernel
		 * on entering syscall, it has to be decoded the same way
		 * whether the syscall has failed or not.
		 */
		temporarily_clear_syserror(tcp);
		print_timespec(tcp, tcp->u_arg[4]);
		restore_cleared_syserror(tcp);
	}
	return 0;
}

SYS_FUNC(mq_notify)
{
	printfd(tcp, tcp->u_arg[0]);
	tprints(", ");
	print_sigevent(tcp, tcp->u_arg[1]);
	return RVAL_DECODED;
}

SYS_FUNC(mq_getsetattr)
{
	if (entering(tcp)) {
		printfd(tcp, tcp->u_arg[0]);
		tprints(", ");
		printmqattr(tcp, tcp->u_arg[1], true);
		tprints(", ");
	} else {
		printmqattr(tcp, tcp->u_arg[2], true);
	}
	return 0;
}
