/*-
 * Copyright (c) 2009 Andrew Thompson, Clone Consulting Limited
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer,
 *    without modification.
 * 2. Redistributions in binary form must reproduce at minimum a disclaimer
 *    similar to the "NO WARRANTY" disclaimer below ("Disclaimer") and any
 *    redistribution must be conditioned upon including a substantially
 *    similar Disclaimer requirement for further binary redistribution.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF NONINFRINGEMENT, MERCHANTIBILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGES.
 *
 *
 * Based on uathload.c by Sam Leffler
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/endian.h>
#include <sys/mman.h>

#include <sys/ioctl.h>
#include <dev/usb/usb.h>
#include <dev/usb/usb_ioctl.h>

#include <err.h>
#include <fcntl.h>
#include <libgen.h>
#include <paths.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <sys/endian.h>

struct um175_stat {
	uint16_t	cmd;
	uint8_t		data1[6];
	uint16_t	d_year;
	uint16_t	d_month;
	uint16_t	d_day;
	uint16_t	d_hour;
	uint16_t	d_minute;
	uint16_t	d_sec;
	uint16_t	d_msec;
	uint8_t		data2[4];
	uint16_t	rssi1;
	uint8_t		data3[36];
	uint16_t	rssi2;
	uint8_t		data4[6];
	uint16_t	fcs;
	uint8_t		end;
} __packed;

#define DATA_TIMEOUT	10000

#define	VERBOSE(_fmt, ...) do {			\
	if (v_flag) {				\
		printf(_fmt, __VA_ARGS__);	\
		fflush(stdout);			\
	}					\
} while (0)

static int v_flag;
static int s_flag;

static void	dbgprint_safe(const char *, const char *, int);
static int	getdevname(const char *, char *);
static void	usage(void);
static int	devopen(char *);
static void	um175_status(int);

static void
dbgprint_safe(const char *prefix, const char *buf, int len)
{
	int i;
	printf("%s %d bytes: \n", prefix, len);
	for (i = 0; i < len;) {
		int j;

		for (j = 0; i + j < len && j < 16; j++) {
			printf("%02x ", (uint8_t)buf[i + j]);
		}
		// pad
		for (; j < 16; j++)
			printf("   ");
		printf("  ");
		for (j = 0; i + j < len && j < 16; j++) {
			if (isprint(buf[i + j]))
				printf("%c", buf[i + j]);
			else
				printf(".");
		}
		printf("\n");
		i += j;
	}
	printf("\n");
}

static int
getdevname(const char *devname, char *datadev)
{
	char *bn, *dn;

	dn = dirname(devname);
	if (dn == NULL)
		return (-1);
	bn = basename(devname);
	if (bn == NULL || strncmp(bn, "ugen", 4))
		return (-1);
	bn += 4;

	/* NB: pipes are hardcoded */
	snprintf(datadev, 256, "/dev/usb/%s.4", bn);
	return (0);
}

static void
usage(void)
{
	errx(-1, "usage: 3gstat [-sv] -d devname");
}

static int
devopen(char *dev)
{
	int bufsize, shortrx, timeout;
	int fd;

	VERBOSE("open %s\n", dev);
	fd = open(dev, O_RDWR, 0);
	if (fd < 0)
		err(-1, "open(%s)", dev);

	bufsize = 512;
	shortrx = 1;
	timeout = DATA_TIMEOUT;
	if (ioctl(fd, USB_SET_RX_TIMEOUT, &timeout) < 0)
		err(-1, "%s: USB_SET_RX_TIMEOUT(%u)", dev, DATA_TIMEOUT);
	if (ioctl(fd, USB_SET_RX_BUFFER_SIZE, &bufsize) < 0)
		err(-1, "%s: USB_SET_RX_BUFFER_SIZE(%u)", dev, bufsize);
	if (ioctl(fd, USB_SET_RX_SHORT_XFER, &shortrx) < 0)
		err(-1, "%s: USB_SET_RX_BUFFER_SIZE(%u)", dev, shortrx);
	if (ioctl(fd, USB_SET_TX_TIMEOUT, &timeout) < 0)
		err(-1, "%s: USB_SET_TX_TIMEOUT(%u)", dev, DATA_TIMEOUT);

	return (fd);
}

static void
um175_status(int fd)
{
	struct um175_stat rxmsg;
	char txdata[] = { 0xc8, 0x0b, 0xfe, 0xb5, 0x7e };

	VERBOSE("writing %zd bytes\n", sizeof(txdata));
	if (write(fd, txdata, sizeof(txdata)) != sizeof(txdata)) {
		VERBOSE("%s", "\n");
		err(-1, "error sending msg (%zd bytes)", sizeof(txdata));
	}

	bzero(&rxmsg, sizeof(rxmsg));
	VERBOSE("reading %zd bytes\n", sizeof(rxmsg));
	if (read(fd, &rxmsg, sizeof(rxmsg)) != sizeof(rxmsg)) {
		VERBOSE("%s", "\n");
		err(-1, "error reading from device");
	}

	VERBOSE("time: %02d/%02d/%04d %02d:%02d:%02d\n",
	    rxmsg.d_month, rxmsg.d_day, rxmsg.d_year,
	    rxmsg.d_hour, rxmsg.d_minute, rxmsg.d_sec);

	if (rxmsg.rssi1 > 255)
		rxmsg.rssi1 = bswap16(rxmsg.rssi1);
	if (rxmsg.rssi2 > 255)
		rxmsg.rssi2 = bswap16(rxmsg.rssi2);

	if (s_flag)
		printf("-%d:-%d\n", rxmsg.rssi1, rxmsg.rssi2);
	else
		printf("3G Signal: -%ddBm, -%ddBm\n", rxmsg.rssi1, rxmsg.rssi2);

	if (v_flag) {
		/* Clear to help debug */
		rxmsg.d_day = rxmsg.d_month = rxmsg.d_year = 0;
		rxmsg.d_hour = rxmsg.d_minute = rxmsg.d_sec = rxmsg.d_msec = 0;
		rxmsg.fcs = rxmsg.end = 0;
		dbgprint_safe("struct um175_stat", (char *)&rxmsg, sizeof(rxmsg));
		fflush(stdout);
	}
}

int
main(int argc, char *argv[])
{
	char dev[256];
	char *devname;
	int fd, c;

	devname = NULL;
	while ((c = getopt(argc, argv, "d:sv")) != -1) {
		switch (c) {
		case 'd':
			devname = optarg;
			break;
		case 's':
			s_flag = 1;
			break;
		case 'v':
			v_flag = 1;
			break;
		default:
			usage();
			/*NOTREACHED*/
		}
	}
	argc -= optind;
	argv += optind;

	if (devname == NULL)
		errx(-1, "No device name; use -d to specify the ugen device");
	if (argc > 0)
		usage();

	if (getdevname(devname, dev))
		err(-1, "getdevname error");

	fd = devopen(dev);
	um175_status(fd);
	close(fd);
	return 0;
}
