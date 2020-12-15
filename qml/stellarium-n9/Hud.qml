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
import QtMobility.systeminfo 1.1
import com.nokia.meego 1.1


HudWindow {

    Component.onCompleted: {
        theme.inverted = true
    }

    objectName: "HudWindow"

    property int timerate: 1000000
    property string datetime: "2012-01-01 12:00:12"
    property string fps: "17.6 FPS"
    property string fov: "0.000d"
    property string location: "Test"

    property bool locationVisible
    property bool datetimeVisible
    property bool timerateVisible
    property bool fpsVisible
    property bool fovVisible
    property bool buttonsVisible
    property bool disableScreensaver
    property double transparency: 0.0
    property double infoTransparency: 0.0
    property double hudOpacity: 1.0

    ScreenSaver {
        screenSaverDelayed: true
        screenSaverInhibited: disableScreensaver
    }

    Item {
        anchors.fill: parent
        opacity: 1 - infoTransparency

        Label {
            id: name
            objectName: "NameLabel"
            text: ""
            textFormat: Text.StyledText
            wrapMode: Text.NoWrap
            font.pixelSize: 24
            font.bold: true
            anchors {
                left: parent.left
                top: parent.top
            }
            onTextChanged: {
                if (name.text == "")
                    infoText.anchors.top = parent.top
                else {
                    infoText.anchors.top = name.bottom
                    infoText.anchors.topMargin = 5
                }
            }
        }
        Label {
            id: infoText
            objectName: "InfoTextLabel"
            textFormat: Text.StyledText
            wrapMode: Text.NoWrap
            width: parent.width
            font.pixelSize: 16
            anchors {
                //top: name.bottom
                left: parent.left
            }
            onTextChanged: {
                clearSelectionButton.visible = text != ""
            }
        }
    }

    Item {

        anchors.fill: parent
        opacity: 1 - transparency

        HudButton {
            id: clearSelectionButton
            objectName: "ClearSelection"
            platformIconId: "toolbar-backspace"
            visible: false
            anchors {
                top: parent.top
                right: parent.right
            }

        }

        Row {
            id: row1
            HudLabel {
                visible: locationVisible
                text: location
                width: 255
            }

            HudLabel {
                visible: timerateVisible
                text: "Time rate: " + timerate + "x"
            }
            anchors {
                left: parent.left
                leftMargin: 20
                bottom: row2.top
            }

        }
        Row {
            id: row2

            HudLabel {
                visible: fovVisible
                text: fov
                width: 115
            }
            HudLabel {
                visible: fpsVisible
                text: fps
                width: 75
            }
            HudLabel {
                visible: datetimeVisible
                text: datetime
            }
            anchors {
                left: parent.left
                leftMargin: 20
                bottom: buttonsVisible ? row3a.top : parent.bottom
                bottomMargin: buttonsVisible ? 0 : 10
            }
        }


        Row {

            id: row3a

            visible: buttonsVisible

            HudButton {
                objectName: "decreaseTimeSpeed"
                platformIconId: "toolbar-mediacontrol-backwards"
            }

            HudButton {
                objectName: "toggleRealTimeSpeed"
                platformIconId: "toolbar-mediacontrol-play"
            }

            HudButton {
                objectName: "increaseTimeSpeed"
                platformIconId: "toolbar-mediacontrol-forward"

            }

            HudButton {
                objectName: "setTimeNow"
                platformIconId: "toolbar-clock"
            }

            HudButton {
                objectName: "centerSelected"
                platformIconId: "toolbar-search"
            }

            anchors {
                left: parent.left
                //leftMargin: 20
                bottom: parent.bottom
            }

        }



        Row {

            id: row3b
            layoutDirection: Qt.RightToLeft

            HudButton {
                objectName: "settingsWindow"
                platformIconId: "toolbar-view-menu"
            }
            anchors {
                right: parent.right
                //rightMargin: 20
                bottom: parent.bottom
            }

        }
    }

}
