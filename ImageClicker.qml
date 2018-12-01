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

    readonly property int _selectionButton: Qt.LeftButton
    readonly property int _unselectionButton: Qt.RightButton

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

            property SelectionModel _model: root.model

            anchors.top: parent.top
            anchors.left: parent.left

            function chunkTriggered(chunkX, chunkY, selected) {
                console.log("Chunk triggered: ", chunkX, chunkY);
                model.setChunk(chunkX, chunkY, selected)
            }

            Repeater {
                id: selectionRowsRepeater
                model: root.model.height

                property SelectionModel _model: selectionRowsColumn._model

                Row {
                    id: selectionRow
                    objectName: "SelectionRow" + index

                    readonly property int _index: index

                    function chunkTriggered(chunkX, selected) {
                        selectionRowsColumn.chunkTriggered(chunkX, index, selected);
                    }

                    Repeater {
                        id: chunkRepeater
                        model: root.model.width

                        property SelectionModel _model: selectionRowsRepeater._model

                        SelectionChunk {
                            width: pixelGridSize * viewer.dpX
                            height: pixelGridSize * viewer.dpY
                            selected: chunkRepeater._model.data(chunkRepeater._model.index(selectionRow._index, index))
                                      === SelectionModel.SELECTED
                            unused: chunkRepeater._model.data(chunkRepeater._model.index(selectionRow._index, index))
                                    === SelectionModel.FORBIDDEN
                        }
                    }
                }
            }
        }

        MouseArea {
            id: editArea

            function triggerChunk(_x, _y, selection) {
                var chunkX = Math.floor(_x / (root.pixelGridSize * viewer.dpX))
                var chunkY = Math.floor(_y / (root.pixelGridSize * viewer.dpY))
                root.model.setChunk(chunkX, chunkY, selection)
            }

            function chunkState(_pressedButtons)
            {
                if ((_pressedButtons & _selectionButton)
                        && (_pressedButtons & _unselectionButton)){
                    return SelectionModel.DEFAULT;
                } else if (_pressedButtons & _selectionButton) {
                    return SelectionModel.SELECTED;
                } else if (_pressedButtons & _unselectionButton) {
                    return SelectionModel.FORBIDDEN;
                }
            }

            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onPressed: {
                triggerChunk(mouseX, mouseY, chunkState(pressedButtons))
            }

            onMouseXChanged: {
                if (pressed) {
                    triggerChunk(mouseX, mouseY, chunkState(pressedButtons))
                }
            }
            onMouseYChanged: {
                if (pressed) {
                    triggerChunk(mouseX, mouseY, chunkState(pressedButtons))
                }
            }
        }

        Connections {
            target: root.model
            onModelReset: {
                // Refreshing all grid using bruteforce model resetting.
                selectionRowsRepeater.model = 0;
                selectionRowsRepeater.model = root.model.height;
            }
        }
    }
}
