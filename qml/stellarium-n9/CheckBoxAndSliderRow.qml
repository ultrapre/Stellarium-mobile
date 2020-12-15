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

//import com.nokia.meego 1.1
Item {

    id: item

    property alias slider: slider  // this doesn't work! why not?

    property alias minimumValue: slider.minimumValue
    property alias maximumValue: slider.maximumValue
    property alias stepSize: slider.stepSize
    property alias value: slider.value
    property alias checked: cb.checked
    property string title

    signal valueChanged(double value)
    signal triggered(bool checked)

    width: view.width
    height: 100


    Label {
        id: label
        text: title
        font: UiConstants.FieldLabelFont
    }

    Item {

        width: parent.width
        height: slider.height

        CheckBox {
            id: cb
            onCheckedChanged: { item.triggered(checked) }
            anchors {
                left: parent.left
                leftMargin: 20
                verticalCenter: parent.verticalCenter
            }
        }

        Slider {
            id: slider
            onValueChanged: { item.valueChanged(value) }
            anchors {
                left: cb.right
                right: parent.right
                leftMargin: 5
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            valueIndicatorVisible: true

        }

        anchors {
            top: label.bottom
        }
    }


}
