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
import com.nokia.meego 1.1
import com.nokia.extras 1.1


Page {
    tools: commonTools

    id: mainPage

    ListView {

        id: view
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        clip: true
        model: itemModel


    }

    VisualItemModel {
        id: itemModel


        HeaderRow {
            title: "Stellarium N9 " + qmlGui.version()

        }

        SeparatorRow {}

        SwitchRow {
            objectName: "FreeLook"
            title: "Free look"
            subtitle: "Rotate device to look around"
        }


        PageRow {
            title: "Search"
            subtitle: "Find objects"
            mouseArea.onClicked: { pageStack.push(objectSearchPage) }
        }

        PageRow {
            title: "Sky"
            subtitle: "Stars, Planets, Labels and Markers"
            mouseArea.onClicked: { pageStack.push(skyPage) }
        }

        PageRow {
            title: "Markings"
            subtitle: "Celestial sphere, constellations"
            mouseArea.onClicked: { pageStack.push(markingsPage) }
        }

        PageRow {
            title: "Location"
            subtitle: locationPage.name
            mouseArea.onClicked: { pageStack.push(locationPage) }
        }

        PageRow {
            title: "Landscapes"
            subtitle: landscapePage.landscapeName
            mouseArea.onClicked: { pageStack.push(landscapePage) }
        }

        PageRow {
            title: "Date and time"
            subtitle: dateTimePage.formatDate() + " " + dateTimePage.formatTime()
            mouseArea.onClicked: { pageStack.push(dateTimePage) }
        }

        PageRow {
            title: "Mount mode"
            subtitle: mountTypeSelectionDialog.model.get(mountTypeSelectionDialog.selectedIndex).name
            mouseArea.onClicked: { mountTypeSelectionDialog.open() }
        }

        PageRow {
            title: "Starlore"
            subtitle: skyCulturePage.skyCultureName
            mouseArea.onClicked: { pageStack.push(skyCulturePage) }
        }

        PageRow {
            title: "Viewing settings"
            subtitle: "HUD, night mode, screensaver"
            mouseArea.onClicked: { pageStack.push(hudSettingsPage) }
        }

        PageRow {
            title: "Save current view options"
            mouseArea.onClicked: { pageStack.push(savePage) }
        }

        PageRow {
            title: "About Stellarium N9"
            mouseArea.onClicked: { pageStack.push(aboutPage) }
        }



    }


    SelectionDialog {
        objectName: "MountTypeSelection"
        id: mountTypeSelectionDialog
        signal mountTypeChanged(int i)

        titleText: "Select mount mode:"
        model: ListModel {
            ListElement { name: "Azimuthal" }
            ListElement { name: "Equatorial" }
            ListElement { name: "Galactic" }
        }
        onSelectedIndexChanged: { mountTypeChanged(selectedIndex) }

    }


}





