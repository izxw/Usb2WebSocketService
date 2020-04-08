PROJ_ARCH = "Unknown";

equals(QT_ARCH, x86_64) {
    PROJ_ARCH = "x64"
} else : equals(QT_ARCH, i386) {
    PROJ_ARCH = "x86"
}

CONFIG(debug, debug|release) {
    PROJ_SPEC = Debug_$${PROJ_ARCH}
} else {
    PROJ_SPEC = Release_$${PROJ_ARCH}
}
