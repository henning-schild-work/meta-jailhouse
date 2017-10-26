require jailhouse.inc

SRC_URI = "git://github.com/siemens/jailhouse.git;protocol=git \
        file://0002-no-ldflags-in-tools.patch \
	file://0003-workaround-if-changed-problem-in-tools-makefile.patch \
	file://0004-no-kbuild-of-tools.patch \
	"

SRCREV = "81528e48763c8dfc10851c49968eb3d053d4b85c"

#do_configure_append() {
#    cp -av ${S}/ci/jailhouse-config-banana-pi.h ${S}/hypervisor/include/jailhouse/config.h
#}
