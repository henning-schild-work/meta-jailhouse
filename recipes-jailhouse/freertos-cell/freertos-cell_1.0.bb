SUMMARY = "FreeRTOS for Jailhouse"
HOMEPAGE = "https://github.com/siemens/freertos-cell"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://freertos/License/license.txt;md5=ff3ee34806c13760712131849e183a35\
		 file://LICENSE;md5=494a529748a63071fbdf44f61db2391c"

DEPENDS = "virtual/kernel make-native"

SRC_URI = "git://github.com/siemens/freertos-cell.git;protocol=https;branch=master; \
        file://Fix-Makefile.patch \
        file://Remove-check-of-interrupt-mask.patch \
        file://Bananapi-config-fix-for-Jailhouse-0.6.patch"

SRCREV = "6ad80637be066d196d81c1640bc1bd5b66e0ec45"

S ="${WORKDIR}/git"

inherit jailhouse-cell

INMATE = "${S}/freertos-demo.bin"
CELLCONFIG = "${S}/jailhouse-configs/bananapi-freertos-demo.c"
CELLCONFIG_TARGET = "freertos-cell.c"


do_compile() {
    LDFLAGS="" oe_runmake
}
