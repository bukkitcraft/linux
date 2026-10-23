#!/bin/busybox ash
# shellcheck disable=SC1091

# This is the "real" init.sh script, it's either jumped to immediately
# from init.sh, or loaded from initramfs-extra on the boot partition
# on space constrained devices with deviceinfo_create_initfs_extra="true".

# The set -a in init.sh only exports variables, not functions
. /init_functions.sh
. /init_functions_2nd.sh

# Handle halt/poweroff/reboot
# Signals from busybox/halt.c
trap 'halt -f' USR1
trap 'poweroff -f' USR2
trap 'reboot -f' TERM

# Run udev early, before splash, to make sure any relevant display drivers are
# loaded in time
setup_udev

setup_usb_network
start_unudhcpd

# Start splash
if [ "$nosplash" != "y" ] && [ "$IN_CI" = "false" ]; then
	setup_framebuffer
	splash_start
	splash_set_message "Loading"
fi

setup_dynamic_partitions "${deviceinfo_super_partitions:=}"

run_hooks /hooks

if [ "$debug_shell" = "y" ]; then
	debug_shell
fi

check_keys

# If running from initramfs-extra this will be a no-op since it was
# called before to mount the boot partition
mount_subpartitions

run_hooks /hooks-extra

wait_root_partition
delete_old_install_partition
resize_root_partition
unlock_root_partition
resize_root_filesystem
mount_root_partition
resize_filesystem_after_mount /sysroot

# Mount boot partition into sysroot if needed since some
# old installations don't have a proper /etc/fstab file. See #2800
if [ -z "$(cat /sysroot/etc/fstab | grep -v "#" | tr -d '[:space:]')" ]; then
	wait_boot_partition
	mount_boot_partition /sysroot/boot "rw"
fi

init="/sbin/init"
setup_bootchart2

# Switch root
run_hooks /hooks-cleanup

echo "Switching root"

# Restore stdout and stderr to their original values if they
# were stashed
if [ -e "/proc/1/fd/3" ]; then
	exec 1>&3 2>&4
elif [ "$debug_shell" != "y" ]; then
	echo "$LOG_PREFIX Disabling console output again (use 'pmos.debug-shell' to keep it enabled)"
	exec >/dev/null 2>&1
fi

# Make it clear that we're at the end of the initramfs
splash_set_message "Starting"

# Re-enable kmsg ratelimiting (might have been disabled for logging)
echo ratelimit > /proc/sys/kernel/printk_devkmsg

# Vibrate to indicate that we are booting
if [ "$IN_CI" != "true" ]; then
	beebzzr &
fi

killall udevd syslogd unudhcpd 2>/dev/null

# Kill any getty shells that might be running
for pid in $(pidof sh); do
	if ! [ "$pid" = "1" ]; then
		kill -9 "$pid"
	fi
done

# cleanup after ourselves
# switch_root does a mount --move , keeping stale filesystems like devtmpfs
# with /dev/log in there.
rm /dev/log 2>/dev/null || true

# Update Wi-Fi and WCNSS modules before switch_root
if [ -f /my_wcn36xx.ko.zst ]; then
	mount -o remount,rw /sysroot 2>/dev/null
	cp -f /my_wcn36xx.ko.zst /sysroot/lib/modules/7.1.3/kernel/drivers/net/wireless/ath/wcn36xx/wcn36xx.ko.zst
	cp -f /my_wcn36xx.ko.zst /sysroot/usr/lib/modules/7.1.3/kernel/drivers/net/wireless/ath/wcn36xx/wcn36xx.ko.zst 2>/dev/null
	echo "[pmOS-rd] SUCCESS: Updated wcn36xx.ko.zst in sysroot" > /dev/kmsg
fi
if [ -f /my_qcom_wcnss_pil.ko.zst ]; then
	mount -o remount,rw /sysroot 2>/dev/null
	cp -f /my_qcom_wcnss_pil.ko.zst /sysroot/lib/modules/7.1.3/kernel/drivers/remoteproc/qcom_wcnss_pil.ko.zst
	cp -f /my_qcom_wcnss_pil.ko.zst /sysroot/usr/lib/modules/7.1.3/kernel/drivers/remoteproc/qcom_wcnss_pil.ko.zst 2>/dev/null
	echo "[pmOS-rd] SUCCESS: Updated qcom_wcnss_pil.ko.zst in sysroot" > /dev/kmsg
fi
if [ -f /my_q6afe.ko.zst ]; then
	mount -o remount,rw /sysroot 2>/dev/null
	cp -f /my_q6afe.ko.zst /sysroot/lib/modules/7.1.3/kernel/sound/soc/qcom/qdsp6/q6afe.ko.zst
	cp -f /my_q6afe.ko.zst /sysroot/usr/lib/modules/7.1.3/kernel/sound/soc/qcom/qdsp6/q6afe.ko.zst 2>/dev/null
	echo "[pmOS-rd] SUCCESS: Updated q6afe.ko.zst in sysroot" > /dev/kmsg
fi
mount -o remount,rw /sysroot 2>/dev/null
if [ -f /sysroot/usr/share/applications/org.gnome.Settings.desktop ]; then
	sed -i 's/OnlyShowIn=GNOME;/OnlyShowIn=GNOME;Phosh;/' /sysroot/usr/share/applications/org.gnome.Settings.desktop
	echo "[pmOS-rd] SUCCESS: Enabled GNOME Settings in Phosh" > /dev/kmsg
fi

cat << 'EOF' > /sysroot/usr/share/applications/reboot-fastboot.desktop
[Desktop Entry]
Name=Fastboot ile Başlat
Name[tr]=Fastboot ile Başlat
Comment=Cihazı Fastboot / Bootloader moduna yeniden başlatır
Exec=systemctl reboot --bootloader
Icon=system-reboot
Terminal=false
Type=Application
Categories=System;Utility;
EOF

cat << 'EOF' > /sysroot/usr/share/applications/reboot-recovery.desktop
[Desktop Entry]
Name=Recovery ile Başlat
Name[tr]=Recovery ile Başlat
Comment=Cihazı Recovery moduna yeniden başlatır
Exec=systemctl reboot --recovery
Icon=system-reboot
Terminal=false
Type=Application
Categories=System;Utility;
EOF

chmod +x /sysroot/usr/share/applications/reboot-fastboot.desktop /sysroot/usr/share/applications/reboot-recovery.desktop 2>/dev/null

mkdir -p /sysroot/etc/systemd/resolved.conf.d 2>/dev/null
cat << 'EOF' > /sysroot/etc/systemd/resolved.conf.d/dns.conf
[Resolve]
DNS=1.1.1.1 8.8.8.8
FallbackDNS=1.0.0.1 8.8.4.4
Domains=~.
EOF
echo "nameserver 1.1.1.1" > /sysroot/etc/resolv.conf 2>/dev/null
echo "nameserver 8.8.8.8" >> /sysroot/etc/resolv.conf 2>/dev/null

# shellcheck disable=SC2093
exec switch_root /sysroot "$init"

echo "$LOG_PREFIX ERROR: switch_root failed!" > /dev/kmsg
echo "$LOG_PREFIX Looping forever. Install and use the debug-shell hook to debug this." > /dev/kmsg
echo "$LOG_PREFIX For more information, see <https://postmarketos.org/debug-shell>" > /dev/kmsg
fail_halt_boot
