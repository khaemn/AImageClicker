import QtQuick 2.9
import QtQuick.Controls 2.0

import CppBackend 1.0

ApplicationWindow {
    id: root

    property SelectionModel selectionModel: backendModel
    property FileManager fileManager: backendManager

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

        onFileSelected: {
            fileManager.openFile(path);
        }
        onFolderSelected: {
            fileManager.openDir(path);
        }
        onForwardClicked: {
            fileManager.loadNextImage();
        }
        onBackwardClicked: {
            fileManager.loadPrevImage();
        }
    }

    ImageClicker {
        id: clicker

        anchors.left: parent.left
        anchors.top: menu.bottom
        anchors.right: parent.right
        anchors.bottom: parent.bottom

        pixelGridSize: menu.selectedPixelGridSize

        model: root.selectionModel
        manager: root.fileManager
    }
}
