import QtQuick 2.9
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.0

/* The main tool bar allows user to select pixel grid size,
    open a desired folder with images, navigate <> in the selected folder.
    When a <- or -> is clicked, the corresponding cignal is emitted to main
    window, the same when the new grid is selected or user wants to select directory.
*/

Rectangle {
    id: root

    property string infoText: "information text"

    readonly property var pixelGridSizes: [100, 50, 20, 10]
//    {
//        0 : 100,
//        1 : 50,
//        2 : 20,
//        3 : 10
//    }

    signal forwardClicked
    signal backwardClicker
    signal folderSelected
    signal gridSelected

    height: 50

    Row {
        id: layout
        anchors.fill: parent
        spacing: 10

        Button {
            id: openBtn
            text: "Open dir ..."
            width: 100
            height: root.height
            font.pixelSize: 12

            onClicked: {
                fileDialog.open()
            }
        }

        Text {
            id: gridText
            text: "Grid chunk (px):"
            width: contentWidth
            height: root.height
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.pixelSize: 12
        }

        ComboBox {
            id: gridSelector
            model: root.pixelGridSizes
            width: 100
            height: root.height
            onCurrentIndexChanged: {
                root.gridSelected(pixelGridSizes[currentIndex])
            }
        }

        // TODO: replace by more detailed info panel
        // with info about: filepath, n/m, pixel size, and so on.
        Text {
            id: infoText
            text: root.infoText
            width: 370
            height: root.height
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter
            font.pixelSize: 12
        }

        Button {
            id: backwardBtn
            text: "<"
            width: 50
            height: root.height
            font.pixelSize: 12
        }

        Button {
            id: forwardBtn
            text: ">"
            width: 50
            height: root.height
            font.pixelSize: 12
        }
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a folder with images or a single image"
        folder: shortcuts.home

        selectFolder: true
        selectMultiple: true

        onAccepted: {
            console.log("User selected folder: " + fileDialog.fileUrls)
            root.folderSelected(fileDialog.fileUrls)
        }
        onRejected: {
            console.log("Folder selection anceled")
        }
    }
}
