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

// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

import com.nokia.meego 1.1


Item {

    property string title
    property string subtitleColor: theme.inverted ? "#C8C8C8" : "#505050"

    width: view.width
    height: 40
    Label {
        id: label
        text: title
        color: subtitleColor
        font {
            pixelSize: 22
            bold: true
        }

        anchors {
            right: parent.right
            bottom: parent.bottom
            //verticalCenter: parent.verticalCenter
        }
    }
    Rectangle {
        id: line
        height: 1;
        color: subtitleColor
        anchors {
            left: parent.left
            right: label.left
            rightMargin: 10
            verticalCenter: label.verticalCenter
        }
    }
}
