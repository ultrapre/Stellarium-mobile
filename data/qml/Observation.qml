import QtQuick 2.0

import QtQuick 2.2
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Styles 1.4
import Stellarium 1.0
import QtQuick.Dialogs 1.0


StelDialog {
    id: observeplugin
    title: qsTr("Observation")
    width: rootStyle.niceMenuWidth

    // XXX: I guess we could move the flickable + column into a custom item.
    Flickable {
        width: parent.width
        height: rootStyle.maxMenuHeight
        clip: true
        contentWidth: parent.width
        contentHeight: columnObsevation.height
        flickableDirection: Flickable.VerticalFlick


        Column {
            id: columnObsevation
            width: parent.width
            height: childrenRect.height

            StelButton {
                id: selectObservingFileButton
                text: qsTr("Select Observing List File")
                onClicked: {
                    fds.open()
                    console.log("opening:"+fds.fileUrl);
                }
                onTextChanged: {
                    console.log(text+" "+fds.fileUrl);
                    if(text=="Setting..."&&fds.fileUrl!=""){
                        text = qsTr("Select Observing List File");
                        stellarium.writeStringSetting("astro/observingListFile", fds.fileUrl)
                        console.log("now set to:"+stellarium.getStringSetting("astro/observingListFile"))
                    }
                }
            }

            FileDialog {
                    id:fds
                    title: "选择文件"
                    folder: "file:///sdcard"
                    selectExisting: true
                    selectFolder: false
                    selectMultiple: false
                    nameFilters: ["文件 (*.*)"]

                    onAccepted: {
                        console.log("Now folder: " + fds.folder);
                        selectObservingFileButton.text = qsTr("Setting...");
                        console.log("You choise: " + fds.fileUrl);
                    }

                    onRejected: {
//                        labels.text = "";
                        console.log("Canceled");
//                        Qt.quit();
                    }

                }


            StelButton {
                text: qsTr("Apply Observing Filter")
                action: "action_applyObserving"
            }

        }
    }

}
