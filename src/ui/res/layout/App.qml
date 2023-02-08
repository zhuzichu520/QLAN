import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Window 2.15
import "../component"
import "../storage"
import "../js/Router.js" as R

CusWindow{
    id:app
    visible: false
    Component.onCompleted: {
        R.init(app)
        navigate(R.WINDOW_MAIN)
    }

    function createComponent(path){
        return Qt.createComponent(path)
    }

}
