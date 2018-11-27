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

        readonly property real dpX: sourceSize.width / paintedWidth
        readonly property real dpY: sourceSize.height / paintedHeight

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

        readonly property int totalColumns: 5
        readonly property int totalRows: 4

        Row {
            id: seleection
            Repeater {

            }
        }
    }

    SelectionChunk {
        id: selectionChunkDummy

        anchors.left: imageArea.left
        anchors.top: imageArea.top

        width: root.pixelGridSize * viewer.dpX
        height: root.pixelGridSize * viewer.dpY
    }
}
