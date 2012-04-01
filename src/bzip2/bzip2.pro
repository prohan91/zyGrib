
TEMPLATE=lib
TARGET=bz2
CONFIG+=staticlib
DEPENDPATH += .
INCLUDEPATH += .

macx {
	CONFIG += i386
}

# Input
HEADERS += bzlib.h \
           bzlib_private.h

SOURCES += blocksort.c \
           bzip2.c \
           bzip2recover.c \
           bzlib.c \
           compress.c \
           crctable.c \
           decompress.c \
           dlltest.c \
           huffman.c \
           mk251.c \
           randtable.c \
           unzcrash.c

