import QtQuick 2.0

import QtQuick 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import Stellarium 1.0
import QtQuick.Dialogs 1.0

StelDialog {
    id: cometsplugin
    title: qsTr("Comets")
    width: rootStyle.niceMenuWidth

    // XXX: I guess we could move the flickable + column into a custom item.
    Flickable {
        width: parent.width
        height: Math.min(columnComets.height, rootStyle.maxMenuHeight)
        clip: true
        contentWidth: parent.width
        contentHeight: columnComets.height
        flickableDirection: Flickable.VerticalFlick


        Column {
            id: columnComets
            width: parent.width
            height: childrenRect.height

            StelButton {
                id: updateComets1
                text: qsTr("Update Comets (GVB)")
                action: "action_updatecomets1"
                onClicked: {
                    cometMessage.show(qsTr("Updating comets, please wait few seconds..."))
                }
            }


            StelButton {
                text: qsTr("Update Comets (MPC)")
                action: "action_updatecomets2"
                onClicked: {
                    cometMessage.show(qsTr("Updating comets, please wait few seconds..."))
                }
            }

        }
    }
    StelMessage {
        id: cometMessage
        anchors.verticalCenter: columnComets.width
        y: columnComets.height
        duration: 3000
    }
}



