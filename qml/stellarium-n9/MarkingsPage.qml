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
            title: "Markings"
        }


        SectionRow {
            title: "Celestial sphere"
        }

        CheckedButton {
            objectName: "EquatorialGrid"
            title: "Equatorial grid"
        }

        CheckedButton {
            objectName: "EquatorialGridJ2000"
            title: "Equatorial grid J2000"
        }

        CheckedButton {
            objectName: "EclipticGridJ2000"
            title: "Ecliptic grid J2000"
        }

        CheckedButton {
            objectName: "AzimuthalGrid"
            title: "Azimuthal grid"
        }

        CheckedButton {
            objectName: "GalacticGrid"
            title: "Galactic grid"
        }

        Item {
            width: 10
            height: 10
        }

        CheckedButton {
            objectName: "CardinalPoints"
            title: "Cardinal points"
        }

        CheckedButton {
            objectName: "Meridian"
            title: "Meridian"
        }

        CheckedButton {
            objectName: "Ecliptic"
            title: "Ecliptic"
        }

        CheckedButton {
            objectName: "Equator"
            title: "Equator"
        }

        CheckedButton {
            objectName: "Horizon"
            title: "Horizon"
        }

        CheckedButton {
            objectName: "GalacticPlane"
            title: "Galactic plane"
        }

        SectionRow {
            title: "Constellations"
        }

        CheckedButton {
            objectName: "ShowConstellationLines"
            title: "Show lines"
        }

        CheckedButton {
            objectName: "ShowConstellationLabels"
            title: "Show labels"
        }

        CheckedButton {
            objectName: "ShowConstellationBoundaries"
            title: "Show borders"
        }
        CheckedButton {
            objectName: "ShowConstellationArt"
            title: "Show art"
        }

        SliderRow {
            objectName: "ArtBrightness"
            title: "Art brightness"
            minimumValue: 0
            maximumValue: 1
            stepSize: 0.05
        }

    }

}





