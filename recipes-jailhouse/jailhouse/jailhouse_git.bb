require jailhouse.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-git:"

SRC_URI = "git://github.com/siemens/jailhouse.git;protocol=git \
	  file://0004-no-kbuild-of-tools.patch \
	  file://0005-tools-makefile.patch \
	"

SRCREV = "${AUTOREV}"
PV = "0.8-git${SRCPV}"

CELLS = ""

DEFAULT_PREFERENCE = "-1"
