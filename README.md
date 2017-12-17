meta-jailhouse
==============

This README file contains information on the contents of the
jailhouse layer.


Dependencies
============

This layer depends on:

  URI: git://git.openembedded.org/bitbake
  branch: master

  URI: git://git.openembedded.org/openembedded-core
  layers: meta
  branch: master


Maintainers
===========

* Ola Redell <ola@retotech.se>
* Anders Törnqvist <anders@retotech.se>
* Jonas Weståker <jonas@retotech.se>

Please submit any patches against this jailhouse layer
via email or https://bitbucket.org/retotech/meta-jailhouse


Tested with
===========

* Yocto 2.2
* This layer has been developed for and tested with Bananapi M1 as target.
No other targets have been used thus far.


Adding the jailhouse layer to your build
========================================

In order to use this layer, you need to make the build system aware of
it.

Assuming the jailhouse layer exists at the top-level of your
yocto build tree, you can add it to the build system by adding the
location of the jailhouse layer to bblayers.conf, along with any
other layers needed. e.g.:

    BBLAYERS ?= " \
       /path/to/yocto/meta \
       /path/to/yocto/meta-poky \
       /path/to/yocto/meta-yocto-bsp \
       /path/to/yocto/meta-jailhouse \
       "


Build Jailhouse using this layer
================================

Include the following packages in your image: **jailhouse** and
**kernel-module-jailhouse**. For example, add the following
to your image recipe, or local.conf:

    IMAGE_INSTALL_append = " jailhouse kernel-module-jailhouse"

The jailhouse inmates and cells are by default
placed under `/usr/share/jailhouse/{inmates,cells}`. These locations
can be adjusted using the variables in **jailhouse-defs.inc**.

The jailhouse build system builds binary cell configuration (.cell) files 
from cell configuration sources (.c). To allow cell configurations to be
defined in cell recipes and imported into the jailhouse build, the jailhouse 
recipe defines a CELLS variable that lists all recipes that provide cells (and 
inmates) for the jailhouse build. Adapt the CELLS variable according to your 
needs, e.g.

    CELLS_pn-jailhouse = "freertos-cell"

in `local.conf`.
With this declaration, freertos-cell entries will be added both to the
DEPENDS and the RDEPENDS_jailhouse variables, and the jailhouse recipe will
pull cell descriptions from the staging directory before building.


Packages produced by a jailhouse.inc based recipe
-------------------------------------------------

The Jailhouse recipes based on the file jailhouse.inc produce
the following packages: 

* **jailhouse**, with the `jailhouse.bin` firmware, the `jailhouse` user 
space application, along with all inmate binaries that come with the jailhouse
repo, and all cells for which jailhouse is given configuration att build time.
* **jailhouse-bash-completion**, with file(s) needed for bash completion.
* **jailhouse-dbg**, jailhouse cli sources
* **kernel-module-jailhouse**, with the jailhouse kernel module, jailhouse.ko


Build cells and inmates
=======================

To build jailhouse cell definitions and inmates, inherit the class
`jailhouse-cell.bbclass` into your cell recipe and define your inmate binary,
and your cell configuration file using the variables `INMATE` and `CELLCONFIG`
as follows:

    inherit jailhouse-cell
    INMATE = "${S}/freertos-demo.bin"
    CELLCONFIG = "${S}/jailhouse-configs/bananapi-freertos-demo.c"

Using this class and variables ensures that the file designated by the
`CELLCONFIG` variable is pulled into the jailhouse build such that
a corresponding *.cell file is created.

Example cell
------------

An example cell recipe for the freertos-cell from Siemens is available
under `recipes-jailhouse/freertos-cell`. To use this, set the 
`CELLS` variable accordingly as described above.

Test the cell by executing the following sequence once booted.

      export JAILHOUSE_DIR=/usr/share/jailhouse
      jailhouse enable ${JAILHOUSE_DIR}/cells/bananapi.cell
      jailhouse cell create ${JAILHOUSE_DIR}/cells/freertos-cell.cell
      jailhouse cell load FreeRTOS ${JAILHOUSE_DIR}/inmates/freertos-demo.bin
      jailhouse cell start FreeRTOS

You should see output on the serial port used by the FreeRTOS inmate.

Important Variables
===================

The following variables should be set in jailhouse bbappends and cell recipes

`CELLCONFIG`  The name of the source cell configuration file (.c) that a cell
recipe installs into the sysroot, for the jailhouse recipe to use to create 
a binary configuration file. This variable should be set in a cell recipe
using a full path e.g. `CELLCONFIG = "${S}/my/path/cell-config.c"`.
Empty by default.

`CELLS`  A list of cells that should be built with jailhouse. The jailhouse
recipe will get dependencies to all cells listed in this variable and
pull in their cell configuration source files to the build. Empty by default.

`INMATE`  The name of the inmate binary file (.bin) that a cell recipe 
produces. This variable should be set in a cell recipe
using a full path e.g. `INMATE = "${B}/freertos-demo.bin"`.
Empty by default.

`JH_CONFIG` The hypervisor configuration file. This is per default taken to 
be one of the configuration files from the ci-directory, based on the
current architecture. Set this variable to your own configuration if needed.
 
The following variables can be left as is
 
`JH_DATADIR`  Base directory for installed jailhouse cells on target. This
defaults to ${datadir}/jailhouse. 

`CELL_DIR`  Target directory into which binary cell configuration files (.cell)
are installed. This defaults to ${JH_DATADIR}/cells. 

`CELLCONF_DIR`  Target directory into which the source cell configuration files
(.c) are installed. Defaults to ${JH_DATADIR}/configs.

`INMATES_DIR`  Target directory into which inmate binaries (.bin) are installed.
Defaults to ${JH_DATADIR}/inmates. 
