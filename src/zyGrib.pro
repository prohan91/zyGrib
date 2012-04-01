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


#here is should be some thing like $$PWD/../QWT---/lib -lqwt
win32 {
        INCLUDEPATH += C:/Qwt-6.0.1/include/
        LIBS += -Lbzip2 -lbz2 -Lzlib-1.2.3 -lz -Lproj-4.6.0/src -lproj
        LIBS += -LC:/Qwt-6.0.1/lib/ -lqwt
        DESTDIR = release
        RC_FILE += ../data/img/resource.rc
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

#!win32 {
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
#}

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
           zuFile.h \
    proj-4.6.0/src/projects.h \
    proj-4.6.0/src/proj_api.h \
    proj-4.6.0/src/pj_list.h \
    proj-4.6.0/src/org_proj4_Projections.h \
    proj-4.6.0/src/nad_list.h \
    proj-4.6.0/src/geodesic.h \
    proj-4.6.0/src/geocent.h \
    proj-4.6.0/src/emess.h \
    bzip2/bzlib_private.h \
    bzip2/bzlib.h \
    zlib-1.2.3/zutil.h \
    zlib-1.2.3/zlib.h \
    zlib-1.2.3/zconf.in.h \
    zlib-1.2.3/zconf.h \
    zlib-1.2.3/trees.h \
    zlib-1.2.3/inftrees.h \
    zlib-1.2.3/inflate.h \
    zlib-1.2.3/inffixed.h \
    zlib-1.2.3/inffast.h \
    zlib-1.2.3/deflate.h \
    zlib-1.2.3/crc32.h

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
           zuFile.cpp \
    proj-4.6.0/src/vector1.c \
    proj-4.6.0/src/rtodms.c \
    proj-4.6.0/src/proj_rouss.c \
    proj-4.6.0/src/proj_mdist.c \
    proj-4.6.0/src/pj_zpoly1.c \
    proj-4.6.0/src/PJ_wink2.c \
    proj-4.6.0/src/PJ_wink1.c \
    proj-4.6.0/src/PJ_wag7.c \
    proj-4.6.0/src/PJ_wag3.c \
    proj-4.6.0/src/PJ_wag2.c \
    proj-4.6.0/src/PJ_vandg4.c \
    proj-4.6.0/src/PJ_vandg2.c \
    proj-4.6.0/src/PJ_vandg.c \
    proj-4.6.0/src/pj_utils.c \
    proj-4.6.0/src/PJ_urmfps.c \
    proj-4.6.0/src/PJ_urm5.c \
    proj-4.6.0/src/pj_units.c \
    proj-4.6.0/src/pj_tsfn.c \
    proj-4.6.0/src/pj_transform.c \
    proj-4.6.0/src/PJ_tpeqd.c \
    proj-4.6.0/src/PJ_tmerc.c \
    proj-4.6.0/src/PJ_tcea.c \
    proj-4.6.0/src/PJ_tcc.c \
    proj-4.6.0/src/PJ_sts.c \
    proj-4.6.0/src/pj_strerrno.c \
    proj-4.6.0/src/PJ_sterea.c \
    proj-4.6.0/src/PJ_stere.c \
    proj-4.6.0/src/PJ_somerc.c \
    proj-4.6.0/src/PJ_sconics.c \
    proj-4.6.0/src/PJ_rpoly.c \
    proj-4.6.0/src/PJ_robin.c \
    proj-4.6.0/src/pj_release.c \
    proj-4.6.0/src/pj_qsfn.c \
    proj-4.6.0/src/PJ_putp6.c \
    proj-4.6.0/src/PJ_putp5.c \
    proj-4.6.0/src/PJ_putp4p.c \
    proj-4.6.0/src/PJ_putp3.c \
    proj-4.6.0/src/PJ_putp2.c \
    proj-4.6.0/src/pj_pr_list.c \
    proj-4.6.0/src/PJ_poly.c \
    proj-4.6.0/src/pj_phi2.c \
    proj-4.6.0/src/pj_param.c \
    proj-4.6.0/src/PJ_ortho.c \
    proj-4.6.0/src/pj_open_lib.c \
    proj-4.6.0/src/PJ_omerc.c \
    proj-4.6.0/src/PJ_oea.c \
    proj-4.6.0/src/PJ_ocea.c \
    proj-4.6.0/src/PJ_ob_tran.c \
    proj-4.6.0/src/PJ_nzmg.c \
    proj-4.6.0/src/PJ_nsper.c \
    proj-4.6.0/src/PJ_nocol.c \
    proj-4.6.0/src/PJ_nell_h.c \
    proj-4.6.0/src/PJ_nell.c \
    proj-4.6.0/src/pj_msfn.c \
    proj-4.6.0/src/PJ_moll.c \
    proj-4.6.0/src/PJ_mod_ster.c \
    proj-4.6.0/src/pj_mlfn.c \
    proj-4.6.0/src/PJ_mill.c \
    proj-4.6.0/src/PJ_merc.c \
    proj-4.6.0/src/PJ_mbtfpq.c \
    proj-4.6.0/src/PJ_mbtfpp.c \
    proj-4.6.0/src/PJ_mbt_fps.c \
    proj-4.6.0/src/pj_malloc.c \
    proj-4.6.0/src/PJ_lsat.c \
    proj-4.6.0/src/PJ_loxim.c \
    proj-4.6.0/src/PJ_lcca.c \
    proj-4.6.0/src/PJ_lcc.c \
    proj-4.6.0/src/pj_latlong.c \
    proj-4.6.0/src/PJ_lask.c \
    proj-4.6.0/src/PJ_larr.c \
    proj-4.6.0/src/PJ_lagrng.c \
    proj-4.6.0/src/PJ_laea.c \
    proj-4.6.0/src/PJ_labrd.c \
    proj-4.6.0/src/PJ_krovak.c \
    proj-4.6.0/src/pj_inv.c \
    proj-4.6.0/src/pj_init.c \
    proj-4.6.0/src/PJ_imw_p.c \
    proj-4.6.0/src/PJ_hatano.c \
    proj-4.6.0/src/PJ_hammer.c \
    proj-4.6.0/src/pj_gridlist.c \
    proj-4.6.0/src/pj_gridinfo.c \
    proj-4.6.0/src/PJ_goode.c \
    proj-4.6.0/src/PJ_gnom.c \
    proj-4.6.0/src/PJ_gn_sinu.c \
    proj-4.6.0/src/PJ_gins8.c \
    proj-4.6.0/src/PJ_geos.c \
    proj-4.6.0/src/pj_geocent.c \
    proj-4.6.0/src/pj_gauss.c \
    proj-4.6.0/src/PJ_gall.c \
    proj-4.6.0/src/pj_fwd.c \
    proj-4.6.0/src/PJ_fouc_s.c \
    proj-4.6.0/src/PJ_fahey.c \
    proj-4.6.0/src/pj_factors.c \
    proj-4.6.0/src/pj_errno.c \
    proj-4.6.0/src/PJ_eqdc.c \
    proj-4.6.0/src/PJ_eqc.c \
    proj-4.6.0/src/pj_ellps.c \
    proj-4.6.0/src/pj_ell_set.c \
    proj-4.6.0/src/PJ_eck5.c \
    proj-4.6.0/src/PJ_eck4.c \
    proj-4.6.0/src/PJ_eck3.c \
    proj-4.6.0/src/PJ_eck2.c \
    proj-4.6.0/src/PJ_eck1.c \
    proj-4.6.0/src/pj_deriv.c \
    proj-4.6.0/src/PJ_denoy.c \
    proj-4.6.0/src/pj_datums.c \
    proj-4.6.0/src/pj_datum_set.c \
    proj-4.6.0/src/PJ_crast.c \
    proj-4.6.0/src/PJ_collg.c \
    proj-4.6.0/src/PJ_chamb.c \
    proj-4.6.0/src/PJ_cea.c \
    proj-4.6.0/src/PJ_cc.c \
    proj-4.6.0/src/PJ_cass.c \
    proj-4.6.0/src/PJ_bonne.c \
    proj-4.6.0/src/PJ_boggs.c \
    proj-4.6.0/src/PJ_bipc.c \
    proj-4.6.0/src/PJ_bacon.c \
    proj-4.6.0/src/pj_auth.c \
    proj-4.6.0/src/PJ_august.c \
    proj-4.6.0/src/pj_apply_gridshift.c \
    proj-4.6.0/src/PJ_aitoff.c \
    proj-4.6.0/src/PJ_airy.c \
    proj-4.6.0/src/PJ_aeqd.c \
    proj-4.6.0/src/PJ_aea.c \
    proj-4.6.0/src/p_series.c \
    proj-4.6.0/src/nad_intr.c \
    proj-4.6.0/src/nad_init.c \
    proj-4.6.0/src/nad_cvt.c \
    proj-4.6.0/src/mk_cheby.c \
    proj-4.6.0/src/jniproj.c \
    proj-4.6.0/src/geod_set.c \
    proj-4.6.0/src/geod_inv.c \
    proj-4.6.0/src/geod_for.c \
    proj-4.6.0/src/geocent.c \
    proj-4.6.0/src/gen_cheb.c \
    proj-4.6.0/src/emess.c \
    proj-4.6.0/src/dmstor.c \
    proj-4.6.0/src/biveval.c \
    proj-4.6.0/src/bchgen.c \
    proj-4.6.0/src/bch2bps.c \
    proj-4.6.0/src/adjlon.c \
    proj-4.6.0/src/aasincos.c \
    bzip2/randtable.c \
    bzip2/huffman.c \
    bzip2/decompress.c \
    bzip2/crctable.c \
    bzip2/compress.c \
    bzip2/bzlib.c \
    bzip2/blocksort.c \
    zlib-1.2.3/zutil.c \
    zlib-1.2.3/uncompr.c \
    zlib-1.2.3/trees.c \
    zlib-1.2.3/inftrees.c \
    zlib-1.2.3/inflate.c \
    zlib-1.2.3/inffast.c \
    zlib-1.2.3/infback.c \
    zlib-1.2.3/gzio.c \
    zlib-1.2.3/deflate.c \
    zlib-1.2.3/crc32.c \
    zlib-1.2.3/adler32.c \
    proj-4.6.0/src/pj_list.c

OTHER_FILES += \
    proj-4.6.0/src/proj_config.h


