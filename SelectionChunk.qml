import QtQuick 2.9

Rectangle {
    id: root
    
    property bool selected: false

    readonly property color _selectedColor: "#4000FF00"
    readonly property color _color: "#400000CC"
    readonly property color _hoveredBorderColor: "yellow"
    readonly property color _borderColor: "grey"

    readonly property int _selectionButton: Qt.LeftButton
    readonly property int _unselectionButton: Qt.RightButton

    border.color: _borderColor
    border.width: 1

    width: 100
    height: 100

    color: selected ? _selectedColor : _color

    MouseArea {
        anchors.fill: parent
        hoverEnabled: true

        acceptedButtons: Qt.LeftButton | Qt.RightButton

        onEntered: {
            root.border.color = _hoveredBorderColor;
        }
        onExited: {
            root.border.color = _borderColor
        }
        onPressed: {
            root.selected = pressedButtons & _selectionButton;
            // TODO: emit signal.
        }
    }
}
