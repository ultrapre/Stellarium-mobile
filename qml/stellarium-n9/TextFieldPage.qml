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
    id: page
    tools: commonTools

    property string title
    property alias textField: textField
    property alias inputMethodHints: textField.inputMethodHints

    signal textFieldChanged(string text)

    Label {
        id: label
        text: title
        anchors {
            top: parent.top
            left: parent.left
        }
    }
    TextField {
        id: textField
        onTextChanged: { textFieldChanged(text) }
        anchors {
            left: parent.left
            right: parent.right
            topMargin: 20
            top: label.bottom
        }

        Image {
            anchors.right: parent.right
            anchors.verticalCenter: parent.verticalCenter
            source:  "image://theme/icon-m-input-clear"

            MouseArea {
                anchors.fill: parent
                onClicked: { textField.text = "" }
            }
        }

    }

    // hack
    MouseArea {
        z:1000
        anchors.fill: parent
        onPressed: {

            mouse.accepted = false

            var selectedItem
            if (mouse.x >= textField.pos.x && mouse.x <= textField.pos.x + textField.width &&
                    mouse.y >= textField.pos.y && mouse.y <= textField.pos.y + textField.height)
            {
                selectedItem = textField
            }
            else
            {
                page.childAt(mouse.x, mouse.y);
            }

            if (selectedItem)
                selectedItem.focus = true
        }
    }

}
