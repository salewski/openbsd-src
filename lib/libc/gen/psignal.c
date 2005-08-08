/*	$OpenBSD: psignal.c,v 1.8 2005/08/08 08:05:34 espie Exp $ */
/*
 * Copyright (c) 1983, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

/*
 * Print the name of the signal indicated
 * along with the supplied message.
 */
#include <sys/types.h>
#include <sys/uio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

extern char *__strsignal(int , char *);

void
psignal(unsigned int sig, const char *s)
{
	static char buf[NL_TEXTMAX];
	const char *c;
	int n;
	struct iovec iov[4];
	int niov = 0;

	c = __strsignal(sig, buf);
	if (s && *s) {

		n = strlen(s);
		iov[0].iov_base = (void *)s;
		iov[0].iov_len = n;
		iov[1].iov_base = ": ";
		iov[1].iov_len = 2;
		niov = 2;
	}
	iov[niov].iov_base = (void *)c;
	iov[niov].iov_len = strlen(c);
	iov[niov+1].iov_base = "\n";
	iov[niov+1].iov_len = 1;
	(void)writev(STDERR_FILENO, iov, niov+2);
}
