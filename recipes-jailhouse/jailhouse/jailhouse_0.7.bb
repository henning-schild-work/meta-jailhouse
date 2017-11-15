require jailhouse.inc

SRC_URI = "git://github.com/siemens/jailhouse.git;protocol=git \
	  file://0004-no-kbuild-of-tools.patch \
	  file://0005-tools-makefile.patch \
	"

SRCREV = "5c13b6409b6088ab717e8af444e11839868302eb"

CELLS = ""

