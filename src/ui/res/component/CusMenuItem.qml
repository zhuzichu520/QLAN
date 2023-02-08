﻿//basicmenuitem.qml
import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Controls.impl 2.12
import QtQuick.Templates 2.12 as T
import QtQuick.Shapes 1.12
import "../storage"

T.MenuItem {
    id: control

    property color textColor: control.highlighted ? Theme.colorFontPrimary : Theme.colorFontPrimary
    property color buttonColor: control.down ? Theme.colorBackground: control.highlighted ? Qt.alpha(Theme.colorPrimary,0.3): "transparent"
    property color indicatorColor: "black"
    property color arrowColor: "black"

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            implicitContentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             implicitContentHeight + topPadding + bottomPadding,
                             implicitIndicatorHeight + topPadding + bottomPadding)

    padding: 0
    spacing: 6

    contentItem: Text {
        readonly property real arrowPadding: control.subMenu && control.arrow ? control.arrow.width + control.spacing : 0
        readonly property real indicatorPadding: control.checkable && control.indicator ? control.indicator.width + control.spacing : 0
        readonly property real left_pd: !control.mirrored ? indicatorPadding : arrowPadding
        //没有边距就贴在边上了
        leftPadding: left_pd<=0?12:left_pd
        rightPadding: control.mirrored ? indicatorPadding : arrowPadding
        horizontalAlignment: Text.AlignLeft
        verticalAlignment: Text.AlignVCenter
        text: control.text
        font: control.font
        color: control.textColor
    }

    indicator: Item {
        x: control.mirrored ? control.width - width - control.rightPadding : control.leftPadding
        //y: control.topPadding + (control.availableHeight - height) / 2
        implicitWidth: 30
        implicitHeight: 30
        Rectangle {
            width: parent.width-8
            height: width
            anchors.centerIn: parent
            visible: control.checkable
            Rectangle {
                width: parent.width-8
                height: width
                anchors.centerIn: parent
                visible: control.checked
                color: control.indicatorColor
            }
        }
    }

    arrow: Shape {
        id: item_arrow
        x: control.mirrored ? control.leftPadding : control.width - width - control.rightPadding
        //y: control.topPadding + (control.availableHeight - height) / 2
        visible: control.subMenu
        implicitWidth: 30
        implicitHeight: 30
        ShapePath {
            strokeWidth: 0
            strokeColor: control.arrowColor
            fillRule: ShapePath.WindingFill
            fillColor: control.arrowColor
            startX: item_arrow.width/4
            startY: item_arrow.height*3/4
            PathLine { x:item_arrow.width/4; y:item_arrow.height/4 }
            PathLine { x:item_arrow.width/2; y:item_arrow.height/2 }
            PathLine { x:item_arrow.width/4; y:item_arrow.height*3/4 }
        }
    }

    background: Rectangle {
        implicitWidth: 94
        implicitHeight: 30
        width: control.width
        height: control.height
        color: control.buttonColor
    }
}
