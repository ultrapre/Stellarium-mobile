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
            title: "Sky"
        }


        SectionRow {
            title: "Stars"
        }

        SliderRow {
            objectName: "AbsoluteScale"
            title: "Absolute scale"
            minimumValue: 0.1
            maximumValue: 2.0
            stepSize: 0.1
        }

        SliderRow {
            objectName: "RelativeScale"
            title: "Relative scale"
            minimumValue: 0.3
            maximumValue: 2.0
            stepSize: 0.1
        }

        CheckBoxAndSliderRow {
            objectName: "Twinkle"
            title: "Twinkle"
            minimumValue: 0.0
            maximumValue: 1.5
            stepSize: 0.1
        }


        CheckedButton {
            objectName: "DynamicEyeAdaptation"
            title: "Dynamic eye adaptation"
        }

        SectionRow {
            title: "Atmosphere"
        }


        CheckedButton {
            objectName: "ShowAtmosphere"
            title: "Show atmosphere"
        }



        SliderRow {
            objectName: "LightPollution"
            title: "Light pollution"
            minimumValue: 1
            maximumValue: 9
            stepSize: 1
        }


        SectionRow {
            title: "Planets and satellites"
        }

        CheckedButton {
            objectName: "ShowPlanets"
            title: "Show planets"
        }

        CheckedButton {
            objectName: "ShowPlanetMarkers"
            title: "Show planet markers"
        }

        CheckedButton {
            objectName: "ShowPlanetOrbits"
            title: "Show planet orbits"
        }

        CheckedButton {
            objectName: "SimulateLightSpeed"
            title: "Simulate light speed"
        }

        CheckedButton {
            objectName: "ScaleMoon"
            title: "Scale moon"
        }

        SectionRow {
            title: "Labels and markers"
        }

        CheckBoxAndSliderRow {
            objectName: "StarLabels"
            title: "Stars"
            minimumValue: 0
            maximumValue: 10
            stepSize: 0.1
        }

        CheckBoxAndSliderRow {
            objectName: "NebulaLabels"
            title: "Nebulas"
            minimumValue: 0
            maximumValue: 10
            stepSize: 0.1
        }

        CheckBoxAndSliderRow {
            objectName: "PlanetLabels"
            title: "Planets"
            minimumValue: 0
            maximumValue: 10
            stepSize: 0.1
        }

    }

}





