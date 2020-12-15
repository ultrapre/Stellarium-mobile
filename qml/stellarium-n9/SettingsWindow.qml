/*
 * StellariumN9 QML Gui
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

import QtQuick 1.1
import com.nokia.meego 1.0

PageStackWindow {
    id: appWindow

    opacity: hudSettingsPage.swBrightness
    showStatusBar: hudSettingsPage.swShowStatus


    initialPage: mainPage
    //initialPage: aboutPage


    MainSettingsPage { id: mainPage }
    SkyPage { id: skyPage }
    ObjectSearchPage { id: objectSearchPage }
    MarkingsPage { id: markingsPage }
    SavePage { id: savePage }
    LocationPage { id: locationPage }
    LocationListPage { id: locationListPage }
    LandscapePage { id: landscapePage }
    DateTimePage { id: dateTimePage }
    SkyCulturePage { id: skyCulturePage }
    AboutPage { id: aboutPage }
    HudSettingsPage { id: hudSettingsPage }

    Component.onCompleted: { theme.inverted = true }

    signal backToSkyView()

    ToolBarLayout {
        id: commonTools
        visible: true
        ToolIcon {
                platformIconId: "toolbar-back"
                anchors.left: (parent === undefined) ? undefined : parent.left
                onClicked: {
                    if (pageStack.depth == 1)
                        appWindow.backToSkyView()
                    else
                         pageStack.pop()
                }
            }
        ToolIcon {
            platformIconId: "toolbar-view-menu"
            anchors.right: (parent === undefined) ? undefined : parent.right
            onClicked: appWindow.backToSkyView()
        }



    }
}


