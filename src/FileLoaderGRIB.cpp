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
#include <QTextStream>
#include <QDomDocument>
#include <QNetworkProxy>
#include <QMessageBox>

#include <cassert>

#include "FileLoaderGRIB.h"
#include "Util.h"
#include "Version.h"

//========================================================================
FileLoaderGRIB::FileLoaderGRIB (QNetworkAccessManager *manager, QWidget *parent)
			: FileLoader (manager)
{
	this->parent = parent;
    step = 0;
	downloadError = false;
	reply_step1 = NULL;
	reply_step2 = NULL;
	host = "www.zygrib.org";
	scriptpath = "/noaa/";
	scriptstock = "313O562/";
    zygriblog = "a07622b82b18524d2088c9b272bb3feeb0eb1737";
    zygribpwd = "61c9b2b17db77a27841bbeeabff923448b0f6388";
}
//-------------------------------------------------------------------------------
FileLoaderGRIB::~FileLoaderGRIB () 
{
	if (reply_step1) {
		reply_step1->deleteLater ();
		reply_step1 = NULL;
	}
	if (reply_step2) {
		reply_step2->deleteLater ();
		reply_step2 = NULL;
	}
}

//-------------------------------------------------------------------------------
void FileLoaderGRIB::stop () 
{
	if (reply_step1) {
		reply_step1->close ();
		downloadError = true;
	}
	if (reply_step2) {
		reply_step2->close ();
		downloadError = true;
	}
}

//-------------------------------------------------------------------------------
void FileLoaderGRIB::getGribFile(
        float x0, float y0, float x1, float y1,
        float resolution, int interval, int days,
        bool wind, bool pressure, bool rain,
        bool cloud, bool temp, bool humid, bool isotherm0,
		bool tempMin, bool tempMax, bool snowDepth,
		bool snowCateg, bool frzRainCateg,
		bool CAPEsfc, 
		bool altitudeData200,
		bool altitudeData300,
		bool altitudeData500,
		bool altitudeData700,
		bool altitudeData850,
		bool altitudeData925,
		bool cloudLayers,
		bool GUSTsfc,
		bool SUNSDsfc
	)
{
    QString page;
	step = 0;
    //----------------------------------------------------------------
    // Etape 1 : Demande la création du fichier Grib (nom en retour)
    //----------------------------------------------------------------
    QString parameters = "";
    if (wind) {
        parameters += "W;";
    }
    if (pressure) {
        parameters += "P;";
    }
    if (rain) {
        parameters += "R;";
    }
    if (cloud) {
        parameters += "C;";
    }
    if (temp) {
        parameters += "T;";
    }
    if (humid) {
        parameters += "H;";
    }
	if (isotherm0) {
		parameters += "I;";
    }    
    if (tempMin) {
        parameters += "m;";
    }
    if (tempMax) {
        parameters += "M;";
    }
    if (snowDepth) {
        parameters += "S;";
    }
    if (snowCateg) {
        parameters += "s;";
    }
    if (frzRainCateg) {
        parameters += "Z;";
    }
    if (CAPEsfc) {
        parameters += "c;";
    }
    if (GUSTsfc) {
        parameters += "G;";
    }
    if (SUNSDsfc) {
        parameters += "D;";
    }
	
    if (altitudeData200) parameters += "2;";
    if (altitudeData300) parameters += "3;";
    if (altitudeData500) parameters += "5;";
    if (altitudeData700) parameters += "7;";
    if (altitudeData850) parameters += "8;";
    if (altitudeData925) parameters += "9;";
    if (cloudLayers) parameters += "L;";
	
    if (Util::getSetting("downloadFnmocWW3_sig", false).toBool())
		parameters += "w3sh;";
    if (Util::getSetting("downloadFnmocWW3_max", false).toBool())
		parameters += "w3mx;"; 
    if (Util::getSetting("downloadFnmocWW3_swl", false).toBool())
		parameters += "w3sw;";
    if (Util::getSetting("downloadFnmocWW3_wnd", false).toBool())
		parameters += "w3wn;"; 
    if (Util::getSetting("downloadFnmocWW3_wcap", false).toBool())
		parameters += "w3wc;";
    if (Util::getSetting("downloadFnmocWW3_prim", false).toBool())
		parameters += "w3pr;"; 
    if (Util::getSetting("downloadFnmocWW3_scdy", false).toBool())
		parameters += "w3sc;"; 
	if (parameters.contains("w3")) {
		DataCenterModel waveDataModel = (DataCenterModel)(Util::getSetting("downloadFnmocWW3_DataModel", FNMOC_WW3_MED).toInt());
		if (waveDataModel == FNMOC_WW3_MED)
			parameters += "w3med;"; 
		else if (waveDataModel == FNMOC_WW3_GLB)
			parameters += "w3glb;"; 
		else if (waveDataModel == NOAA_NCEP_WW3)
			parameters += "w3ncp;"; 
	}
    if (parameters != "")
    {
        step = 1;
        emit signalGribSendMessage(
        		tr("Make file on server... Please wait..."));
        emit signalGribReadProgress(step, 0, 0);
		
		QString phpfilename;
		phpfilename = scriptpath+"getzygribfile3.php?";
		QString now = QTime::currentTime().toString("HHmmss");
        QTextStream(&page) << phpfilename
                           << "but=prepfile"
                           << "&la1=" << floor(y0)
                           << "&la2=" << ceil(y1)
                           << "&lo1=" << floor(x0)
                           << "&lo2=" << ceil(x1)
                           << "&res=" << resolution
                           << "&hrs=" << interval
                           << "&jrs=" << days
                           << "&par=" << parameters
                           << "&l=" << zygriblog
                           << "&m=" << zygribpwd
						   << "&tm=" << now
                           << "&client=" << Version::getCompleteName() 
                           ;
		bool stricthttp = Util::getSetting ("strictHttpDownload", false).toBool(); 
		if (stricthttp) {
			QString zl = Util::encode(Util::decode(Util::getSetting("zyGribForumUserName", "").toString()),now);
			QString zp = Util::encode(Util::decode(Util::getSetting("zyGribForumUserPassword", "").toString()),now);
			QTextStream(&page) << "&zl=" << zl << "&zp=" << zp << "&md=h";
		}
		QNetworkRequest request;
		request.setUrl (QUrl("http://"+host+page) );
		if (! stricthttp)
			request.setRawHeader ("User-Agent", qPrintable(Version::getAppName()+"/"+Version::getVersion()) );
		Util::validArea (request,x0,y0,x1,y1);
		reply_step1 = networkManager->get (request);
		connect (reply_step1, SIGNAL(downloadProgress (qint64,qint64)), 
				 this, SLOT(downloadProgress (qint64,qint64)));
		connect (reply_step1, SIGNAL(error(QNetworkReply::NetworkError)),
				 this, SLOT(slotNetworkError (QNetworkReply::NetworkError)));
		connect (reply_step1, SIGNAL(finished()),
				 this, SLOT(slotFinished_step1 ()));
    }
}
//-------------------------------------------------------------------------------
void FileLoaderGRIB::slotNetworkError (QNetworkReply::NetworkError /*err*/)
{
	if (! downloadError) {
		if (sender() == reply_step1) {
// 		DBG("ERROR step 1");
			emit signalGribLoadError (reply_step1->errorString());
			downloadError = true;
		}
		else if (sender() == reply_step2) {
// 		DBG("ERROR step 2");
			emit signalGribLoadError (reply_step2->errorString());
			downloadError = true;
		}
	}
}
//-------------------------------------------------------------------------------
void FileLoaderGRIB::downloadProgress (qint64 done, qint64 total)
{
	if (downloadError) {
		step = 1000;
		return;
	}
	if (sender() == reply_step2) {
		emit signalGribReadProgress (step, done, total);
	}
}
//-------------------------------------------------------------------------------
void FileLoaderGRIB::slotFinished_step1 ()
{
// DBG("slotFinished_step1");	
	if (!downloadError) {
		//-------------------------------------------
		// Retour de l'étape 1 : préparation du fichier
		//-------------------------------------------
		QByteArray data = reply_step1->readAll ();
		
		QString strbuf (data);
		QStringList lsbuf = strbuf.split("\n");

		QString status;
		for (int i=0; i < lsbuf.size(); i++)
		{
			QStringList lsval = lsbuf.at(i).split(":");
			if (lsval.size() >= 2) {
				if (lsval.at(0) == "status")
					status = lsval.at(1);
				else if (lsval.at(0) == "file") 
					fileName = QString(lsval.at(1)).replace(".grb","%20");
				else if (lsval.at(0) == "size")
					fileSize = lsval.at(1).toInt();
				else if (lsval.at(0) == "checksum")
					checkSumSHA1 = lsval.at(1);
				else if (lsval.at(0) == "message") {
					QString m = QUrl::fromPercentEncoding (lsval.at(1).toUtf8());
					QMessageBox::warning (parent, tr("Information"), m);
				}
			}
		}
		//-------------------------------------------------------------
		// Lance l'étape 2 : Demande le contenu du fichier Grib
		//-------------------------------------------------------------
		if (status == "ok") {
			QString page;
            step = 2;
            QString s;
            s = tr("Total size : ") + QString("%1 ko").arg(fileSize/1024, 0);
            emit signalGribSendMessage(s);
            QTextStream(&page) << scriptpath
			<<"313O562/"<<fileName;
            emit signalGribStartLoadData();            
			QNetworkRequest request;
			request.setUrl (QUrl("http://"+host+page) );
			reply_step2 = networkManager->get (request);
			connect (reply_step2, SIGNAL(downloadProgress (qint64,qint64)), 
					 this, SLOT(downloadProgress (qint64,qint64)));
			connect (reply_step2, SIGNAL(error(QNetworkReply::NetworkError)),
					 this, SLOT(slotNetworkError (QNetworkReply::NetworkError)));
			connect (reply_step2, SIGNAL(finished()),
					this, SLOT(slotFinished_step2 ()));
		}
		else {
			emit signalGribLoadError (status);
			downloadError = true;
		}
	}
}

//-------------------------------------------------------------------------------
void FileLoaderGRIB::slotFinished_step2 ()
{
// DBG("slotFinished_step2");		
	if (!downloadError) {
		//--------------------------------------------------
		// Reçu le contenu du fichier Grib
		//--------------------------------------------------
		step = 1000;
		
		arrayContent = reply_step2->readAll ();
		if (arrayContent.size() == 0) {
			emit signalGribLoadError (tr("Empty file."));
			return;
		}
		//--------------------------------------------------
		// Vérifie le checksum
		//--------------------------------------------------
		emit signalGribSendMessage(tr("CheckSum control"));
		if (Util::sha1 (arrayContent) == checkSumSHA1)
		{
			//--------------------------------------------------
			// Signale la fin du téléchargement
			//--------------------------------------------------
			emit signalGribSendMessage(tr("Finish")
							+ QString(" %1 ko").arg(arrayContent.size()/1024));
			emit signalGribDataReceived(&arrayContent, fileName.replace("%20",".grb"));
		}
		else {
			emit signalGribLoadError (tr("Bad checksum."));
		}
	}
}
