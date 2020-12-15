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



Page {
    tools: commonTools

    id: searchPage

    property alias listView: listView
    property alias searchField: searchField

    property bool found: false

    signal searchTextEntered(string name, bool recheck)
    signal searchTextChanged(string text)


    // A hack for Virtual Keyboard
    MouseArea {
        z:1000
        anchors.fill: parent
        onPressed: {

            mouse.accepted = false;

            var selectedItem = mouse.y < 80 ? searchField : searchPage.childAt(mouse.x, mouse.y);
            if (!selectedItem)
                selectedItem = root;

            selectedItem.focus = true;
            //console.log("Mouse at: " + mouse.x + " " + mouse.y)
        }
    }

    Item {
        id: searchBar
        width: parent.width
        height: 80


        SearchField {
            id: searchField

            anchors {
                left: parent.left
                leftMargin: 10
                right: parent.right
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }

            onSearchTextEntered: {
                searchPage.searchTextEntered(text, true)
            }
        }

        BorderImage {
            id: background
            anchors.fill: parent
            anchors.leftMargin: -10
            anchors.rightMargin: -10
            source: theme.inverted ? "image://theme/meegotouch-panel-inverted-background-pressed" : "image://theme/meegotouch-panel-background-pressed"
        }
    }


    Component {
        id: listDelegate

        Item {
            width: parent.width
            height: 80
            Label {
                text: modelData
                anchors.verticalCenter: parent.verticalCenter
            }

            MouseArea{
                id: mouseArea
                anchors.fill:  parent
                onClicked: {
                    searchPage.searchTextEntered(modelData, false)
                }
            }

            Rectangle {
                id: separator
                width: parent.width; height: 1; color: "#aaaaaa"
                anchors.bottom: parent.bottom
            }

            BorderImage {
                id: background
                anchors.fill: parent
                anchors.leftMargin: -10
                anchors.rightMargin: -10
                visible: mouseArea.pressed
                source: theme.inverted ? "image://theme/meegotouch-panel-inverted-background-pressed" : "image://theme/meegotouch-panel-background-pressed"
            }

        }
    }

    property string lastQueryText

    ListView {
        id: listView
        width: parent.width
        clip: true

        anchors.top: searchBar.bottom
        anchors.bottom: parent.bottom
        delegate: listDelegate

        Timer {
            id: timer
            interval: 500; repeat: true
            running: true

            triggeredOnStart: true
            onTriggered: {
                if (lastQueryText != searchField.text)
                {
                    lastQueryText = searchField.text
                    searchPage.searchTextChanged(searchField.text)
                }
            }
        }
    }


}


