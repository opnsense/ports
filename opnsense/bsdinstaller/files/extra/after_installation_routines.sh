#!/bin/sh

# Set platform back to pfSense to prevent freesbie_1st from running
echo "pfSense" > /mnt/usr/local/etc/platform

# Let parent script know that a install really happened
touch /tmp/install_complete

mkdir -p /mnt/var/installer_logs
cp /tmp/install.disklabel /mnt/var/installer_logs
cp /tmp/install.disklabel* /mnt/var/installer_logs
cp /tmp/installer.log /mnt/var/installer_logs
cp /tmp/new.fdisk /mnt/var/installer_logs

# Fixup permissions on installed files
if [ -f /etc/installed_filesystem.mtree ]; then /usr/sbin/mtree -U -e -q -f /etc/installed_filesystem.mtree -p /mnt/ > /mnt/conf/mtree.log; fi;

#Sync disks
/bin/sync
