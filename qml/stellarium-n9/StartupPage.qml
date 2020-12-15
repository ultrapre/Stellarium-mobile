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


Window {

    Item {
        width: parent.width
        height: 250
        anchors.centerIn: parent

        Label {
            id: label
            text: "Stellarium N9"
            font {
                pixelSize: 40
                bold: true
            }
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
            }
        }
        Label {
            id: label2
            text: qmlGui.version()
            font {
                pixelSize: 32
                bold: true
            }
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: label.bottom
            }
        }

        Image {
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: label2.bottom
                topMargin: 20
            }

            source: "/usr/share/icons/hicolor/80x80/apps/stellarium-n980.png"
        }
    }

    Label {
        id: label3
        text: "Based on Stellarium " + qmlGui.versionOriginal()
        font {
            pixelSize: 26
        }
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 50
        }

    }
}


