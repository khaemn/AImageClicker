import QtQuick 2.9
import QtQuick.Controls 2.0

import CppBackend 1.0

Item {
    id: root

    // TODO: bind to corresp. control
    property int pixelGridSize: 100

    property SelectionModel model
    property FileManager manager

    readonly property string statusText: _statusText
    property string _statusText: "Click 'Open ..' to load file or folder."

    readonly property string currentImageSource: manager.imagePath

    Image {
        id: viewer

        readonly property real dpX: paintedWidth / sourceSize.width
        readonly property real dpY: paintedHeight / sourceSize.height

        readonly property int horizontalChunks: Math.round(sourceSize.width / root.pixelGridSize)
        readonly property int verticalChunks: Math.round(sourceSize.height / root.pixelGridSize)

        anchors.fill: parent
        source: root.manager.imagePath

        fillMode: Image.PreserveAspectFit

        onStatusChanged: {
            if (status === Image.Ready) {
                root._statusText = "Loaded\n"
                                  + source
                                  + "\n" + sourceSize.width + "x" + sourceSize.height
            }
        }
    }

    Rectangle {
        id: imageArea

        anchors.centerIn: viewer
        height: viewer.paintedHeight
        width: viewer.paintedWidth

        color: "green"
        opacity: 0.1
    }

    Item {
        id: selectionGrid

        readonly property int totalRows: viewer.verticalChunks
        readonly property int chunksInRow: viewer.horizontalChunks

        anchors.fill: imageArea

        visible: viewer.status === Image.Ready

        Column {
            id: selectionRowsColumn

            anchors.top: parent.top
            anchors.left: parent.left

            function chunkTriggered(chunkX, chunkY, selected) {
                // TODO: impl me
                console.log("Chunk triggered: ", chunkX, chunkY);
                model.setChunk(chunkX, chunkY, selected)
            }

            Repeater {
                model: root.model.height

                Row {
                    id: selectionRow
                    objectName: "SelectionRow" + index

                    readonly property int _index: index

                    function chunkTriggered(chunkX, selected) {
                        selectionRowsColumn.chunkTriggered(chunkX, index, selected);
                    }

                    Repeater {
                        model: root.model.width

                        SelectionChunk {
                            width: pixelGridSize * viewer.dpX
                            height: pixelGridSize * viewer.dpY
                            selected: root.model
                                      ? root.model.data(root.model.index(selectionRow._index, index)) === 1
                                      : false
                            onTriggered: {
                                selectionRow.chunkTriggered(index, wasSelected);
                                console.log("Data at: ", root.model.data(root.model.index(selectionRow._index, index))
                                            , "Selected:", wasSelected, selected)
                                selected = root.model.data(root.model.index(selectionRow._index, index)) === 1
                            }
                        }
                    }
                }
            }
        }
    }
}
