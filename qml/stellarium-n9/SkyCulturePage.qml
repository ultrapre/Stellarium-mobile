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
import QtWebKit 1.0



Page {
    tools: commonTools

    id: skyCulturePage

    property string skyCultureName
    property string htmlFile

    objectName: "SkyCulturePage"

    signal skyCultureChanged(int index)

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
            title: "Starlore"
        }

        SectionRow { title: "Current starlore" }
        Label {
            text: skyCultureName
            font: UiConstants.TitleFont
        }

        Item {
            width: view.width
            height: 80
            Button {
                signal triggered(bool checked)
                objectName: "UseSkyCultureAsDefault"
                text: "Set as default"
                checkable: true
                onCheckedChanged: {
                    enabled = !checked
                    triggered(checked)
                }
                anchors.centerIn: parent
            }
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

        SectionRow { title: "Description" }

        Item { width: view.width; height: 30 }


        WebView {
            html: "<html><body bgcolor=\"#505050\">" + htmlFile + "</body><html>"
            //width: view.width
            preferredWidth: view.width
            settings.minimumFontSize: 24
        }



    }

    SelectionDialog {
        id: selectionDialog
        titleText: "Select starlore:"
        model: skyCultures
        onSelectedIndexChanged: {
            skyCulturePage.skyCultureChanged(selectedIndex)
        }
    }

}





