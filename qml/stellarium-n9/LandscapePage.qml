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

    id: landscapePage

    property string landscapeName
    property string description

    objectName: "LandscapePage"

    signal landscapeChanged(int index)



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
            title: "Landscape"
        }


        SectionRow {
            title: "Options"
        }

        CheckedButton {
            objectName: "ShowGround"
            title: "Show ground"
        }

        CheckedButton {
            objectName: "ShowFog"
            title: "Show fog"
        }

        CheckedButton {
            objectName: "LandscapeSetsLocation"
            title: "Use associated planet and position"
        }

        Item {
            width: view.width
            height: 80
            Button {
                signal triggered(bool checked)
                objectName: "UseLandscapeAsDefault"
                text: "Set as default"
                checkable: true
                onCheckedChanged: {
                    enabled = !checked
                    triggered(checked)
                }
                anchors.centerIn: parent
            }
        }

        SectionRow {
            title: "Current landscape"
        }





        Label {
            objectName: "LandscapeDescription"
            width: view.width
            font.pixelSize: 22
            wrapMode: Text.WordWrap
            text: description
        }

        Item {
            width: view.width
            height: 80

            Button {
                text: "Change"
                anchors.centerIn: parent
                onClicked: selectionDialog.open()
            }
        }

    }

    SelectionDialog {
        id: selectionDialog
        titleText: "Select landscape:"
        model: landscapes
        onSelectedIndexChanged: {
            // TODO: would prefer to return name, but can't find any docs on how access model data
            landscapePage.landscapeChanged(selectedIndex)
        }
    }

}





