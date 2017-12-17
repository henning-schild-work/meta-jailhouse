SECTION = "kernel"
DESCRIPTION = "Mainline Linux kernel"
LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=d7810fab7487fb0aad327b76f1be7cd7"
COMPATIBLE_MACHINE = "(sun4i|sun5i|sun7i)"

inherit kernel

require recipes-kernel/linux/linux-dtb.inc
require recipes-kernel/linux/linux.inc

# Pull in the devicetree files into the rootfs
RDEPENDS_kernel-base += "kernel-devicetree"

KERNEL_EXTRA_ARGS += "LOADADDR=${UBOOT_ENTRYPOINT}"

S = "${WORKDIR}/linux-${PV}"

SRC_URI[md5sum] = "938baaf8fd3d232e9fbc2f402adf0d3f"
SRC_URI[sha256sum] = "0907678ba9ea146ddbdecd0a0b6363f56b896b5c61c9a15e809effb3ea346ccc"

	
SRC_URI = "https://www.kernel.org/pub/linux/kernel/v4.x/linux-${PV}.tar.xz \
        file://defconfig \
        "

SRC_URI_append_jailhouse-bpi = " \
        file://jailhouse-required-symbol-export.patch \
	file://jailhouse-required-symbol-export_2.patch \
	file://jailhouse-required-symbol-export_3.patch \
	"

