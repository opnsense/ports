#!/bin/sh

# Let parent script know that a install really happened
touch /tmp/install_complete

mkdir -p /mnt/var/logs/installer
cp /tmp/install.disklabel* /mnt/var/logs/installer
cp /tmp/installer.log /mnt/var/logs/installer
cp /tmp/new.fdisk /mnt/var/logs/installer

# Fixup permissions on installed files
if [ -f /etc/installed_filesystem.mtree ]; then
	mtree -U -e -q -f /etc/installed_filesystem.mtree -p /mnt/ \
	    > /mnt/var/logs/installer/mtree.log
fi

sync
