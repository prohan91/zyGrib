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

#include "DataMeteoAbstract.h"

#include <cstdio>
#include <cmath>


//----------------------------------------------------------------------
double DataRecordAbstract::computeThetaE (double T, // temperature (K)
					  double P, // pressure (hPa)
					  double SH // specific humidity (kg/kg)
					)
{
	if (T==GRIB_NOTDEF || P==GRIB_NOTDEF || SH==GRIB_NOTDEF
		|| SH==1.0 || P==0.0
	) {
		return GRIB_NOTDEF;
	}
	
	double mr = 1000.0 * SH/(1.0-SH);	// mixing ratio (g/kg)
	double Cp = 1004.0;
	double Rd = 287.0;
	double P0 = 1000.0;

	// source: http://en.wikipedia.org/wiki/Latent_heat
	// Lv = (2404.83 kJ/kg {at 40 °C} to 2601.83 kJ/kg {at −40 °C})
	// => cubic interpolation between -40 and 40, else line y=ax+b
	double Lv;
	double a = (2404.83-2601.83)/80.0;
	double b = 2404.83-40.0*a;
	double tc = T-273.15;
	if (tc < -40 || tc>40)
		Lv = a*tc + b;
	else
		Lv = -0.0000614342*tc*tc*tc + 0.00158927*tc*tc - 2.36418*tc + 2500.79;	
//printf("T=%f  tc=%f   Lv=%f  cub=%f\n", T, tc, Lv,-0.0000614342*tc*tc*tc + 0.00158927*tc*tc - 2.36418*tc + 2500.79);

	double thetae;	// θe
	thetae = (T + Lv/Cp*mr) * pow(P0/P, Rd/Cp);
	return thetae;
}

//----------------------------------------------------------------------
double DataRecordAbstract::dewpointMagnusTetens (double tempCelcius, double humidRel)
{
	double dewpoint = GRIB_NOTDEF;
	if (tempCelcius != GRIB_NOTDEF && humidRel != GRIB_NOTDEF)
	{
		double a = 17.27;
		double b = 237.7;
		double t  = tempCelcius-273.15;
		double rh = humidRel/100.0;
		double bt = b+t;
		if (rh>0 && bt!=0) {
			double alpha = a*t/bt + log(rh);
			double aa = a-alpha;
			if (aa != 0) {
				dewpoint = b*alpha/aa;
				dewpoint += 273.15;
			}
		}
	}
	return dewpoint;
}		
//----------------------------------------------------------------------
double DataRecordAbstract::computeGeopotentialAltitude (
					double Phpa  // pressure (hPa)
				)
{
	double L=-6.5e-3;
	double Ra=287.05;
	double Pb=101325;
	double Tb=288.15;
	double gb=9.807;
	double Zb=0;
	double Ps = Phpa*100;
	return ((Tb+L*Zb) * pow(Pb/Ps, L*Ra/gb) - Tb) / L;
}

//----------------------------------------------------------------------
/** Compute a timestamp in the UTC timezone.
*/
time_t DataRecordAbstract::UTC_mktime (
	int year,int month,int day,int hour,int min,int sec) 
{
	if (year<1970 || month<1 || month>12 || day<1
			|| hour<0 || min<0 || sec<0)
		return -1;
	time_t r = 0;
	// TODO : optimize (precomputed data)
	for (int y=1970; y<year; y++) {
		r += 365*24*3600;
		if (isleapyear(y))
			r += 24*3600;
	}
	if (month > 1) {
		for (int m=1; m<month; m++) {
			if (m==2) {
				r += 28*24*3600;
				if (isleapyear(year))
					r += 24*3600;
			}
			else if (m==1||m==3||m==5||m==7||m==8||m==10||m==12) {
				r += 31*24*3600;
			}
			else {
				r += 30*24*3600;
			}
		}
	}
	r += (day-1)*24*3600;
	r += hour*3600;
	r += min*60;
	r += sec;
	return r;
}
