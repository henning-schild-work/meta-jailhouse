SUMMARY = "A small image just capable of starting Jailhouse with cells"

include recipes-core/images/core-image-minimal.bb

IMAGE_INSTALL_append= " \
                      jailhouse \
                      jailhouse-bash-completion \
                      kernel-module-jailhouse \
                      "

IMAGE_FEATURES += "ssh-server-openssh"
