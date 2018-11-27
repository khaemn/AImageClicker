import QtQuick 2.9
import QtQuick.Controls 2.0

ApplicationWindow {
    id: root

    visible: true

    width: 800
    height: 600
    maximumHeight: height
    maximumWidth: width
    minimumHeight: height
    minimumWidth: width

    title: qsTr("AImageClicker")

    color: "darkgrey"

    MainBar {
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.right: parent.right
    }
}
