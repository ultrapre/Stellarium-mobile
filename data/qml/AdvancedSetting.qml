
import QtQuick 2.0

import QtQuick 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import Stellarium 1.0
import QtQuick.Dialogs 1.0


StelDialog {
    id: advancedSettingDiag
    title: qsTr("Advanced Setting")
    width: rootStyle.niceMenuWidth

    // XXX: I guess we could move the flickable + column into a custom item.
    Flickable {
        width: parent.width
        height: Math.min(columnAdvancedSetting.height, rootStyle.maxMenuHeight)
        clip: true
        contentWidth: parent.width
        contentHeight: columnAdvancedSetting.height
        flickableDirection: Flickable.VerticalFlick


        Column {
            id: columnAdvancedSetting
            width: parent.width
            height: childrenRect.height

            StelButton {
                //y:dsoAmountview.height+dsoAmountview.y
                text: qsTr("Restore default settings")
                anchors.margins: rootStyle.margin
                onClicked: stellarium.resetSettings()
            }

        }
    }

}
