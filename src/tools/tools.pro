TEMPLATE = subdirs

TOOLS_SUBDIRS = src_tools_bootstrap src_tools_moc src_tools_rcc src_tools_qdoc
contains(QT_CONFIG, dbus): TOOLS_SUBDIRS += src_tools_qdbusxml2cpp src_tools_qdbuscpp2xml
!contains(QT_CONFIG, no-gui): TOOLS_SUBDIRS += src_tools_uic
# Set subdir and respective target name
src_tools_bootstrap.subdir = $$PWD/bootstrap
src_tools_bootstrap.target = sub-tools-bootstrap
src_tools_moc.subdir = $$PWD/moc
src_tools_moc.target = sub-moc
src_tools_rcc.subdir = $$PWD/rcc
src_tools_rcc.target = sub-rcc
src_tools_uic.subdir = $$PWD/uic
src_tools_uic.target = sub-uic
src_tools_qdoc.subdir = $$QT_SOURCE_TREE/src/tools/qdoc
src_tools_qdoc.target = sub-qdoc
contains(QT_CONFIG, dbus) {
    src_tools_qdbusxml2cpp.subdir = $$QT_SOURCE_TREE/src/tools/qdbusxml2cpp
    src_tools_qdbusxml2cpp.target = sub-qdbusxml2cpp
    src_tools_qdbuscpp2xml.subdir = $$QT_SOURCE_TREE/src/tools/qdbuscpp2xml
    src_tools_qdbuscpp2xml.target = sub-qdbuscpp2xml
}

!wince*:!ordered {
    # Set dependencies for each subdir
    src_tools_moc.depends = src_tools_bootstrap
    src_tools_rcc.depends = src_tools_bootstrap
    src_tools_uic.depends = src_tools_bootstrap
    src_tools_qdoc.depends = src_tools_bootstrap
    contains(QT_CONFIG, dbus) {
        src_tools_qdbusxml2cpp.depends = src_tools_bootstrap
        src_tools_qdbuscpp2xml.depends = src_tools_bootstrap
    }
}

SUBDIRS = $$TOOLS_SUBDIRS
