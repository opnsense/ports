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
#include <security/pam_modules.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *auth_cmd = "/usr/local/sbin/opnsense-auth";

PAM_EXTERN int
pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN int
pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN int
pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN int
pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return PAM_SUCCESS;
}

PAM_EXTERN int
pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv)
{
	return PAM_SERVICE_ERR;
}

PAM_EXTERN int
pam_sm_authenticate(pam_handle_t *pamh, int flags,int argc, const char **argv)
{
	const char *user;
	char *password;
	char *service;
	int pam_err;
	FILE *fp;

	pam_err = pam_get_user(pamh, &user, NULL);
	if (pam_err != PAM_SUCCESS) {
		return pam_err;
	}

	pam_err = pam_get_item(pamh, PAM_SERVICE, (const void **)&service);
	if (pam_err != PAM_SUCCESS) {
		return pam_err;
	}

	pam_err = pam_get_authtok(pamh, PAM_AUTHTOK, (const char **)&password,
	    NULL);
	if (pam_err != PAM_SUCCESS) {
		return pam_err;
	}

	fp = popen(auth_cmd, "w");
	if (!fp) {
		return PAM_SYSTEM_ERR;
	}

	/* send authentication data to script */
	fprintf(fp, "service=%s%c", service, 0);
	fprintf(fp, "user=%s%c", user, 0);
	fprintf(fp, "password=%s%c", password, 0);
	/* extra NUL to mark end of data */
	fprintf(fp, "%c", 0);

	/* use exit status to authenticate */
	if (pclose(fp)) {
		pam_err = PAM_AUTH_ERR;
	}

	free(password);

	return (pam_err);
}
