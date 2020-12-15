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


Item {
    id: listItem

    property string title;
    property string subtitle;
    property string iconSource;

    property string titleColor: theme.inverted ? "#ffffff" : "#282828"
    property string subtitleColor: theme.inverted ? "#C8C8C8" : "#505050"

    property alias checked: sw.checked

    height: UiConstants.ListItemHeightDefault
    width: view.width

    signal triggered(bool checked)

    Row {
        anchors.fill: parent
        spacing: 10

        Image {
            anchors.verticalCenter: parent.verticalCenter
            visible: iconSource ? true : false
            width: 40
            height: 40
            source: iconSource ? iconSource : ""
        }

        Column {
            anchors.verticalCenter: parent.verticalCenter


            Label {
                id: mainText
                text: title
                font: UiConstants.TitleFont
                color: titleColor
            }

            Label {

                id: subText
                text: subtitle ? subtitle : ""
                font: UiConstants.SubtitleFont
                color: subtitleColor
                visible: text != ""
            }
        }
    }

    Switch {

        id: sw
        onCheckedChanged: { listItem.triggered(checked) }
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 20
        }

    }

}
