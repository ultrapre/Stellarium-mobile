import QtQuick 2.0

import QtQuick 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import Stellarium 1.0
import QtQuick.Dialogs 1.0


StelDialog {
    id: viewsky
    title: qsTr("Sky View")
    width: rootStyle.niceMenuWidth

    // XXX: I guess we could move the flickable + column into a custom item.
    Flickable {
        width: parent.width
        height: Math.min(columnSky.height, rootStyle.maxMenuHeight)
        clip: true
        contentWidth: parent.width
        contentHeight: columnSky.height
        flickableDirection: Flickable.VerticalFlick


        Column {
            id: columnSky
            width: parent.width
            height: childrenRect.height

        StelListItem {
            checkbox: true
            action: "actionShow_Telrads"
            setting: "astro/flag_telrads"
            text: qsTr("Show telrads")
        }

        StelListItem {
            checkbox: true
            action: "actionShow_Toast_Survey"
            setting: "astro/flag_toast_survey"
            text: qsTr("Show toast survey")
        }

        StelListItem {
            checkbox: true
            action: "actionShow_Planets_Hints"
            setting: "astro/flag_planets_hints"
            text: qsTr("Show planet markers")
        }

        StelListItem {
            checkbox: true
            action: "actionShow_Ecliptic_Line"
            setting: "viewing/flag_ecliptic_line"
            text: qsTr("Show ecliptic line")
        }

        StelListItem {
            checkbox: true
            action: "actionShow_Meridian_Line"
            setting: "viewing/flag_meridian_line"
            text: qsTr("Show meridian line")
        }

        StelListItem {
            checkbox: true
            action: "actionShow_Constellation_Boundaries"
            setting: "viewing/flag_constellation_boundaries"
            text: qsTr("Constellation boundaries")
        }

        StelListItem {
            text: qsTr("Light pollution")
            rightText: stellarium.lightPollution
            withArrow: true
            onClicked: {
                var picker = root.openPage("ValuePicker.qml")
                picker.title = qsTr("Light pollution")
                picker.min = 1
                picker.max = 9
                picker.value = stellarium.lightPollution
                function onValueChanged() {
                    stellarium.lightPollution = picker.value
                }
                picker.valueChanged.connect(onValueChanged)
            }
        }

        StelListItem {
            text: qsTr("Milky Way brightness")
            rightText: stellarium.milkyWayBrightness
            withArrow: true
            onClicked: {
                var picker = root.openPage("ValuePicker.qml")
                picker.title = qsTr("Milky Way brightness")
                picker.min = 0
                picker.max = 10
                picker.value = stellarium.milkyWayBrightness
                function onValueChanged() {
                    stellarium.milkyWayBrightness = picker.value
                }
                picker.valueChanged.connect(onValueChanged)
            }
        }

        StelListItem {
            text: qsTr("Thickness of lines")
            rightText: stellarium.linesThickness
            withArrow: true
            onClicked: {
                var picker = root.openPage("ValuePicker.qml")
                picker.title = qsTr("Thickness of lines")
                picker.min = 0
                picker.max = 8
                picker.value = stellarium.linesThickness
                function onValueChanged() {
                    stellarium.linesThickness = picker.value
                }
                picker.valueChanged.connect(onValueChanged)
            }
        }
        }
    }
}
