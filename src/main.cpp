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

#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QTime>
#include <QMessageBox>
#include <QImageWriter>

#include "MainWindow.h"
#include "Settings.h"
#include "Version.h"
#include "Font.h"
#include "Util.h"
#include "DataMeteoAbstract.h"
#include "ColorScale.h"

//===========================================================
int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
	qsrand(QTime::currentTime().msec());
	
    QTextCodec::setCodecForTr(QTextCodec::codecForName("utf8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf8"));

	//----------------------------------------------------------
    // Find application settings files
    //----------------------------------------------------------
	Settings::initializeSettingsDir();
	Settings::initializeGribFilesDir();
    //printf("settings: %s\n", qPrintable( Settings::getSettingsDir()) );
	//QString path = Util::getSetting("gribFilePath", "").toString();
    //printf("Grib files dir: %s\n", qPrintable(path) );

	Util::setSetting("AppVersion", Version::getCompleteName());
    //----------------------------------------------------------
    // Fonts
    //----------------------------------------------------------
	Font::loadAllFonts();

    //----------------------------------------------------------
/*	double pr, h;
	pr = 925;
	h = DataRecordAbstract::computeGeopotentialAltitude (pr);
	printf ("%g %g\n", pr,h);
	pr = 300;
	h = DataRecordAbstract::computeGeopotentialAltitude (pr);
	printf ("%g %g\n", pr,h);
	pr = 500;
	h = DataRecordAbstract::computeGeopotentialAltitude (pr);
	printf ("%g %g\n", pr,h);*/
	//----------------------------------------------------------
    // Images formats
    //----------------------------------------------------------
/*	QList<QByteArray> list = QImageWriter::supportedImageFormats ();
	for (int i = 0; i < list.size(); ++i) {
		DBGS (list.at(i).data());
	}	*/
	//----------------------------------------------------------
    // Load language
    //----------------------------------------------------------
    QTranslator trZygrib;
    QTranslator trSystem;

    // A. Degwerth [Cassidian]: added new parsing of command line options
    // added new Command line option "-Ini:<key>=<value>" to make it possible to replace
    // ini-entries via the command line.
    // e.g. zygrip.exe -Ini:appLanguage=ar starts zygrib always with the arabic UI
    bool openLatestGribFile = true;

    //--
    // check if we have commandline arguments which should replace some INI settings
    //--
    QStringList cmdLineArgs = app.arguments();
    
    foreach(QString str, cmdLineArgs)
    {
		//qDebug() << "CommandLineArg: " << str;
		if (str.startsWith("-Ini:", Qt::CaseInsensitive))
		{
			// replace all "
			str.remove("\"");
			str.remove("-Ini:", Qt::CaseInsensitive);

			QStringList kv = str.split("=");
			if (kv.size() == 2)
			{
				// put the values into the ini
				Util::setSetting(kv[0].trimmed(),kv[1].trimmed());
				//qDebug() << "Overwrite INI:" << kv[0].trimmed() << "=" << kv[1].trimmed();
			}
		}
		else if (str == "-n")
		{
			openLatestGribFile = false;
		}
    }

    QString lang = Util::getSetting("appLanguage", "").toString();
    if (lang == "") {
		//----------------------------------------------------------
		// first call of zyGrib : choice language
		//----------------------------------------------------------
		DialogChooseLang langChooser (NULL, "");
		langChooser.exec ();
        lang = langChooser.getLanguage();
        Util::setSetting("appLanguage", lang);
    }

    //-----------------------------------------------
    // Set language
    //-----------------------------------------------
    if (lang == "fr") {
        QLocale::setDefault(QLocale("fr_FR"));
        trSystem.load( QString("qt_fr"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else if (lang == "de") {
        QLocale::setDefault(QLocale("de_DE"));
        trSystem.load( QString("qt_de"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else if (lang == "ru") {
        QLocale::setDefault(QLocale("ru_RU"));
        trSystem.load( QString("qt_ru"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else if (lang == "pl") {
        QLocale::setDefault(QLocale("pl_PL"));
        trSystem.load( QString("qt_pl"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else if (lang == "pt") {
        QLocale::setDefault(QLocale("pt_PT"));
        trSystem.load( QString("qt_pt"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else if (lang == "es") {
        QLocale::setDefault(QLocale("es_ES"));
        trSystem.load( QString("qt_es"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else if (lang == "it") {
        QLocale::setDefault(QLocale("it_IT"));
        trSystem.load( QString("qt_it"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else if (lang == "nl") {
        QLocale::setDefault(QLocale("nl_NL"));
        trSystem.load( QString("qt_nl"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else if (lang == "cz") {
        QLocale::setDefault(QLocale("cz_CZ"));
        trSystem.load( QString("qt_cz"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    // A. Degwerth [Cassidian] added Arabic language support
    else if (lang == "ar") {
        QLocale::setDefault(QLocale("ar_AR"));
        trSystem.load( QString("qt_ar"), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        trZygrib.load( Util::pathTr(lang));
        app.installTranslator(&trZygrib);
        app.installTranslator(&trSystem);
    }
    else { 	// e=English = default
        QLocale::setDefault(QLocale("en_US"));
    }
    //-----------------------------------------------
	// Set layout orientation
    //-----------------------------------------------
	if (lang == "ar") {
		app.setLayoutDirection (Qt::RightToLeft);
	}
	else {
		app.setLayoutDirection (Qt::LeftToRight);
	}

    //====================================================
    // Open main window
    //====================================================
	bool withmblue = true;
// 	if (argc >= 2 && strcmp("-m",argv[1])==0)
// 		withmblue = true;

	MainWindow *win = new MainWindow (800, 600, withmblue);
	assert (win);
	
	Util::setApplicationProxy ();
	
    win->show();

	//-------------------------------------------------------------------
    // Open file (command line parameter or last open)
    //-------------------------------------------------------------------
    // A. Degwerth [Cassidian] short modifications because the command line is parsed above
	if (openLatestGribFile) {
		QString filename = "";

		if (cmdLineArgs.size() > 1) {
			// find the last argument without "-"
			for(int i = 1; i < cmdLineArgs.size(); i++)
			{
				QString arg = cmdLineArgs[i];
				//qDebug() << "CommandLineArg: " << str;
				if (!arg.startsWith("-"))
				{
					filename = arg;
				}
			}
			
			if(! QFile::exists(filename)) {
				filename = "";
			}
		}
		
		if (filename == "") {
			filename = Util::getSetting("gribFileName", "").toString();
		}
		
		if (QFile::exists(filename))
		{
			win->openMeteoDataFile (filename, false);
		}
	}
	
    //====================================================
	return app.exec();
}
