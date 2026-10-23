# shamrock ramdisk

postmarketOS initramfs for General Mobile GM 5 Plus (shamrock, MSM8952).

## Içerik

- `init`, `init_2nd.sh`, `init_functions.sh`, `init_functions_2nd.sh` – özel pMOS initramfs
- `my_wcn36xx.ko.zst`, `my_qcom_wcnss_pil.ko.zst`, `my_q6afe.ko.zst` – sysroot'a kopyalanan modüller
- `etc/deviceinfo` – cihaz bilgisi

## Kullanım

```bash
# Ramdisk img oluştur
cd shamrock-ramdisk
find . | cpio -H newc -o | gzip > ../rd-msm26.img

# Boot imajı oluştur (kernel derledikten sonra)
mkbootimg \
  --kernel arch/arm64/boot/Image.gz \
  --ramdisk rd-msm26.img \
  --base 0x80000000 --kernel_offset 0x8000 \
  --ramdisk_offset 0x01000000 \
  --tags_offset 0x100 --pagesize 2048 \
  -o boot-shamrock.img

# Cihaza gönder (boot bölümüne YAZMA, sadece boot et)
fastboot -s aa8fc832 boot boot-shamrock.img
```
