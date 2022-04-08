/*
 * Stellarium
 * Copyright (C) 2014 Guillaume Chereau
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

import QtQuick 2.2
import QtQuick.Dialogs 1.0

import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import Stellarium 1.0

StelDialog {
    id: advanceddiag
    title: qsTr("Advanced")
    //width: rootStyle.niceMenuWidth
    width: 240*stellarium.guiScaleFactor
    height: childrenRect.height

    Column {
        width: parent.width
        Repeater {
            model: advancedModel
            StelListItem {
                text: qsTranslate("ctx", title);
                withArrow: true
                onClicked: advanceddiag.openPage(page)
            }
        }
    }

    ListModel {
        id: advancedModel
        ListElement {
            title: qsTr("Comets")
            page: "Comets.qml"
        }
        ListElement {
            title: qsTr("Plan Observation")
            page: "Observation.qml"
        }
        ListElement {
            title: qsTr("Advanced Setting")
            page: "AdvancedSetting.qml"
        }
    }

}
/*
StelDialog {
	id: root
	title: qsTr("Advanced")
	width: rootStyle.niceMenuWidth

	// XXX: I guess we could move the flickable + column into a custom item.
	Flickable {
		width: root.width
		height: Math.min(column.height, rootStyle.maxMenuHeight)
		clip: true
		contentWidth: column.width
		contentHeight: column.height
		flickableDirection: Flickable.VerticalFlick

		Column {
			id: column
			width: root.width
			height: childrenRect.height

            StelButton {
                text: qsTr("Update Comets (GVB)")
                action: "action_updatecomets1"
            }

            StelButton {
                text: qsTr("Update Comets (MPC)")
                action: "action_updatecomets2"
            }

            StelButton {
                text: qsTr("Restore default settings")
                anchors.margins: rootStyle.margin
                onClicked: stellarium.resetSettings()
            }

		}
	}
}
*/
