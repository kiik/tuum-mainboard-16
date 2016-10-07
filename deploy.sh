umount /mnt 
mount /dev/$1 /mnt

cp BUILD/LPC1768/GCC_ARM/UT-Mainboard-16_mbed.bin /mnt
sync
