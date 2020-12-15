/*
 * Stellarium
 * Copyright (C) 2008 Guillaume Chereau
 *
 * Stellarium N9 QML Gui
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

#ifndef _STELQMLSEARCH_HPP_
#define _STELQMLSEARCH_HPP_

#include <QObject>
#include <QMap>
#include <QHash>
#include "VecMath.hpp"


class StelQmlSearch : public QObject
{
    Q_OBJECT

public:
    StelQmlSearch();
    virtual ~StelQmlSearch();


public slots:

    void updateSearchResults(const QString& text, QStringList& matches);

    bool gotoObject(const QString& name);


private slots:

    //! Called when the current simbad query status changes
    //void onSimbadStatusChanged();

    //! Whether to use SIMBAD for searches or not.
    //void enableSimbadSearch(bool enable);


    //! Called when a SIMBAD server is selected in the list.
    //void selectSimbadServer(int index);

private:
    //class SimbadSearcher* simbadSearcher;
    //class SimbadLookupReply* simbadReply;
    //QMap<QString, Vec3d> simbadResults;

    QString substituteGreek(const QString& keyString);
    QString getGreekLetterByName(const QString& potentialGreekLetterName);
    QHash<QString, QString> greekLetters;


    //bool useSimbad;
    //! URL of the server used for SIMBAD queries.
    //QString simbadServerUrl;
    //void populateSimbadServerList();

    //! URL of the default SIMBAD server (Strasbourg).
    //static const char* DEF_SIMBAD_URL;
};

#endif

