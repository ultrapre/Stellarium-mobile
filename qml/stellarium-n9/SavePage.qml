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
            title: "Save"
        }

        SeparatorRow {}

        Item {
            height: 150
            width: view.width
            Button {
                objectName: "SaveCurrentViewOptions"
                text: "Save current view options"
                anchors.centerIn: parent
                onClicked: {
                    banner.show()
                }
            }
        }

    }

    InfoBanner{
        id: banner
        text: "Current view options have been saved."
        //timerEnabled: checkBox1.checked
        //iconSource: checkBox2.checked ? "assets/system_banner_thumbnail.png" : ""
        //timerShowTime: 3000
        //topMargin: 20
        //leftMargin: 20
    }

}





