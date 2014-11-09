/*
 * Copyright (c) 2002 Andrew Stevenson. All Rights Reserved
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *     This product includes software developed by Andrew Stevenson.
 * 4. The name of Andrew Stevenson may not be used to endorse or promote
 *    products derived from this software without specific prior written
 *    permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ANDREW STEVENSON ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL ANDREW STEVENSON BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * That said I'd appreciate a message if you use this software in anyway.
 *                                               Andrew <andrew@ugh.net.au>
 */

#ifndef lint
static const char rcsid[] =
	"$Id: beep.c,v 1.1.1.1 2002/06/09 13:26:27 andrew Exp $";
#endif

#include <sys/ioctl.h>
#include <sys/types.h>

#include <dev/speaker/speaker.h>

#include <err.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <unistd.h>

#include "beep.h"

static void usage(void);
static void version(void);

u_int8_t Options;			/* global options */

int main(int argc, char *argv[]) {
	const char *speaker_device;	/* path to /dev/speaker */
	int c,
		spkr_fd;				/* fd to /dev/speaker */
	tone_t tone_description;	/* description of tone passed to /dev/speaker */

	/* make sure we remember our program name */
	setprogname(argv[0]);

	/* defaults */
	Options = 0;
	speaker_device = PATH_DEVSPEAKER;
	tone_description.frequency = DEFAULT_FREQUENCY;
	tone_description.duration = DEFAULT_DURATION;

	/* handle command line switches */
	while ((c = getopt(argc, argv, "Vd:hp:v")) != -1) {
		switch (c) {
			case 'V':
				/* version */
				version();
				break;
			case 'd':
				/* specify speaker device */
				speaker_device = optarg;
				break;
			case 'h':
				/* help */
				usage();
				break;
			case 'p':
				/* set pitch */
				tone_description.frequency = atoi(optarg);
				if (tone_description.frequency <= 0 || (tone_description.frequency == INT_MAX && errno == ERANGE)) {
					warnc(ERANGE, "invalid pitch");
					usage();
				}
				break;
			case 'v':
				/* verbose */
				Options |= OPT_VERBOSE;
				break;
			case '?':
			default:
				/* unknown option */
				usage();
				break;
		}
	}
	argc -= optind;
	argv += optind;

	/* see if a duration was specified */
	switch (argc) {
		case 0:
			/* default duration */
			break;
		case 1:
			/* duration specified */
			tone_description.duration = atoi(argv[0]);
			if (tone_description.duration < 0 || (tone_description.duration == INT_MAX && errno == ERANGE)) {
				warnc(ERANGE, "invalid duration");
				usage();
			}
			break;
		default:
			/* too many arguments */
			usage();
			break;
	}

	/* let the user know what we are up to */
	if (Options &= OPT_VERBOSE) {
		fprintf(stderr, "frequency: %dHz   duration: %dms   device: %s\n", tone_description.frequency, tone_description.duration, speaker_device);
	}

	/* open speaker device */
	if ((spkr_fd = open(speaker_device, O_WRONLY)) == -1) {
		err(EX_OSFILE, "open of %s for writing", speaker_device);
	}

	/* play tone */
	if (ioctl(spkr_fd, SPKRTONE, &tone_description) == -1) {
		err(EX_IOERR, "ioctl");
	}

	/* close speaker device */
	if (close(spkr_fd) == -1) {
		err(EX_IOERR, "close of %s", speaker_device);
	}

	return EX_OK;
}

static void usage(void) {

	fprintf(stderr, "usage: %s [-v] [-d device] [-p pitch] [duration]\n"
					"       %s -h\n"
					"       %s -V\n", getprogname(), getprogname(), getprogname());
	exit(EX_USAGE);
}

static void version(void) {

	printf("beep 1.0 Copyright 2002 Andrew Stevenson <andrew@ugh.net.au>\n");
	exit(EX_OK);
}
