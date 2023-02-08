import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls.Material 2.15 as M
import Controller 1.0
import "../js/Router.js" as R
import "../storage"
import "../component"
import "../view"


Item {

    Text {
        anchors.centerIn: parent
        color:Theme.colorFontPrimary
        font.pixelSize: 20
        text: qsTr("正在建设中...")
    }

}
