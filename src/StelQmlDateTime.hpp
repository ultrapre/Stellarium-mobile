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


#ifndef STELQMLDATETIME_HPP
#define STELQMLDATETIME_HPP

#include <QObject>

class StelQmlDateTime : public QObject
{
    Q_OBJECT
public:

    StelQmlDateTime();
    double newJd();
    void init(QObject* dateTimePage);
    bool valid(int y, int m, int d, int h, int min, int s);

public slots:

    void setDateTime(double newJd);

private slots:

    void dateChanged(int y, int m, int d);
    void timeChanged(int h, int m, int s);

    void yearChanged(int ny);
    void monthChanged(int nm);
    void dayChanged(int nd);
    void hourChanged(int nh);
    void minuteChanged(int nm);
    void secondChanged(int ns);

private:

    void updateDateTimePage();

    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

    QObject* dateTimePage;

    
};

#endif // STELQMLDATETIME_HPP
