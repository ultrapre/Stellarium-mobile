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

Item {
    id: root
    width: screen.displayWidth
    height: screen.displayHeight

    default property alias content: windowContent.data

    // Read only property true if window is in portrait
    property alias inPortrait: window.portrait



    objectName: "windowRoot"



    Item {
        objectName: "Window"

        id: window
        property bool portrait

        Component.onCompleted: {
            width = screen.platformWidth;
            height = screen.platformHeight;
        }

        anchors.centerIn : parent
        transform: Rotation { id: windowRotation;
                                origin.x: 0;
                                origin.y: 0;
                                angle: 0
                            }

        Item {
            id: windowContent
            width: parent.width
            height: parent.height

            objectName: "windowContent"
            clip: true
        }


        state: screen.orientationString

        onStateChanged: {
            if (inputContext.softwareInputPanelVisible) {
                root.orientationChangeAboutToStart();
                platformWindow.startSipOrientationChange(screen.rotation);
                root.orientationChangeStarted();
                relayoutingWaiter.animating = true
            }
        }


        states: [
            State {
                name: "Landscape"
                PropertyChanges { target: window; rotation: screen.rotation; portrait: screen.isPortrait; explicit: true; }
                PropertyChanges { target: window; height: screen.platformHeight; width: screen.platformWidth; explicit: true; }
                PropertyChanges { target: windowRotation;
                                  origin.x: root.height / 2;
                                  origin.y: root.height / 2; }
            },
            State {
                name: "Portrait"
                PropertyChanges { target: window; rotation: screen.rotation; portrait: screen.isPortrait; explicit: true; }
                PropertyChanges { target: window; height: screen.platformHeight; width: screen.platformWidth; explicit: true; }
                PropertyChanges { target: windowRotation;
                                  origin.x: root.height - root.width / 2;
                                  origin.y: root.width / 2; }
            },
            State {
                name: "LandscapeInverted"
                PropertyChanges { target: window; rotation: screen.rotation; portrait: screen.isPortrait; explicit: true; }
                PropertyChanges { target: window; height: screen.platformHeight; width: screen.platformWidth; explicit: true; }
                PropertyChanges { target: windowRotation;
                                  origin.x: root.height / 2;
                                  origin.y: root.height / 2; }
            },
            State {
                name: "PortraitInverted"
                PropertyChanges { target: window; rotation: screen.rotation; portrait: screen.isPortrait; explicit: true; }
                PropertyChanges { target: window; height: screen.platformHeight; width: screen.platformWidth; explicit: true; }
                PropertyChanges { target: windowRotation;
                                  origin.x: root.height - root.width / 2;
                                  origin.y: root.width / 2; }
            }
        ]


        focus: true

    }
}
