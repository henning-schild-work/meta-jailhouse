require jailhouse.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-0.7:"

SRC_URI = "git://github.com/siemens/jailhouse.git;protocol=git \
	  file://0004-no-kbuild-of-tools.patch \
	  file://0005-tools-makefile.patch \
	"

SRCREV = "${AUTOREV}"
PV = "0.7-git${SRCPV}"

CELLS = ""

