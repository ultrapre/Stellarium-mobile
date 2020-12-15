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
import QtMobility.location 1.1

Page {

    id: locationPage
    objectName: "LocationPage"
    anchors.margins: UiConstants.DefaultMargin
    tools: commonTools

    property string terrainImage
    property double latitude
    property string latH
    property int latD
    property int latM
    property int latS

    property double longitude
    property string longH
    property int longD
    property int longM
    property int longS

    property string planet
    property string country
    property string name
    property double altitude

    property bool newLocation: false
    property bool canDeleteLocation: false

    property int spacing: 10


    signal addLocationToList()
    signal deleteLocation()

    signal locationChanged()

    //onNameChanged: { locationChanged() }

    function updateLocation(updateName)
    {
        if (!newLocation)
        {
            if (updateName)
                name = "New location"
            newLocation = true
        }
        locationChanged();
    }

    Component.onCompleted: {
        initializeDataModels();
    }


    ListView {

        id: view
        anchors.fill: parent
        anchors.leftMargin: 10
        anchors.rightMargin: 10
        clip: true
        model: itemModel
    }

    onLatitudeChanged: {
        latH = latitude >= 0 ? "N" : "S"

        var d = Math.abs(latitude)
        var m = d * 60.

        latD = Math.floor(d)
        latM = Math.floor((d - Math.floor(d)) * 60.)
        latS = Math.round((m - Math.floor(m)) * 60.)

    }

    onLongitudeChanged: {
        longH = longitude >= 0 ? "E" : "W"

        var d = Math.abs(longitude)
        var m = d * 60.

        longD = Math.floor(d)
        longM = Math.floor((d - Math.floor(d)) * 60.)
        longS = Math.round((m - Math.floor(m)) * 60.)

    }


    VisualItemModel {
        id: itemModel

        HeaderRow { title: "Location" }

        SeparatorRow {}


        PageRow {
            title: "Select location from list"
            mouseArea.onClicked: pageStack.push(locationListPage)
        }

        PageRow {
            id: row
            title: "Update from device position"
            PositionSource {
                id: positionSource
                active: false
                onPositionChanged: {
                    //console.log("position changed")
                    if (position.altitudeValid)
                        altitude = position.coordinate.altitude
                    if (position.longitudeValid && position.latitudeValid)
                    {
                        longitude = position.coordinate.longitude
                        latitude = position.coordinate.latitude
                        calcLongitude()
                        calcLatitude()
                        updateLocation(true)
                        banner.text = "Position updated."
                        banner.show()
                        row.subtitle = "Position updated."
                        //console.log("updated")
                    }
                    else
                    {
                        banner.text = "Could not get position from device."
                        banner.show()
                        row.subtitle = "Positioning failed."
                        //console.log("could not get position")
                    }
                    active = false
                }
            }

            mouseArea.onClicked: {
                if (positionSource.positioningMethod == PositionSource.NoPositioningMethod)
                {
                    banner.text = "No positioning method available."
                    banner.show()
                }
                else
                {
                    positionSource.active = true
                    banner.text = "Retreiving position from device. Please wait."
                    banner.show()
                    row.subtitle = "Retrieving position..."
                    //console.log("Position source active: " + positionSource.active)
                }
            }

            InfoBanner{
                id: banner
            }

        }


        PageRow {
            title: "Name"
            subtitle: name
            TextFieldPage {
                id: nameEditPage
                title: "Location Name"
                onTextFieldChanged: { name = text; updateLocation(false) }
            }
            mouseArea.onClicked: {
                nameEditPage.textField.text = name
                pageStack.push(nameEditPage)
            }
        }

        PageRow {
            title: "Country"
            subtitle: country
            TextFieldPage {
                id: countryEditPage
                title: "Location Country"
                onTextFieldChanged: { country = text; updateLocation(true) }
            }
            mouseArea.onClicked: {
                countryEditPage.textField.text = country
                pageStack.push(countryEditPage)
            }
        }

        PageRow {
            title: "Planet"
            subtitle: planet
            TextFieldPage {
                id: planetEditPage
                title: "Location Planet"
                onTextFieldChanged: { planet = text; updateLocation(true) }
            }
            mouseArea.onClicked: {
                planetEditPage.textField.text = planet
                pageStack.push(planetEditPage)
            }
        }

        PageRow {
            title: "Latitude"
            subtitle: latH + " " + latD + "d " + latM + "m " + latS + "s"
            mouseArea.onClicked: {
                hemisphereColumn.selectedIndex = latH == "N" ? 0 : 1
                degColumn.selectedIndex = latD
                minColumn.selectedIndex = latM
                secColumn.selectedIndex = latS
                latitudeDialog.open()
            }
        }

        PageRow {
            title: "Longitude"
            subtitle: longH + " " + longD + "d " + longM + "m " + longS + "s"
            mouseArea.onClicked: {
                longDirColumn.selectedIndex = longH == "E" ? 0 : 1
                deg2Column.selectedIndex = longD
                min2Column.selectedIndex = longM
                sec2Column.selectedIndex = longS
                longitudeDialog.open()
            }
        }

        PageRow {
            title: "Altitude"
            subtitle: altitude + "m"
            TextFieldPage {
                id: altitudeEditPage
                title: "Location Altitude (meters)"
                onTextFieldChanged: { altitude = text; locationChanged() }
                inputMethodHints: Qt.ImhDigitsOnly
            }
            mouseArea.onClicked: {
                altitudeEditPage.textField.text = altitude
                pageStack.push(altitudeEditPage)
            }

        }

        Item {
            id: addToListButton
            width: view.width
            height: 60

            Button {
                text: "Add to List"
                anchors.centerIn: parent
                onClicked: {
                    addLocationToList()
                    newLocation = false
                    canDeleteLocation = true
                }
            }
            enabled: newLocation
        }

        Item {
            id: deleteButton
            width: view.width
            height: 60

            Button {
                text: "Delete"
                anchors.centerIn: parent
                onClicked: {
                    deleteLocation()
                    newLocation = true
                    canDeleteLocation = false
                }
            }
            enabled: canDeleteLocation
        }

        Item {
            id: item
            width: view.width
            height: view.width
            Image {
                id: image
                source: terrainImage
                fillMode: Image.PreserveAspectFit
                anchors.fill: parent

                MouseArea {
                    anchors.centerIn: parent
                    width: image.paintedWidth
                    height: image.paintedHeight
                    onClicked: {
                        var x = (mouseX - (image.paintedWidth) * 0.5) / image.paintedWidth * 2.
                        var y = (mouseY - (image.paintedHeight) * 0.5) / image.paintedHeight * 2.

                        longitude = x * 180
                        latitude = -y * 90
                        updateLocation(true)
                    }
                }
            }
        }

    }

    function calcLatitude()
    {
        if (latD == 90)
        {
            latM = 0;
            latS = 0;
        }
        latitude = (latH == "N" ? 1. : -1.) * (latD + latM / 60. + latS / 3600.)
    }

    function calcLongitude()
    {
        if (longD == 180)
        {
            longM = 0;
            longS = 0;
        }
        longitude = (longH == "E" ? 1. : -1.) * (longD + longM / 60. + longS / 3600.)
    }


    TumblerDialog {
        id: latitudeDialog
        titleText: "Select latitude"
        acceptButtonText: "Ok"
        rejectButtonText: "Cancel"
        columns: [ hemisphereColumn, degColumn, minColumn, secColumn ]
        onAccepted: {
            latH = hemisphereList.get(hemisphereColumn.selectedIndex).value
            latD = degList.get(degColumn.selectedIndex).value
            latM = minList.get(minColumn.selectedIndex).value
            latS = secList.get(secColumn.selectedIndex).value
            calcLatitude()
            updateLocation(true)
        }
    }

    TumblerDialog {
        id: longitudeDialog
        titleText: "Select longitude"
        acceptButtonText: "Ok"
        rejectButtonText: "Cancel"
        columns: [ longDirColumn, deg2Column, min2Column, sec2Column ]
        onAccepted: {
            longH = longDirList.get(longDirColumn.selectedIndex).value
            longD = deg2List.get(deg2Column.selectedIndex).value
            longM = minList.get(min2Column.selectedIndex).value
            longS = secList.get(sec2Column.selectedIndex).value
            calcLongitude()
            updateLocation(true)
        }
    }

    function initializeDataModels() {

        hemisphereList.append({"value" : "N"})
        hemisphereList.append({"value" : "S"})

        longDirList.append({"value" : "E"})
        longDirList.append({"value" : "W"})

        for (var deg = 0; deg <= 90; deg++) { degList.append({"value" : deg}) }
        for (var min = 0; min <= 59; min++) { minList.append({"value" : min}) }
        for (var sec = 0; sec <= 59; sec++) { secList.append({"value" : sec}) }

        for (var deg2 = 0; deg2 <= 180; deg2++) { deg2List.append({"value" : deg2}) }
    }


    TumblerColumn {
        id: hemisphereColumn
        items: ListModel { id: hemisphereList }
        label: "N/S"
        //selectedIndex: latH == "N" ? 0 : 1
    }

    TumblerColumn {
        id: degColumn
        items: ListModel { id: degList }
        label: "Deg"
        //selectedIndex: latD
    }

    TumblerColumn {
        id: minColumn
        items: ListModel { id: minList }
        label: "Min"
        //selectedIndex: latM
    }

    TumblerColumn {
        id: secColumn
        items: ListModel { id: secList }
        label: "Sec"
        //selectedIndex: latS
    }

    TumblerColumn {
        id: longDirColumn
        items: ListModel { id: longDirList }
        label: "E/W"
        //selectedIndex: longH == "E" ? 0 : 1
    }

    TumblerColumn {
        id: deg2Column
        items: ListModel { id: deg2List }
        label: "Deg"
        //selectedIndex: longD
    }
    TumblerColumn {
        id: min2Column
        items: minList
        label: "Min"
        //selectedIndex: longM
    }

    TumblerColumn {
        id: sec2Column
        items: secList
        label: "Sec"
        //selectedIndex: longS
    }

}
