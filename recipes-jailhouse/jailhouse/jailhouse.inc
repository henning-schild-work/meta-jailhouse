SUMMARY = "Jailhouse"
HOMEPAGE = "https://github.com/siemens/jailhouse"
SECTION = "jailhouse"
LICENSE = "GPL-2.0 & BSD-2-Clause"
LIC_FILES_CHKSUM = "file://COPYING;md5=9fa7f895f96bde2d47fd5b7d95b6ba4d \
                 file://tools/root-cell-config.c.tmpl;beginline=6;endline=33;md5=2825581c1666c44a17955dc574cfbfb3 \
                 file://hypervisor/include/jailhouse/hypercall.h;beginline=9;endline=36;md5=2825581c1666c44a17955dc574cfbfb3 \
                 file://hypervisor/include/jailhouse/cell-config.h;beginline=9;endline=36;md5=2825581c1666c44a17955dc574cfbfb3 \
                 file://hypervisor/arch/arm/include/asm/jailhouse_hypercall.h;beginline=9;endline=36;md5=2825581c1666c44a17955dc574cfbfb3 \
                 file://hypervisor/arch/x86/include/asm/jailhouse_hypercall.h;beginline=9;endline=36;md5=2825581c1666c44a17955dc574cfbfb3 \
                 file://driver/jailhouse.h;beginline=9;endline=36;md5=2825581c1666c44a17955dc574cfbfb3"

DEPENDS = "virtual/kernel make-native python-mako-native dtc-native python-mako"

S ="${WORKDIR}/git"

JH_DATADIR="${datadir}/jailhouse"
CELL_DIR ?= "${JH_DATADIR}/cells"
CELLCONF_DIR ?= "${JH_DATADIR}/configs"
INMATES_DIR ?= "${JH_DATADIR}/inmates"

export PACKAGECONFIG_CONFARGS

inherit module pythonnative bash-completion

do_configure() {
    # Copy all cell configs included through PACKAGECONFIG 
    for arg in $(echo $PACKAGECONFIG_CONFARGS); do
        if conf=$(echo $arg | grep -o "with-.*$");
        then
           cp "${STAGING_DIR_HOST}/${CELLCONF_DIR}/${conf#with-}.c" ${S}/configs/
        fi
    done
}

USER_SPACE_CFLAGS = '${CFLAGS} -DLIBEXECDIR=\\\"${libexecdir}\\\" \
		  -DJAILHOUSE_VERSION=\\\"$JAILHOUSE_VERSION\\\" \
		  -Wall -Wextra -Wmissing-declarations -Wmissing-prototypes -Werror \
		  -I../driver'

TOOLS_SRC_DIR = "${S}/tools"
TOOLS_OBJ_DIR = "${S}/tools"

do_compile() {
   oe_runmake V=1 \
        ARCH=${TARGET_ARCH} CROSS_COMPILE=${TARGET_PREFIX} \
        KDIR=${STAGING_KERNEL_BUILDDIR}

   cd ${TOOLS_SRC_DIR}
   export JAILHOUSE_VERSION=$(cat ../VERSION)
   oe_runmake V=1 \
   	       CFLAGS="${USER_SPACE_CFLAGS}" \
               src=${TOOLS_SRC_DIR} obj=${TOOLS_OBJ_DIR} \
	       ${TOOLS_OBJ_DIR}/jailhouse-config-collect ${TOOLS_OBJ_DIR}/jailhouse
}

do_install() {
    oe_runmake \
	       ARCH=${TARGET_ARCH} \
	       CROSS_COMPILE=${TARGET_PREFIX} \
	       KDIR=${STAGING_KERNEL_BUILDDIR} \
	       DESTDIR=${D} install

    install -d ${D}${CELL_DIR}
    install ${B}/configs/*.cell ${D}${CELL_DIR}/

    install -d ${D}${INMATES_DIR}
    install ${B}/inmates/demos/${TARGET_ARCH}/*.bin ${D}${INMATES_DIR}
}

PACKAGE_BEFORE_PN = "kernel-module-jailhouse"
FILES_${PN} = "${base_libdir}/firmware ${libexecdir} ${sbindir} ${JH_DATADIR}"

PACKAGECONFIG ??= "freertos-cell freertos-demo1-cell freertos-demo3-cell freertos-ivshmem-demo"
PACKAGECONFIG[freertos-cell] = \
       "--with-freertos-cell,,freertos-cell,freertos-cell"
PACKAGECONFIG[freertos-demo1-cell] = \
       "--with-freertos-demo1-cell,,freertos-demo1-cell,freertos-demo1-cell"
PACKAGECONFIG[freertos-demo3-cell] = \
       "--with-freertos-demo3-cell,,freertos-demo3-cell,freertos-demo3-cell"
PACKAGECONFIG[freertos-ivshmem-demo] = \
       "--with-freertos-ivshmem-demo,,freertos-ivshmem-demo,freertos-ivshmem-demo"
