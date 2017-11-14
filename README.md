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

Please submit any patches against this jailhouse layer to
meta-jailhouse@retotech.se


Tested with
===========

This layer has been developed for and tested with Bananapi M1 as target.
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
can be adjusted using the variables in jailhouse-dirs.inc.

The jailhouse build system builds cell configuration (*.cell) files from the
cell descriptions (*.c). To enable cell descriptions being defined in 
cell recipes and imported into the jailhouse build, the jailhouse recipe
defines a CELLS variable that lists all recipes that provide cells (and inmates)
for the jailhouse build. Adapt the CELLS variable according to your needs, e.g.

    CELLS_append = " freertos-cell"

With this declaration, freertos-cell entries will be added both to the
DEPENDS and the RDEPENDS_jailhouse variables, and the jailhouse recipe will
pull cell descriptions from the staging directory before building.


Packages produced by a jailhouse.inc based recipe
-------------------------------------------------

The Jailhouse recipes based on the file jailhouse.inc produce
the follwing packages: 

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