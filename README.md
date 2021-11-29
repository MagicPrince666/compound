# 固件合成分离器

# 合成mt7628固件
```
./mt7628 image.bin ../../u-boot-mt7688/uboot.bin ../../openwrt/bin/targets/ramips/mt76x8/openwrt-ramips-mt76x8-widora_bit5-32m-squashfs-sysupgrade.bin
cp image.bin /mnt/d/
```

# 合成mt7628带kernel固件
```
./mt7628 image.bin ../../u-boot-mt7688/uboot.bin ../../openwrt/bin/targets/ramips/mt76x8/openwrt-ramips-mt76x8-widora_bit5-32m-squashfs-sysupgrade.bin
cp image.bin /mnt/d/
```

# 分离固件
```
./mt7628 image.bin
```

# 挂载
```
sudo mount -t squashfs -o loop rootfs.bin /mnt
mount -t squashfs /dev/mtdblock0  /media
```