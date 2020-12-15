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

TextField {

    id: searchField

    signal searchTextEntered(string text)

    placeholderText: qsTr("Search...")
    //enableSoftwareInputPanel: false
    inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhNoAutoUppercase

    Keys.onReturnPressed: {
        searchTextEntered(text)
    }



    Image {
        id: searchButton
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        source: (searchField.text == "") ? "image://theme/icon-m-common-search"
                                         : "image://theme/icon-m-input-clear"

        MouseArea {
            anchors.fill: parent
            onClicked: {
                searchField.text = "";
                searchTextEntered("");
            }
        }
    }
}
