/*
 * Stellarium
 * Copyright (C) 2013 Fabien Chereau
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

StelDialog {
	id: root
	title: country ? qsTr("Pick City") : qsTr("Pick Country")
	width: rootStyle.niceMenuWidth
	height: 320*rootStyle.scale
	property string country
	property string city

	Rectangle {
		id: inputRect
		color: 'transparent'
		border.width: 1*rootStyle.scale
		border.color: 'white'
		anchors.margins: rootStyle.margin
		width: root.width
		height: 45 * rootStyle.scale
		TextInput {
			id: textInput
			anchors.fill: parent
			anchors.margins: rootStyle.margin
			font.pixelSize: rootStyle.fontNormalSize
			color: "#AAAAAA"
			text: qsTr("Filter")
			font.italic: true
			verticalAlignment: Text.AlignVCenter
			horizontalAlignment: Text.AlignHCenter
			onActiveFocusChanged: {
				if (activeFocus && text === qsTr("Filter"))
				{
					text = ""
					textInput.font.italic = false
					textInput.color = 'white'
				} else {
					textInput.font.italic = true
					textInput.color = '#AAAAAA'
				}
			}
		}
	}

	ListView {
		id: countriesList
		anchors.left: parent.left
		anchors.top: inputRect.bottom
		width: root.country ? 0 : root.width
		Behavior on width {
			NumberAnimation { easing.type: Easing.InOutQuad }
		}
		height: root.height - inputRect.height
		delegate: StelListItem {
			withArrow: false
			text: qsTr(modelData)
			selected: root.country === modelData
			onClicked: {
				root.country = modelData;
				textInput.focus = false;
				textInput.text = qsTr("Filter");
			}
		}
		model: {
			return filterValues(stellarium.getCountryNames());
		}
		clip: true
	}
	ListView {
		anchors.left: countriesList.right
		anchors.right: parent.right
		anchors.top: inputRect.bottom
		height: root.height
		delegate: StelListItem {
			withArrow: false
			text: qsTr(modelData)
			selected: root.city === modelData
			onClicked: root.city = modelData
		}
		model: {
			return filterValues(stellarium.getCityNames(root.country));
		}
		clip: true
	}

	// Filter a list of strings according to the current filter input.
	function filterValues(values) {
		var ret = [];
		var filter = textInput.text.toLowerCase()
		if (filter === qsTr("filter")) filter = ""
		for (var i = 0; i < values.length; i++) {
			if (values[i].toLowerCase().startsWith(filter))
				ret.push(values[i]);
		}
		return ret;
	}

	onCityChanged: {
		if (!country || !city) return;
		stellarium.location = "%1, %2".arg(city).arg(country)
		close();
	}
}
