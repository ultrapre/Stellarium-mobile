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

    id: aboutPage

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


        Label {
            id: label1
            text: "Stellarium N9"
            font {
                pixelSize: 40
                bold: true
            }
        }

        Label {
            text: "Version " + qmlGui.version()
        }

        Label {
            text: "Based on Stellarium " + qmlGui.versionOriginal()
        }

        Item {
            width: view.width
            height: 25
        }


        Item {
            width: view.width
            height: 20
        }

        Item {
            width: view.width
            height: 35
        }

        Label {
            width: view.width
            font.pixelSize: 18
            wrapMode: Text.WordWrap
            onLinkActivated: { Qt.openUrlExternally(link) }

            text: "Stellarium Copyright (c) 2004-2012 Fabien Chereau et al\
<br><br> \
N9 Port Copyright (c) 2012 Marko Srebre \
<br><br> \
\
This program is free software; you can redistribute it and/or \
modify it under the terms of the GNU General Public License \
as published by the Free Software Foundation; either version 2 \
of the License, or (at your option) any later version. \
<br> \
This program is distributed in the hope that it will be useful, \
but WITHOUT ANY WARRANTY; without even the implied warranty of \
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the \
GNU General Public License for more details. \
<br> \
You should have received a copy of the GNU General Public License \
along with this program; if not, write to the Free Software \
Foundation, Inc., 51 Franklin Street, Suite 500, Boston, MA  02110-1335, USA.\
<br>\
<a href=\"https://www.gnu.org/licenses/gpl-2.0.html\">https://www.gnu.org/licenses/gpl-2.0.html</a><br>"
        }



    }
}

