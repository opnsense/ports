#!/bin/sh

# Let parent script know that a install really happened
touch /tmp/install_complete

# Copy all the installer logs to the new installation
mkdir -p /mnt/var/log/installer
rm /mnt/var/log/installer.log
cp /tmp/install.disklabel* /mnt/var/log/installer
cp /tmp/installer.log /mnt/var/log/installer
cp /tmp/new.fdisk /mnt/var/log/installer

# Fixup permissions on installed files
if [ -f /etc/installed_filesystem.mtree ]; then
	mtree -U -e -q -f /etc/installed_filesystem.mtree -p /mnt/ \
	    > /mnt/var/log/installer/mtree.log
	rm /mnt/etc/installed_filesystem.mtree
fi

sync
