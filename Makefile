QTBIN=/usr/bin
#QTBIN=/opt/qt/qt/bin
#QTBIN=/usr/local/Trolltech/Qt-4.7.0/bin

INSTALLDIR=$(HOME)/zyGrib

MACQTBIN=/opt/local/bin

all: zyGrib

SRC= src/*.h src/*.cpp \
     src/*/*.h src/*/*.cpp src/*/*.c \
     src/*/*/*.h src/*/*/*.c \


mac: $(SRC)
	rm -f  ./zyGrib
	rm -fr ./zyGrib.app
	rm -f  src/Makefile
	cd src/bzip2; $(MACQTBIN)/qmake; make
	cd src/zlib-1.2.3; $(MACQTBIN)/qmake; make
	cd src/proj-4.6.0/src/; $(MACQTBIN)/qmake; make
	cd src; $(MACQTBIN)/qmake; make

clean:
	rm -f  zyGrib
	rm -fr zyGrib.app
	rm -f  src/zyGrib
	rm -f  src/release/zyGrib.exe
	cd src;	$(QTBIN)/qmake; make clean

veryclean:
	rm -f  zyGrib
	rm -fr zyGrib.app
	rm -f  src/zyGrib
	rm -f  src/release/zyGrib.exe
	cd src/bzip2; $(QTBIN)/qmake; make clean
	cd src/zlib-1.2.3; $(QTBIN)/qmake; make clean
	cd src/proj-4.6.0/src/; $(QTBIN)/qmake; make clean
	cd src;	$(QTBIN)/qmake; make clean
	rm -f src/zlib-1.2.3/libz.a
	rm -f src/proj-4.6.0/src/libproj.a
	rm -f src/bzip2/libbz2.a

zyGrib: $(SRC)
	@ echo
	@ echo
	rm -f ./zyGrib
	cd src/bzip2; $(QTBIN)/qmake; make
	cd src/zlib-1.2.3; $(QTBIN)/qmake; make
	cd src/proj-4.6.0/src/; $(QTBIN)/qmake; make
	cd src; $(QTBIN)/qmake; make
	@ echo "-----------------------------------"
	@ echo "#!/bin/bash" >> ./zyGrib
	@ echo "cd `pwd`" >> ./zyGrib
	@ echo 'src/zyGrib $$*' >> ./zyGrib
	@ chmod 755 ./zyGrib

install: zyGrib
	mkdir -p $(INSTALLDIR)
	mkdir -p $(INSTALLDIR)/bin
	cp -a data $(INSTALLDIR)
	cp -a grib $(INSTALLDIR)
	rm -f ./zyGrib
	rm -f $(INSTALLDIR)/bin/zyGrib
	cp  -a src/zyGrib $(INSTALLDIR)/bin
	echo "#!/bin/bash" >> ./zyGrib
	echo "cd $(INSTALLDIR)" >> ./zyGrib
	echo 'bin/zyGrib $$*' >> ./zyGrib
	chmod 755 ./zyGrib
	cp -af zyGrib $(INSTALLDIR)


