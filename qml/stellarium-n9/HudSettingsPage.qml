/*
 * StellariumN9 QML Gui
 * Copyright (C) 2013 Marko Srebre
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



Page {

    id: hudSettingsPage

    tools: commonTools

    property alias swBrightness : swBrightness.value
    property alias swShowStatus : swShowStatus.checked

    objectName: "HudSettingsPage"

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
            title: "Viewing Settings"
        }


        SectionRow {
            title: "HUD elements"
        }


        CheckedButton {
            objectName: "HudShowLocation"
            title: "Location"
        }

        CheckedButton {
            objectName: "HudShowTimerate"
            title: "Timerate"
        }

        CheckedButton {
            objectName: "HudShowFov"
            title: "FOV"
        }

        CheckedButton {
            objectName: "HudShowFps"
            title: "FPS"
        }

        CheckedButton {
            objectName: "HudShowDatetime"
            title: "Date and Time"
        }

        CheckedButton {
            objectName: "HudShowButtons"
            title: "Buttons"
        }

        SectionRow {
            title: "HUD Transparency"
        }

        SliderRow {
            objectName: "HudTransparency"
            title: "Transparency"
            minimumValue: 0.0
            maximumValue: 0.90
            stepSize: 0.05
        }

        SliderRow {
            objectName: "HudInfoTransparency"
            title: "Object info. transparency"
            minimumValue: 0.0
            maximumValue: 0.90
            stepSize: 0.05
        }

        SectionRow {
            title: "Settings Window"
        }

        SliderRow {
            id: swBrightness
            objectName: "SettingsWindowBrightness"
            title: "Brightness (hack)"
            minimumValue: 0.1
            maximumValue: 1.0
            stepSize: 0.05
            //onValueChanged: { appWindow.opacity = value }
        }

        CheckedButton {
            id: swShowStatus
            objectName: "SettingsWindowShowStatus"
            title: "Show status bar"
            //onCheckedChanged: { appWindow.showStatusBar = checked }
        }


        SectionRow {
            title: "Misc"
        }

        CheckedButton {
            objectName: "HudNightVisionMode"
            title: "Night vision mode"
        }

        CheckedButton {
            objectName: "HudDisableScreensaver"
            title: "Disable screensaver"
        }
    }

}





