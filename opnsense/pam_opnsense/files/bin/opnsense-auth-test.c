/*
 * Copyright (C) 2016 Deciso B.V.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <security/pam_appl.h>
#include <security/openpam.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static const char *service = "opnsense-auth-test";
static const char *user = "root";

static void
usage(void)
{
	fprintf(stderr, "usage: opnsense-auth-test [-s service] [-u user]\n");
	exit(EXIT_FAILURE);
}

int
main(int argc, char **argv)
{
	pam_handle_t *pamh = NULL;
	struct pam_conv pamc;
	int pam_err, c;

	while ((c = getopt(argc, argv, "s:u:")) != -1) {
		switch (c) {
		case 's':
			service = optarg;
			break;
		case 'u':
			user = optarg;
			break;
		default:
			usage();
			/* NOTREACHED */
		}
	}

	argc -= optind;
	argv += optind;

	if (argc) {
		usage();
		/* NOTREACHED */
	}

	memset(&pamc, 0, sizeof(pamc));
	pamc.conv = &openpam_ttyconv;

	pam_err = pam_start(service, user, &pamc, &pamh);
	if (pam_err == PAM_SUCCESS) {
		pam_err = pam_authenticate(pamh, 0);
		if (pam_err == PAM_SUCCESS) {
			pam_err = pam_acct_mgmt(pamh, 0);
			if (pam_err == PAM_SUCCESS) {
				printf("User %s successfully authenticated "
				    "for service %s\n", user, service);
			}
		}
	}

	if (pam_err != PAM_SUCCESS) {
		printf("User %s NOT authenticated for service %s\n",
		    user, service);
	}

	if (pam_end(pamh, pam_err) != PAM_SUCCESS) {
		exit(1);
	}

	return (pam_err != PAM_SUCCESS);
}
