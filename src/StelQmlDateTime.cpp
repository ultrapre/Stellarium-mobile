/*
 * Stellarium
 * Copyright (C) 2008 Nigel Kerr
 * Copyright (C) 2012 Timothy Reaves
 * Copyright (C) 2012 Marko Srebre
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.
*/

#include "StelQmlDateTime.hpp"
#include "StelApp.hpp"
#include "StelCore.hpp"
#include "StelLocaleMgr.hpp"

#include <QDebug>

StelQmlDateTime::StelQmlDateTime() :
  year(0),
  month(0),
  day(0),
  hour(0),
  minute(0),
  second(0)
{
}


void StelQmlDateTime::init(QObject* _dateTimePage)
{
    dateTimePage = _dateTimePage;

    double jd = StelApp::getInstance().getCore()->getJDay();

    // UTC -> local tz
    setDateTime(jd + (StelApp::getInstance().getLocaleMgr().getGMTShift(jd)/24.0));


    QObject::connect(dateTimePage, SIGNAL(dateChanged(int, int, int)), this, SLOT(dateChanged(int, int, int)));
    QObject::connect(dateTimePage, SIGNAL(timeChanged(int, int, int)), this, SLOT(timeChanged(int, int, int)));

}

//! take in values, adjust for calendrical correctness if needed, and push to
//! the widgets and signals
bool StelQmlDateTime::valid(int y, int m, int d, int h, int min, int s)
{
    int dy, dm, dd, dh, dmin, ds;

    if (!StelUtils::changeDateTimeForRollover(y, m, d, h, min, s, &dy, &dm, &dd, &dh, &dmin, &ds)) {
        dy = y;
        dm = m;
        dd = d;
        dh = h;
        dmin = min;
        ds = s;
    }

    year = dy;
    month = dm;
    day = dd;
    hour = dh;
    minute = dmin;
    second = ds;

    updateDateTimePage();

    StelApp::getInstance().getCore()->setJDay(newJd());
    return true;
}


void StelQmlDateTime::timeChanged(int newhour, int newminute, int newsecond)
{
    if (hour != newhour || minute != newminute || second != newsecond)
    {
        valid(year, month, day, newhour, newminute, newsecond );
    }
}
void StelQmlDateTime::dateChanged(int newyear, int newmonth, int newday)
{
    if (year != newyear || month != newmonth || day != newday)
    {
        valid( newyear, newmonth, newday, hour, minute, second );
    }
}

void StelQmlDateTime::yearChanged(int newyear)
{
  if ( year != newyear ) {
    valid( newyear, month, day, hour, minute, second );
  }
}
void StelQmlDateTime::monthChanged(int newmonth)
{
  if ( month != newmonth ) {
    valid( year, newmonth, day, hour, minute, second );
  }
}
void StelQmlDateTime::dayChanged(int newday)
{
  if ( day != newday ) {
    valid( year, month, newday, hour, minute, second );
  }
}
void StelQmlDateTime::hourChanged(int newhour)
{
  if ( hour != newhour ) {
    valid( year, month, day, newhour, minute, second );
  }
}
void StelQmlDateTime::minuteChanged(int newminute)
{
  if ( minute != newminute ) {
    valid( year, month, day, hour, newminute, second );
  }
}
void StelQmlDateTime::secondChanged(int newsecond)
{
  if ( second != newsecond ) {
    valid( year, month, day, hour, minute, newsecond );
  }
}

double StelQmlDateTime::newJd()
{
  double jd;
  StelUtils::getJDFromDate(&jd,year, month, day, hour, minute, second);
  jd -= (StelApp::getInstance().getLocaleMgr().getGMTShift(jd)/24.0); // local tz -> UTC
  return jd;
}

void StelQmlDateTime::updateDateTimePage()
{
    if (!dateTimePage)
        return;

    dateTimePage->setProperty("year", year);
    dateTimePage->setProperty("month", month);
    dateTimePage->setProperty("day", day);
    dateTimePage->setProperty("hour", hour);
    dateTimePage->setProperty("minute", minute);
    dateTimePage->setProperty("second", second);
}

void StelQmlDateTime::setDateTime(double newJd)
{
    newJd += (StelApp::getInstance().getLocaleMgr().getGMTShift(newJd)/24.0); // UTC -> local tz
    StelUtils::getDateFromJulianDay(newJd, &year, &month, &day);
    StelUtils::getTimeFromJulianDay(newJd, &hour, &minute, &second);
    updateDateTimePage();
}

