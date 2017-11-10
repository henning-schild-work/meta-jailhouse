require recipes-jailhouse/jailhouse/jailhouse-dirs.inc

INMATE ?= ""
CELLCONFIG ?= ""

INMATE_TARGET ?= "${INMATE}"
CELLCONFIG_TARGET ?= "${CELLCONFIG}"

do_install() {
    if [ -n "${CELLCONFIG}" ]
    then
	install -d ${D}${CELLCONF_DIR}
    	install ${CELLCONFIG} ${D}${CELLCONF_DIR}/$(basename ${CELLCONFIG_TARGET})
    fi

    if [ -n "${INMATE}" ]
    then
	install -d ${D}${INMATES_DIR}
    	install ${INMATE} ${D}${INMATES_DIR}/$(basename ${INMATE_TARGET})
    fi
}

FILES_${PN}-dev += "${CELLCONF_DIR}"
FILES_${PN} += "${INMATES_DIR}"
