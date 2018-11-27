import QtQuick 2.9
import QtQuick.Controls 2.0

Item {
    id: root

    // TODO: bind to corresp. control
    property int pixelGridSize: 100

    function openFile(path) {
        currentImageSource = path;
    }

    function openFolder(path) {
        console.log("ON OPEN FOLDER NOT IMPL");
    }

    function forward() {
        console.log("ON FORW CLICKED NOT IMPL");
    }

    function back() {
        console.log("ON BACK CLICKED NOT IMPL");
    }

    property string currentImageSource: ""

    Image {
        id: viewer

        readonly property real dpX: paintedWidth / sourceSize.width
        readonly property real dpY: paintedHeight / sourceSize.height

        readonly property int horizontalChunks: Math.round(sourceSize.width / root.pixelGridSize)
        readonly property int verticalChunks: Math.round(sourceSize.height / root.pixelGridSize)

        anchors.fill: parent
        source: root.currentImageSource

        // TODO: correct size handling
        fillMode: Image.PreserveAspectFit

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
            id: selectionRows

            anchors.top: parent.top
            anchors.left: parent.left

            Repeater {
                model: selectionGrid.totalRows

                Row {
                    id: selectionRow
                    objectName: "SelectionRow" + index

                    Repeater {
                        model: selectionGrid.chunksInRow
                        SelectionChunk {
                            width: pixelGridSize * viewer.dpX
                            height: pixelGridSize * viewer.dpY
                        }
                    }
                }
            }
        }
    }
}
