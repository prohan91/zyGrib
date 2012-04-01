/**********************************************************************
zyGrib: meteorological GRIB file viewer
Copyright (C) 2008-2010 - Jacques Zaninetti - http://www.zygrib.org

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
***********************************************************************/
#include <QFile>

#include "MenuBar.h"
#include "Font.h"
#include "Util.h"
#include "Projection.h"

//===================================================================================
void ZeroOneActionGroup::addAction(QAction *act)
{
	lsactions.append(act);
	connect(act, SIGNAL(triggered(bool)),
            	this,  SLOT(slot_actionTrigerred(bool)));
}
//------------------------------------------------------------------
void ZeroOneActionGroup::slot_actionTrigerred(bool b)
{
	QAction *act = (QAction *) sender();
	setCheckedAction(act, b);
}
//------------------------------------------------------------------
void ZeroOneActionGroup::setCheckedAction(QAction *act, bool b)
{
	for (int i=0; i<lsactions.size(); i++) {
		if (lsactions.at(i)== act) {
			lsactions.at(i)->setChecked(b);
		}
		else {
			lsactions.at(i)->setChecked(false);
		}
	}
	if (b)
		emit triggered( act );
	else
		emit triggered( NULL );
}

//===================================================================================
MenuBar::MenuBar (QWidget *parent, bool withmblue)
    : QMenuBar (parent)
{
    //-------------------------------------
    // Menu + Actions
    //-------------------------------------
    menuFile = new QMenu(tr("File"));
        acFile_Open = addAction(menuFile,
        			tr("Open"), tr("Ctrl+O"),
                    tr("Open a GRIB file"), Util::pathImg("fileopen.png"));
        acFile_Close = addAction(menuFile,
        			tr("Close"), tr("Ctrl+W"),
                    tr("Close"), Util::pathImg("fileclose.png"));
        menuFile->addSeparator();
        acFile_Load_GRIB = addAction(menuFile,
        			tr("Download GRIB"), tr("Ctrl+D"),
                    tr("Download"), Util::pathImg("network.png"));
        acFile_GribServerStatus = addAction(menuFile,
        			tr("GRIB server status"), tr("Ctrl+R"),
                    tr("GRIB file server status"), Util::pathImg("connect_no.png"));

        acFile_Load_IAC = addAction(menuFile,
        	tr("IAC fleetcode NOAA"), tr("Ctrl+L"),
			tr("Download current IAC file (fleetcode) from NOAA - Analyse or Forecast +24h - Europe"), "");

		QMenu *menutmp = new QMenu (tr("Meteoblue"));
			acMBlue_fastInterpolation = addActionCheck (menutmp,
					tr("Fast interpolation"), tr(""),
					tr("Use a faster but a little less accurate interpolation"), "");
			acMBlueSwiss_Load = addAction (menutmp,
					tr("Load Meteoblue file : Swiss"), tr("Ctrl+B"),
					tr("Download Meteoblue file (Swiss)"), Util::pathImg("meteoblue.png"));
			acMBlueSwiss_ShowArea = addActionCheck (menutmp, 
					tr("Show area : Swiss"), "",
					tr("Show Meteoblue area (Swiss)"));
		if (withmblue)
			menuFile->addMenu (menutmp);
			
        menuFile->addSeparator();
        acFile_Info_GRIB = addAction(menuFile,
        			tr("File information"), tr("Ctrl+I"),
                    tr("GRIB file information"), Util::pathImg("info.png"));
        menuFile->addSeparator();
        ac_CreateAnimation = addAction(menuFile,
        			tr("Create animation"), tr("Ctrl+A"),
                    tr("Create animation with GRIB data"), Util::pathImg("anim.png"));
        ac_ExportImage = addAction(menuFile,
        			tr("Save current image"), tr("Ctrl+S"),"",Util::pathImg("media-floppy.png"));
        menuFile->addSeparator();
        acFile_Quit = addAction(menuFile,
                    tr("Quit"), tr("Ctrl+Q"),
                    tr("Bye"), Util::pathImg("exit.png"));
    addMenu(menuFile);
	
    //-------------------------------------
    menuAltitude = new QMenu(tr("Altitude"));
		acAlt_GroupAltitude = new QActionGroup (menuAltitude);
			acAlt_MSL = addActionCheck(menuAltitude, tr("Sea level"), "", "");
			acAlt_GND = addActionCheck(menuAltitude, tr("Surface"), "", "");
			acAlt_sigma995 = addActionCheck(menuAltitude, tr("Sigma 995"), "", "");
			acAlt_GND_1m = addActionCheck(menuAltitude, tr("1 m above ground"), "", "");
			acAlt_GND_2m = addActionCheck(menuAltitude, tr("2 m above ground"), "", "");
			acAlt_GND_3m = addActionCheck(menuAltitude, tr("3 m above ground"), "", "");
			acAlt_GND_10m = addActionCheck(menuAltitude, tr("10 m above ground"), "", "");
			acAlt_925hpa = addActionCheck(menuAltitude, tr("925 hPa (≈ 760 m)"), "", "");
			acAlt_850hpa = addActionCheck(menuAltitude, tr("850 hPa (≈ 1460 m)"), "", "");
			acAlt_700hpa = addActionCheck(menuAltitude, tr("700 hPa (≈ 3000 m)"), "", "");
			acAlt_500hpa = addActionCheck(menuAltitude, tr("500 hPa (≈ 5600 m)"), "", "");
			acAlt_300hpa = addActionCheck(menuAltitude, tr("300 hPa (≈ 9200 m)"), "", "");
			acAlt_200hpa = addActionCheck(menuAltitude, tr("200 hPa (≈ 11800 m)"), "", "");
			acAlt_Atmosphere = addActionCheck(menuAltitude, tr("Atmosphere"), "", "");
			acAlt_GroupAltitude->addAction (acAlt_MSL);
			acAlt_GroupAltitude->addAction (acAlt_GND);
			acAlt_GroupAltitude->addAction (acAlt_sigma995);
			acAlt_GroupAltitude->addAction (acAlt_GND_1m);
			acAlt_GroupAltitude->addAction (acAlt_GND_2m);
			acAlt_GroupAltitude->addAction (acAlt_GND_3m);
			acAlt_GroupAltitude->addAction (acAlt_GND_10m);
			acAlt_GroupAltitude->addAction (acAlt_925hpa);
			acAlt_GroupAltitude->addAction (acAlt_850hpa);
			acAlt_GroupAltitude->addAction (acAlt_700hpa);
			acAlt_GroupAltitude->addAction (acAlt_500hpa);
			acAlt_GroupAltitude->addAction (acAlt_300hpa);
			acAlt_GroupAltitude->addAction (acAlt_200hpa);
			acAlt_GroupAltitude->addAction (acAlt_Atmosphere);
        menuAltitude->addSeparator();
		acAlt_GroupGeopotLine = new ZeroOneActionGroup (menuAltitude);
			acAlt_GeopotLine_925hpa = addActionCheck (menuAltitude, tr("Geopotential altitude 925 hpa"), "", "");
			acAlt_GeopotLine_850hpa = addActionCheck (menuAltitude, tr("Geopotential altitude 850 hpa"), "", "");
			acAlt_GeopotLine_700hpa = addActionCheck (menuAltitude, tr("Geopotential altitude 700 hpa"), "", "");
			acAlt_GeopotLine_500hpa = addActionCheck (menuAltitude, tr("Geopotential altitude 500 hpa"), "", "");
			acAlt_GeopotLine_300hpa = addActionCheck(menuAltitude, tr("Geopotential altitude 300 hpa"), "", "");
			acAlt_GeopotLine_200hpa = addActionCheck(menuAltitude, tr("Geopotential altitude 200 hpa"), "", "");
			acAlt_GroupGeopotLine->addAction (acAlt_GeopotLine_925hpa);
			acAlt_GroupGeopotLine->addAction (acAlt_GeopotLine_850hpa);
			acAlt_GroupGeopotLine->addAction (acAlt_GeopotLine_700hpa);
			acAlt_GroupGeopotLine->addAction (acAlt_GeopotLine_500hpa);
			acAlt_GroupGeopotLine->addAction (acAlt_GeopotLine_300hpa);
			acAlt_GroupGeopotLine->addAction (acAlt_GeopotLine_200hpa);
			
            menuGeopotStep = new QMenu(tr("Spacing (m)"));
            acAlt_GroupGeopotStep = new QActionGroup (menuGeopotStep);
                acAlt_GeopotStep_1  = addActionCheck(menuGeopotStep, tr("1"), "", "");
                acAlt_GeopotStep_2  = addActionCheck(menuGeopotStep, tr("2"), "", "");
                acAlt_GeopotStep_5  = addActionCheck(menuGeopotStep, tr("5"), "", "");
                acAlt_GeopotStep_10 = addActionCheck(menuGeopotStep, tr("10"), "", "");
                acAlt_GeopotStep_20 = addActionCheck(menuGeopotStep, tr("20"), "", "");
                acAlt_GeopotStep_50 = addActionCheck(menuGeopotStep, tr("50"), "", "");
                acAlt_GeopotStep_100 = addActionCheck(menuGeopotStep, tr("100"), "", "");
                acAlt_GroupGeopotStep->addAction (acAlt_GeopotStep_1);
                acAlt_GroupGeopotStep->addAction (acAlt_GeopotStep_2);
                acAlt_GroupGeopotStep->addAction (acAlt_GeopotStep_5);
                acAlt_GroupGeopotStep->addAction (acAlt_GeopotStep_10);
                acAlt_GroupGeopotStep->addAction (acAlt_GeopotStep_20);
                acAlt_GroupGeopotStep->addAction (acAlt_GeopotStep_50);
                acAlt_GroupGeopotStep->addAction (acAlt_GeopotStep_100);
            menuAltitude->addMenu(menuGeopotStep);
			acAlt_GeopotLabels = addActionCheck(menuAltitude, tr("Geopotentials labels"), "","");
			
	//-------------------------------------
    menuGrib = new QMenu(tr("Data"));
	
		acView_GroupColorMap = new ZeroOneActionGroup(menuGrib);
			acView_WindColors = addActionCheck(menuGrib, tr("Wind map"), "", "");
			acView_CurrentColors = addActionCheck(menuGrib, tr("Current map"), "", "");
			acView_RainColors = addActionCheck(menuGrib, tr("Precipitation map"),"","");
			acView_CloudColors = addActionCheck(menuGrib, tr("Cloud cover"), "","");
			acView_HumidColors = addActionCheck(menuGrib, tr("Relative humidity map"),"","");
			acView_TempColors = addActionCheck(menuGrib, tr("Temperature map"),"","");
			acView_DeltaDewpointColors = addActionCheck(menuGrib, tr("Gap temperature-dew point"), "", "");
			acView_SnowCateg = addActionCheck(menuGrib, tr("Snow (snowfall possible)"), "", "");
			acView_SnowDepth = addActionCheck(menuGrib, tr("Snow (depth)"), "", "");
			acView_FrzRainCateg = addActionCheck(menuGrib, tr("Frozen rain (rainfall possible)"), "", "");
			acView_CAPEsfc = addActionCheck(menuGrib, tr("CAPE (surface)"), "", "");
        menuGrib->addSeparator();
			acView_SigWaveHeight = addActionCheck(menuGrib, tr("Significant wave height"), "", "");
			acView_MaxWaveHeight = addActionCheck(menuGrib, tr("Maximum wave height"), "", "");
			acView_WhiteCapProb = addActionCheck(menuGrib, tr("Whitecap probability"), "", "");
			acView_GroupColorMap->addAction(acView_WindColors);
			acView_GroupColorMap->addAction(acView_CurrentColors);
			acView_GroupColorMap->addAction(acView_RainColors);
			acView_GroupColorMap->addAction(acView_CloudColors);
			acView_GroupColorMap->addAction(acView_HumidColors);
			acView_GroupColorMap->addAction(acView_TempColors);
			acView_GroupColorMap->addAction(acView_DeltaDewpointColors);
			acView_GroupColorMap->addAction(acView_SnowCateg);
			acView_GroupColorMap->addAction(acView_SnowDepth);
			acView_GroupColorMap->addAction(acView_FrzRainCateg);
			acView_GroupColorMap->addAction(acView_CAPEsfc);
		//-------------------------------------------------------
			acView_GroupColorMap->addAction(acView_SigWaveHeight);
			acView_GroupColorMap->addAction(acView_MaxWaveHeight);
			acView_GroupColorMap->addAction(acView_WhiteCapProb);

        //--------------------------------
        menuGrib->addSeparator();
        acView_WindArrow = addActionCheck(menuGrib, tr("Wind arrows"), tr("Ctrl+J"),
                    tr("Show wind arrows"));
        acView_CurrentArrow = addActionCheck(menuGrib, tr("Current arrows"), "",
                    tr("Show current arrows"));
        //--------------------------------
        menuGrib->addSeparator();
		acView_Isobars = addActionCheck(menuGrib, tr("Isobars (MSL)"), "",
						"");
        acView_PressureMinMax = addActionCheck(menuGrib, tr("Pressure Low High"), "",
                            tr("Show Low (L) and Hight (H) pressure points"));
        //--------------------------------
        menuGrib->addSeparator();
        acView_TemperatureLabels = addActionCheck(menuGrib,
        			tr("Temperature"), tr("Ctrl+T"),
                    "");
		acView_Isotherms0 = addActionCheck(menuGrib, tr("Isotherms (temperature 0°C)"), "","");
		acView_Isotherms2m = addActionCheck(menuGrib, tr("Isotherms (altitude 2m)"), "","");
        //--------------------------------
        menuGrib->addSeparator();
		menuViewOptions = new QMenu (tr("Options"));
        menuGrib->addMenu (menuViewOptions);
        //--------------------------------
		menuIsobarsStep = new QMenu(tr("Isobars spacing (hPa)"));
		acView_GroupIsobarsStep = new QActionGroup(menuIsobarsStep);
			acView_IsobarsStep1 = addActionCheck(menuIsobarsStep, tr("1"), "", "");
			acView_IsobarsStep2 = addActionCheck(menuIsobarsStep, tr("2"), "", "");
			acView_IsobarsStep3 = addActionCheck(menuIsobarsStep, tr("3"), "", "");
			acView_IsobarsStep4 = addActionCheck(menuIsobarsStep, tr("4"), "", "");
			acView_IsobarsStep5 = addActionCheck(menuIsobarsStep, tr("5"), "", "");
			acView_IsobarsStep6 = addActionCheck(menuIsobarsStep, tr("6"), "", "");
			acView_IsobarsStep8 = addActionCheck(menuIsobarsStep, tr("8"), "", "");
			acView_IsobarsStep10 = addActionCheck(menuIsobarsStep, tr("10"), "", "");
			acView_GroupIsobarsStep->addAction(acView_IsobarsStep1);
			acView_GroupIsobarsStep->addAction(acView_IsobarsStep2);
			acView_GroupIsobarsStep->addAction(acView_IsobarsStep3);
			acView_GroupIsobarsStep->addAction(acView_IsobarsStep4);
			acView_GroupIsobarsStep->addAction(acView_IsobarsStep5);
			acView_GroupIsobarsStep->addAction(acView_IsobarsStep6);
			acView_GroupIsobarsStep->addAction(acView_IsobarsStep8);
			acView_GroupIsobarsStep->addAction(acView_IsobarsStep10);
		menuViewOptions->addMenu(menuIsobarsStep);
        //--------------------------------
		menuIsotherms0Step = new QMenu(tr("Isotherms 0°C spacing (m)"));
		acView_GroupIsotherms0Step    = new QActionGroup(menuIsotherms0Step);
			acView_Isotherms0Step10   = addActionCheck(menuIsotherms0Step, tr("10"), "", "");
			acView_Isotherms0Step20   = addActionCheck(menuIsotherms0Step, tr("20"), "", "");
			acView_Isotherms0Step50   = addActionCheck(menuIsotherms0Step, tr("50"), "", "");
			acView_Isotherms0Step100  = addActionCheck(menuIsotherms0Step, tr("100"), "", "");
			acView_Isotherms0Step200  = addActionCheck(menuIsotherms0Step, tr("200"), "", "");
			acView_Isotherms0Step500  = addActionCheck(menuIsotherms0Step, tr("500"), "", "");
			acView_Isotherms0Step1000 = addActionCheck(menuIsotherms0Step, tr("1000"), "","");
			acView_GroupIsotherms0Step->addAction(acView_Isotherms0Step10);
			acView_GroupIsotherms0Step->addAction(acView_Isotherms0Step20);
			acView_GroupIsotherms0Step->addAction(acView_Isotherms0Step50);
			acView_GroupIsotherms0Step->addAction(acView_Isotherms0Step100);
			acView_GroupIsotherms0Step->addAction(acView_Isotherms0Step200);
			acView_GroupIsotherms0Step->addAction(acView_Isotherms0Step500);
			acView_GroupIsotherms0Step->addAction(acView_Isotherms0Step1000);
		menuViewOptions->addMenu(menuIsotherms0Step);
        //--------------------------------
		menuIsotherms2mStep = new QMenu(tr("Isotherms 2m spacing (°C)"));
		acView_GroupIsotherms2mStep = new QActionGroup(menuIsotherms2mStep);
			acView_Isotherms2mStep1 = addActionCheck(menuIsotherms2mStep, tr("1"), "", "");
			acView_Isotherms2mStep2 = addActionCheck(menuIsotherms2mStep, tr("2"), "", "");
			acView_Isotherms2mStep5 = addActionCheck(menuIsotherms2mStep, tr("5"), "", "");
			acView_Isotherms2mStep10 = addActionCheck(menuIsotherms2mStep, tr("10"), "", "");
			acView_GroupIsotherms2mStep->addAction(acView_Isotherms2mStep1);
			acView_GroupIsotherms2mStep->addAction(acView_Isotherms2mStep2);
			acView_GroupIsotherms2mStep->addAction(acView_Isotherms2mStep5);
			acView_GroupIsotherms2mStep->addAction(acView_Isotherms2mStep10);
		menuViewOptions->addMenu(menuIsotherms2mStep);
        //--------------------------------
        acView_IsobarsLabels = addActionCheck (menuViewOptions, 
							tr("Isobars labels"), "", "");
        acView_Isotherms0Labels = addActionCheck (menuViewOptions,
        					tr("Isotherms 0°C labels"), "", "");
        acView_Isotherms2mLabels = addActionCheck (menuViewOptions,
        					tr("Isotherms 2m labels"), "",  "");
		//------------------------------------------------------------------
        menuViewOptions->addSeparator();
        acView_DuplicateFirstCumulativeRecord = addActionCheck(menuViewOptions,
        			tr("NOAA-GFS")+": "+tr("Duplicate first cumulative record"), "",
                    "");
        acView_DuplicateMissingWaveRecords = addActionCheck(menuViewOptions,
        			tr("FNMOC-WW3")+": "+tr("Duplicate missing wave records"), "",
                    tr("")
					);
        acView_InterpolateValues = addActionCheck(menuViewOptions,
        			tr("Numerical data interpolation"), "",
                    "");

        acView_ColorMapSmooth = addActionCheck(menuViewOptions,
        			tr("Smooth colors"), tr("Ctrl+F"),
                    "");
        //--------------------------------
        menuViewOptions->addSeparator();
        acView_Barbules = addActionCheck(menuViewOptions, tr("Wind barbs"), "",
                    tr("Show barbs on wind arrows"));
        acView_ThinWindArrows = addActionCheck(menuViewOptions, tr("Thin wind arrows"), "",
                    tr("Draw thin wind arrows"));
        acView_WindArrowsOnGribGrid = addActionCheck(menuViewOptions,
        			tr("Wind arrows on Grib grid"), "",
                    "");
        acView_CurrentArrowsOnGribGrid = addActionCheck(menuViewOptions,
        			tr("Current arrows on Grib grid"), "",
                    "");
        menuViewOptions->addSeparator();
        acView_GribGrid = addActionCheck(menuViewOptions, tr("Show Grib grid"), 
					tr("Ctrl+X"), tr("Show GRIB grid"));
        acView_ShowColorScale = addActionCheck(menuViewOptions, tr("Show color scale"),
					tr("Ctrl+Y"), tr("Show color scale"));
        acView_ShowBoardPanel = addActionCheck(menuViewOptions, tr("Show values panel"),
					tr("Ctrl+V"), tr("Show values panel"));

    addMenu(menuGrib);
    addMenu(menuAltitude);

    //-------------------------------------
    menuMap = new QMenu(tr("Earth"));
		QMenu *menuQuality = new QMenu(tr("Map quality"));
        acMap_GroupQuality = new QActionGroup(menuQuality);
            acMap_Quality1 = addActionCheck(menuQuality, tr("Resolution 1 (25 km)"), "", tr("Niveau de détail de la carte"));
            acMap_Quality2 = addActionCheck(menuQuality, tr("Resolution 2 (5 km)"), "", tr("Niveau de détail de la carte"));
            acMap_Quality3 = addActionCheck(menuQuality, tr("Resolution 3 (1 km)"), "", tr("Niveau de détail de la carte"));
            acMap_Quality4 = addActionCheck(menuQuality, tr("Resolution 4 (200 m)"), "", tr("Niveau de détail de la carte"));
            acMap_Quality5 = addActionCheck(menuQuality, tr("Resolution 5 (100 m)"), "", tr("Niveau de détail de la carte"));
            acMap_GroupQuality->addAction(acMap_Quality1);
            acMap_GroupQuality->addAction(acMap_Quality2);
            acMap_GroupQuality->addAction(acMap_Quality3);
            acMap_GroupQuality->addAction(acMap_Quality4);
            acMap_GroupQuality->addAction(acMap_Quality5);
		menuMap->addMenu(menuQuality);

		QMenu *menuProjection = new QMenu(tr("Projection"));
        acMap_GroupProjection = new QActionGroup(menuProjection);
            acMap_PROJ_ZYGRIB = addActionCheck(menuProjection, tr("ZyGrib"), "", "");
            acMap_PROJ_MERCATOR = addActionCheck(menuProjection, tr("Mercator"), "", "");
            acMap_PROJ_MILLER = addActionCheck(menuProjection, tr("Miller"), "", "");
            acMap_PROJ_CENTRAL_CYL = addActionCheck(menuProjection, tr("Central Cylindric"), "", "");
            acMap_PROJ_EQU_CYL = addActionCheck(menuProjection, tr("Equal cylindric"), "", "");
            acMap_GroupProjection->addAction(acMap_PROJ_ZYGRIB);
            acMap_GroupProjection->addAction(acMap_PROJ_MERCATOR);
            acMap_GroupProjection->addAction(acMap_PROJ_MILLER);
            acMap_GroupProjection->addAction(acMap_PROJ_CENTRAL_CYL);
            acMap_GroupProjection->addAction(acMap_PROJ_EQU_CYL);
		menuMap->addMenu(menuProjection);

	menuMap->addSeparator();
        acMap_Orthodromie = addActionCheck(menuMap, tr("Great circle distance"), "", "");
        acMap_LonLatGrid = addActionCheck(menuMap, tr("Longitudes-latitudes grid"), "", "");

     menuMap->addSeparator();
        acMap_CountriesBorders = addActionCheck(menuMap, tr("Boundaries"), "", tr("Show boundaries"));
        acMap_Rivers = addActionCheck(menuMap, tr("Rivers"), "", tr("Show rivers"));
        acMap_CountriesNames = addActionCheck(menuMap, tr("Countries names"), "", tr("Display countries names"));

        QMenu *menuCitiesNames = new QMenu(tr("Cities names"));
        acMap_GroupCitiesNames = new QActionGroup(menuMap);
            acMap_CitiesNames0 = addActionCheck(menuCitiesNames, tr("None"), "", "");
            acMap_CitiesNames1 = addActionCheck(menuCitiesNames, tr("Level 1")+" (>= 1000000)", "", "");
            acMap_CitiesNames2 = addActionCheck(menuCitiesNames, tr("Level 2")+" (>= 100000)", "", "");
            acMap_CitiesNames3 = addActionCheck(menuCitiesNames, tr("Level 3")+" (>= 10000)", "", "");
            acMap_CitiesNames4 = addActionCheck(menuCitiesNames, tr("Level 4")+" (>= 1000)", "", "");
            acMap_CitiesNames5 = addActionCheck(menuCitiesNames, tr("Level 5")+" (>= 0)", "", "");
            acMap_GroupCitiesNames->addAction(acMap_CitiesNames0);
            acMap_GroupCitiesNames->addAction(acMap_CitiesNames1);
            acMap_GroupCitiesNames->addAction(acMap_CitiesNames2);
            acMap_GroupCitiesNames->addAction(acMap_CitiesNames3);
            acMap_GroupCitiesNames->addAction(acMap_CitiesNames4);
            acMap_GroupCitiesNames->addAction(acMap_CitiesNames5);
            menuMap->addMenu(menuCitiesNames);
        acMap_FindCity = addAction (menuMap, tr("Find a city..."), "", "");
        acMap_ShowPOIs = addActionCheck(menuMap, tr("Point of interest"), tr("Ctrl+N"), tr("Display Points of interest"));

        menuMap->addSeparator();
        acMap_Zoom_In = addAction(menuMap,
        				tr("Increase map scale"), tr("+"),
                        tr("Increase map scale"), Util::pathImg("viewmag+.png"));
        acMap_Zoom_Out = addAction(menuMap,
        				tr("Reduce map scale"), tr("-"),
                        tr("Reduce map scale"), Util::pathImg("viewmag-.png"));
        acMap_Zoom_Sel = addAction(menuMap,
                        tr("Zoom (selected zone or Grib file)"), tr("Ctrl+Z"),
                        tr("Zoom on the selected zone or on the Grib file area"),
                        Util::pathImg("viewmagfit.png"));
        acMap_Zoom_All = addAction(menuMap,
        				tr("Show whole map"), tr("Ctrl+M"),
                        tr("Show whole map"), Util::pathImg("viewmag1.png"));
        menuMap->addSeparator();
        acMap_Go_Left = addAction(menuMap,
        				tr("Left"), tr("LEFT"),
                        tr("Move"), Util::pathImg("back.png"));
        acMap_Go_Right = addAction(menuMap,
        				tr("Right"), tr("RIGHT"),
                        tr("Move"), Util::pathImg("forward.png"));
        acMap_Go_Up   = addAction(menuMap,
        				tr("Top"), tr("UP"),
                        tr("Move"), Util::pathImg("up.png"));
        acMap_Go_Down = addAction(menuMap,
        				tr("Down"), tr("DOWN"),
                        tr("Move"), Util::pathImg("down.png"));

    addMenu(menuMap);

    //-------------------------------------
    menuOptions = new QMenu(tr("Options"));
        acOptions_Proxy = addAction(menuOptions, tr("Internet parameters"),"","","");
        acOptions_AngleConverter = addAction(menuOptions,
        				tr("Angle converter"), "", "","");
        acOptions_DateChooser = addActionCheck(menuOptions, 
						tr("Date selector"), "", "");
        acOptions_Units = addAction(menuOptions,
        				tr("Units"), tr("Ctrl+U"), "","");
        acOptions_Fonts = addAction(menuOptions,
        				tr("Fonts"), tr("Ctrl+E"), "","");
        acOptions_GraphicsParams = addAction(menuOptions,
						tr("Graphical parameters"), tr("Ctrl+G"), "","");

		QString lang = Util::getSetting("appLanguage", "").toString();
		QString flagIconName = (lang == "") ? "" : Util::pathImg("drapeau_")+lang+".png";
        acOptions_Language = addAction(menuOptions,
						tr("Language"), tr("Language"), "",flagIconName);
    addMenu(menuOptions);

    //-------------------------------------
    menuHelp = new QMenu(tr("Help"));
        acHelp_Help = addAction(menuHelp,
        				tr("Help"), tr("Ctrl+H"),
        				"",Util::pathImg("help.png"));
        acHelp_APropos = addAction(menuHelp, tr("About zyGrib"),"","","");
        acHelp_AProposQT = addAction(menuHelp, tr("About QT"),"","","");
    addMenu(menuHelp);

    //-------------------------------------
    // Autres objets de l'interface
    //-------------------------------------
    acDatesGrib_prev = addAction( NULL,
            tr("Last forecast [page up]"),tr("PgUp"),"",Util::pathImg("1leftarrow.png"));
    acDatesGrib_next = addAction( NULL,
            tr("Next forecast [page down]"),tr("PgDown"),"",Util::pathImg("1rightarrow.png"));

    cbDatesGrib = new QComboBox ();
    cbDatesGrib->setSizeAdjustPolicy (QComboBox::AdjustToContents);
    cbDatesGrib->addItem("-------------------------");
    
	cbDatesGrib->setEnabled (false);
	acDatesGrib_prev->setEnabled (true);
	acDatesGrib_next->setEnabled (true);

	updateFonts();
}

//---------------------------------------------------------
void MenuBar::updateFonts ()
{
	cbDatesGrib->setFont (Font::getFont(FONT_ComboBox));
	
	QFont ft = Font::getFont(FONT_MenuBar);
	this->setFont(ft);
	QList<QAction *> lsactions = this->findChildren<QAction *>();
	for (int i = 0; i < lsactions.size(); ++i) {
		lsactions.at(i)->setFont(ft);
	}
	
}


//---------------------------------------------------------
// Menu popup : bouton droit de la souris
//---------------------------------------------------------
QMenu * MenuBar::createPopupBtRight(QWidget *parent)
{
	QMenu *popup = new QMenu(parent);

	ac_OpenMeteotable = addAction(popup, tr("Meteotable"),"","","");
	ac_CreatePOI = addAction(popup, tr("Mark Point Of Interest"),"","","");
	
	// added by Tim Holtschneider, 05.2010
 	ac_OpenCurveDrawer = addAction(popup, tr("Plot Data"),"","","");

	return popup;
}

//===================================================================================
QAction* MenuBar::addAction(QMenu *menu,
                    QString title, QString shortcut, QString statustip,
                    QString iconFileName)
{
    QAction *action;
    action = new QAction(title, menu);
    action->setShortcut  (shortcut);
    action->setShortcutContext (Qt::ApplicationShortcut);
    action->setStatusTip (statustip);
    if (iconFileName != "") {
        action->setIcon(QIcon(iconFileName));
		action->setIconVisibleInMenu(true);
	}
    if (menu != NULL)
        menu->addAction(action);
    return action;
}
//-------------------------------------------------
QAction* MenuBar::addActionCheck(QMenu *menu,
                    QString title, QString shortcut, QString statustip,
                    QString iconFileName)
{
    QAction *action;
    action = addAction(menu, title, shortcut, statustip, iconFileName);
    action->setCheckable  (true);
    return action;
}

//-------------------------------------------------
void MenuBar::setProjection(int idproj)
{
	switch (idproj)
	{
        case Projection::PROJ_MERCATOR :
    		acMap_PROJ_MERCATOR->setChecked(true);  break;
        case Projection::PROJ_MILLER :
    		acMap_PROJ_MILLER->setChecked(true);    break;
        case Projection::PROJ_CENTRAL_CYL :
    		acMap_PROJ_CENTRAL_CYL->setChecked(true); break;
        case Projection::PROJ_EQU_CYL :
    		acMap_PROJ_EQU_CYL->setChecked(true);   break;
        case Projection::PROJ_ZYGRIB :
		    acMap_PROJ_ZYGRIB->setChecked(true);    break;
	}
}

//-------------------------------------------------
void MenuBar::setQuality(int q) {
    switch (q) {
        case 0: acMap_Quality1->setChecked(true); break;
        case 1: acMap_Quality2->setChecked(true); break;
        case 2: acMap_Quality3->setChecked(true); break;
        case 3: acMap_Quality4->setChecked(true); break;
        case 4: acMap_Quality5->setChecked(true); break;
    }
}
//-------------------------------------------------
void MenuBar::setIsobarsStep(int step) {
    switch (step) {
        case 1: acView_IsobarsStep1->setChecked(true); break;
        case 2: acView_IsobarsStep2->setChecked(true); break;
        case 3: acView_IsobarsStep3->setChecked(true); break;
        case 4: acView_IsobarsStep4->setChecked(true); break;
        case 5: acView_IsobarsStep5->setChecked(true); break;
        case 6: acView_IsobarsStep6->setChecked(true); break;
        case 8: acView_IsobarsStep8->setChecked(true); break;
        case 10: acView_IsobarsStep10->setChecked(true); break;
    }
}
//-------------------------------------------------
void MenuBar::setIsotherms0Step(int step) {
    switch (step) {
        case 10: acView_Isotherms0Step10->setChecked(true); break;
        case 20: acView_Isotherms0Step20->setChecked(true); break;
        case 50: acView_Isotherms0Step50->setChecked(true); break;
        case 100: acView_Isotherms0Step100->setChecked(true); break;
        case 200: acView_Isotherms0Step200->setChecked(true); break;
        case 500: acView_Isotherms0Step500->setChecked(true); break;
        case 1000: acView_Isotherms0Step1000->setChecked(true); break;
    }
}
//-------------------------------------------------
void MenuBar::setIsotherms2mStep(int step) {
    switch (step) {
        case 1: acView_Isotherms2mStep1->setChecked(true); break;
        case 2: acView_Isotherms2mStep2->setChecked(true); break;
        case 5: acView_Isotherms2mStep5->setChecked(true); break;
        case 10: acView_Isotherms2mStep10->setChecked(true); break;
    }
}
//-------------------------------------------------
void MenuBar::setCitiesNamesLevel(int level) {
    switch (level) {
        case 0: acMap_CitiesNames0->setChecked(true); break;
        case 1: acMap_CitiesNames1->setChecked(true); break;
        case 2: acMap_CitiesNames2->setChecked(true); break;
        case 3: acMap_CitiesNames3->setChecked(true); break;
        case 4: acMap_CitiesNames4->setChecked(true); break;
        case 5: acMap_CitiesNames5->setChecked(true); break;
    }
}

//------------------------------------------------------------
// Génère la liste des dates des Records du fichier GRIB
void MenuBar::updateListeDates(std::set<time_t> *setDates, time_t currentDate)
{
    listGribDates.clear();
    // Construit un vector à partir du set (plus pratique)
    std::set<time_t>::iterator its;
    for (its=setDates->begin(); its!=setDates->end(); its++) {
        listGribDates.push_back(*its);
    }

    // Met à jour les item du QComboBox
    while (cbDatesGrib->count() > 0) {
        cbDatesGrib->removeItem(0);
    }
    std::vector<time_t>::iterator it;
    for (it=listGribDates.begin(); it!=listGribDates.end(); it++) {
        time_t tps = *it;
        QString str = Util::formatDateTimeLong(tps);
        //printf("%s\n", qPrintable(str));
        cbDatesGrib->addItem(str);
    }
	
	updateCurrentDate (currentDate);
}
//------------------------------------------------------------
time_t  MenuBar::getDateGribById(int id)
{
    if (listGribDates.size() > (uint)id)
        return listGribDates[id];
    else
        return (time_t)0;
}
//------------------------------------------------------------
void MenuBar::updateCurrentDate (time_t currentDate)
{
	acDatesGrib_prev->setEnabled (true);
	acDatesGrib_next->setEnabled (true);
	QString strCurrentDate = Util::formatDateTimeLong (currentDate);
	int id = cbDatesGrib->findText (strCurrentDate);
	if (id >= 0) {
		cbDatesGrib->setCurrentIndex (id);
		if (id == 0) {
			acDatesGrib_prev->setEnabled (false);
		}
		if (id == cbDatesGrib->count()-1) {
			acDatesGrib_next->setEnabled (false);
		}
	}
}









