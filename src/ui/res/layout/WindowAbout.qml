import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import QtQuick.Layouts 1.15
import "../js/Router.js" as R
import "../component"
import "../storage"

CusWindow {
    id:window
    width: 550
    height: 470
    minimumWidth: 550
    minimumHeight: 470
    title: "关于"

    page: CusPage{

        CusToolBar {
            id:toolBar
            darkEnable: false
            topEnable: false
            title:window.title
        }


        Text{
            text: "个人博客"
            anchors{
                centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                onClicked: {
                    Qt.openUrlExternally("https://zhuzichu520.github.io")
                }
            }
        }


    }


}
