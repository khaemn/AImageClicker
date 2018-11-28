import QtQuick 2.9
import QtQuick.Controls 2.0

import SelectionModel 1.0

ApplicationWindow {
    id: root

    property SelectionModel backend: backendModel

    visible: true

    width: 1024
    height: 768
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    title: qsTr("AImageClicker")

    color: "darkgrey"

    MainBar {
        id: menu

        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right

        infoText: clicker.statusText
    }

    ImageClicker {
        id: clicker

        anchors.left: parent.left
        anchors.top: menu.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        pixelGridSize: menu.selectedPixelGridSize

        model: root.backend

        Connections {
            target: menu
            onFileSelected: {
                clicker.openFile(path);
            }
            onFolderSelected: {
                clicker.openFolder(path);
            }
            onForwardClicked: {
                clicker.forward();
            }
            onBackwardClicked: {
                clicker.back();
            }
        }
    }
}
