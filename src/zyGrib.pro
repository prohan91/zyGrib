CONFIG += qt release
#CONFIG += qt debug console

TEMPLATE = app
TARGET   = zyGrib

DEPENDPATH  += . util map GUI
INCLUDEPATH += . util map GUI bzip2 zlib-1.2.3 proj-4.6.0/src
INCLUDEPATH += curvedrawer

# LIBS += -Lbzip2 -lbz2 -Lzlib-1.2.3 -lz -Lproj-4.6.0/src -lproj

# ----------------------------------------------------
# platform specific
# ----------------------------------------------------
win32 {
	INCLUDEPATH += C:/Qwt-6.0.0/include/
	LIBS += -Lbzip2 -lbz2 -Lzlib-1.2.3 -lz -Lproj-4.6.0/src -lproj
	LIBS += -LC:/Qwt-6.0.0/lib/ -lqwt
	DESTDIR = release
	RC_FILE += resource.rc
}
else {
macx {
	QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.5
	INCLUDEPATH += /usr/local/qwt-6.0.1/include/
	LIBS += -Lbzip2 -lbz2 -Lzlib-1.2.3 -lz -Lproj-4.6.0/src -lproj
	LIBS += -L/usr/local/qwt-6.0.1/lib/ -lqwt
	DESTDIR = ..
	CONFIG += i386
	ICON = ../data/img/zyGrib.icns
}
else {
	INCLUDEPATH += /usr/include/qwt
	LIBS += -lbz2 -lz -lproj -lqwt
	DESTDIR = .
}
}
# ----------------------------------------------------

CFLAGS += -std=c99 

OBJECTS_DIR = objs
MOC_DIR = objs
UI_DIR  = GUI

QT += network xml

CODECFORTR = UTF-8
CODECFORSRC = UTF-8
TRANSLATIONS =  ../data/tr/zyGrib_fr.ts \
				../data/tr/zyGrib_cz.ts \
				../data/tr/zyGrib_de.ts \
				../data/tr/zyGrib_it.ts \
				../data/tr/zyGrib_nl.ts \
				../data/tr/zyGrib_pt.ts \
				../data/tr/zyGrib_ru.ts \
				../data/tr/zyGrib_ar.ts \
				../data/tr/zyGrib_es.ts

!win32 {
	# conditional, because uic dont work in my cross compilator environment.
	# ui_*.h files are made under linux before windows compilation.
	
	FORMS += GUI/PositionEditorWidget.ui \
		 	 GUI/PoiEditorDialog.ui \
			 GUI/ColorEditorWidget.ui \
			 GUI/LineEditorWidget.ui \
			 GUI/TextStyleEditorWidget.ui \
			 GUI/GraphicsParamsDialog.ui \
			 GUI/MeteotableOptionsDialog.ui \
		 	 GUI/AngleConverterWidget.ui 
}

HEADERS += \
			 GUI/PositionEditorWidget.h \
			 GUI/ColorEditorWidget.h \
			 GUI/LineEditorWidget.h \
			 GUI/TextStyleEditorWidget.h \
		 	 GUI/AngleConverterWidget.h \
		 	 GUI/AngleConverterDialog.h \
				curvedrawer/BoatSpeed.h \
				curvedrawer/CurveDrawer.h \
				curvedrawer/CustomQwtClasses.h \
           BoardPanel.h \
		   ColorScale.h \
		   ColorScaleWidget.h \
		   DataDefines.h \
		   DataColors.h \
		   DataQString.h \
		   DataMeteoAbstract.h \
           DataPointInfo.h \
           DateChooser.h \
		   DialogBoxBase.h \
		   DialogBoxColumn.h \
           DialogFonts.h \
           DialogGraphicsParams.h \
           DialogLoadGRIB.h \
           DialogLoadIAC.h \
           DialogLoadMBLUE.h \
           DialogProxy.h \
           DialogServerStatus.h \
           DialogUnits.h \
           FileLoader.h \
           FileLoaderGRIB.h \
           FileLoaderIAC.h \
           FileLoaderMBLUE.h \
           Font.h \
           GshhsRangsReader.h \
           GshhsReader.h \
           GisReader.h \
           GribAnimator.h \
           GribPlot.h \
           GribReader.h \
           GribRecord.h \
		   GriddedPlotter.h \
		   GriddedRecord.h \
		   GriddedReader.h \
           IacPlot.h \
           IacReader.h \
           ImageWriter.h \
		   IrregularGridded.h \
           IsoLine.h \
		   LongTaskProgress.h \
           LonLatGrid.h \
           MbzFile.h \
           MbluePlot.h \
           MblueReader.h \
           MblueRecord.h \
           MeteoTable.h \
           MeteoTableWidget.h \
           MeteotableOptionsDialog.h \
           MainWindow.h \
           MenuBar.h \
           Orthodromie.h \
           POI.h \
           POI_Editor.h \
           PositionEditor.h \
           Projection.h \
           MapDrawer.h \
           Settings.h \
           Terrain.h \
           Util.h \
           Version.h \
           zuFile.h

SOURCES += \
			 GUI/PositionEditorWidget.cpp \
			 GUI/ColorEditorWidget.cpp \
			 GUI/LineEditorWidget.cpp \
			 GUI/TextStyleEditorWidget.cpp \
		 	 GUI/AngleConverterWidget.cpp \
		 	 GUI/AngleConverterDialog.cpp \
				curvedrawer/BoatSpeed.cpp \
				curvedrawer/CurveDrawer.cpp \
				curvedrawer/CustomQwtClasses.cpp \
        MbzFile.cpp \
		MblueRecord.cpp \
		MblueReader.cpp \
		MbluePlot.cpp \
           BoardPanel.cpp \
		   ColorScale.cpp \
		   ColorScaleWidget.cpp \
		   DataColors.cpp \
		   DataQString.cpp \
		   DataMeteoAbstract.cpp \
           DataPointInfo.cpp \
           DateChooser.cpp \
		   DialogBoxColumn.cpp \
           DialogFonts.cpp \
           DialogGraphicsParams.cpp \
           DialogLoadGRIB.cpp \
           DialogLoadIAC.cpp \
           DialogLoadMBLUE.cpp \
           DialogProxy.cpp \
           DialogServerStatus.cpp \
           DialogUnits.cpp \
           FileLoaderGRIB.cpp \
           FileLoaderIAC.cpp \
           FileLoaderMBLUE.cpp \
           Font.cpp \
		   GriddedPlotter.cpp \
		   GriddedReader.cpp \
		   GriddedRecord.cpp \
           GshhsRangsReader.cpp \
           GshhsReader.cpp \
           GribAnimator.cpp \
           GribPlot.cpp \
           GisReader.cpp \
           GribReader.cpp \
           GribRecord.cpp \
           IacPlot.cpp \
           IacReader.cpp \
           IacReaderUtil.cpp \
           ImageWriter.cpp \
		   IrregularGridded.cpp \
           IsoLine.cpp \
		   LongTaskProgress.cpp \
           LonLatGrid.cpp \
           main.cpp \
           MainWindow.cpp \
           MenuBar.cpp \
           MeteoTable.cpp \
           MeteoTableWidget.cpp \
           MeteotableOptionsDialog.cpp \
           Orthodromie.cpp \
           POI.cpp \
           POI_Editor.cpp \
           PositionEditor.cpp \
           Projection.cpp \
           Projection_libproj.cpp \
           MapDrawer.cpp \
           Settings.cpp \
           Terrain.cpp \
           Util.cpp \
           zuFile.cpp


