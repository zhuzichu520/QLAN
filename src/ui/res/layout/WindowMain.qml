import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import Qt.labs.platform 1.1
import QtQuick.Layouts 1.15
import Controller 1.0
import "../js/Router.js" as R
import "../component"
import "../storage"

CusWindow {
    id:window
    width: 800
    height: 600
    minimumWidth: 800
    minimumHeight: 600
    maximumWidth: 800
    maximumHeight: 600
    title: "登录"
    closeDestory:false

    MainController{
        id:controller
    }
    Connections{
        target: controller

        function onResultCodeChanged(){
            var resultCode = controller.resultCode
            hideLoading()
            if(resultCode!==0){
                if(resultCode === 85){
                    showErrorToast("该设备名称已在使用中")
                    return
                }
                showErrorToast("连接失败，错误码："+resultCode)
            }
        }

        function onDriverListChanged(){
            var driverList = controller.driverList
            console.info(JSON.stringify(driverList))
        }

    }

    page: CusPage{

        CusToolBar {
            id:toolBar
            darkEnable: false
            topEnable: false
            isTop: false
            title:"映射网络驱动"
        }

        ColumnLayout{
            anchors{
                top: toolBar.bottom
                left: parent.left
                leftMargin: 40
                topMargin: 40
            }
            Text{
                text:"要映射的网络文件夹:"+uiHelper.getRenderVersion()
                font.pixelSize: 20
                color:Theme.colorPrimary
            }
            Text{
                text:"请为连接指定驱动器号，以及你要连接的文件夹"
                color:Theme.colorFontSecondary
                Layout.topMargin: 10
                font.pixelSize: 14
            }
            CusComboBox
            {
                id:box_local_name
                Layout.topMargin: 10
                label: "驱动器号"
                model: ["Z:","Y:","X:","W:","V:","U:","T:","R:","Q:","P:","O:","N:","M:","L:","K:","J:","I:","H:","G:","F:","E:","B:","A:"]
            }
            PrimaryTextField{
                id:input_remote_name
                lableText:"文件夹："
                text:"\\\\192.168.142.130\\123"
                width: 260
            }
        }

        PrimaryButton{
            id:btn_connect
            width: 260
            height: 36
            text:"连接"

            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom:parent.bottom
                bottomMargin: 15
            }
            onClicked: {
                showLoading()
                controller.onConnect(input_remote_name.text,box_local_name.getText());
            }
        }

        PrimaryButton{
            id:btn_refresh
            width: 260
            height: 36
            text:"刷新"

            anchors{
                horizontalCenter: parent.horizontalCenter
                bottom:parent.bottom
                bottomMargin: 60
            }
            onClicked: {
                controller.onRefresh();
            }
        }


    }
}
