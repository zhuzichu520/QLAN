﻿import QtQuick 2.15
import QtQuick.Controls 2.15
import "../storage"

ToolTip {
    id:tool_tip

    contentItem: Text {
        text: tool_tip.text
        font: tool_tip.font
        wrapMode: Text.WrapAnywhere
        color: Theme.colorFontPrimary
    }

    background: Item {

        Rectangle{
            anchors.fill: parent
            color: Theme.colorBackground
            radius: 5
        }

        Shadow{
            anchors.fill: parent
            shadowColor: Theme.colorPrimary
        }

    }
}
