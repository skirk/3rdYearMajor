TEMPLATE = app
CONFIG += console
CONFIG -= qt

INCLUDEPATH += ./include \
                /usr/include/libxml2

OBJECTS_DIR = ./obj
SOURCES += \
    src/DataBase.cpp \
    src/Loader.cpp \
    src/main.cpp \
    src/Node.cpp \
    src/NodeNetwork.cpp

HEADERS += \
    include/DataBase.h \
    include/Loader.h \
    include/Node.h \
    include/NodeNetwork.h \
    include/Slot.h


LIBS += -L/usr/local/lib -lxml2

OTHER_FILES += \
    nodes/test.xml \
    nodes/test2.xml

