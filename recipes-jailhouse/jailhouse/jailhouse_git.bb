require jailhouse.inc

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-git:"

SRC_URI = "git://github.com/siemens/jailhouse.git;protocol=git \
	  file://no-kbuild-of-tools.patch \
	  file://tools-makefile.patch \
          file://tools-makefile-man-pages.patch"


SRCREV = "${AUTOREV}"
PV = "0.9-git${SRCPV}"

CELLS = ""

#DEFAULT_PREFERENCE = "-1"
