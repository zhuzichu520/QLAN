import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import "../storage"

ColumnLayout {


    id:comboBoxComponentItem

    property alias label: labelText.text
    property alias currentText: control.currentText
    property alias currentIndex: control.currentIndex
    property alias model: control.model
    property var   bindRadio: null
    property var   color: comboBoxComponentItem.bindRadio == null?"#696969":
                                                                   (comboBoxComponentItem.bindRadio.checked?"#6495ED":"#696969")

    property var   borderWidth: comboBoxComponentItem.bindRadio == null?1:
                                                                         (comboBoxComponentItem.bindRadio.checked?2:1)

    property int  leftMargin: 20
    property int  comboBoxWidth: 150
    property int  customIndex: -1


    spacing: 0

    Text
    {
       id: labelText
       color:"#999999"
    }


    RowLayout{

        Layout.topMargin: 5
        ComboBox {
            id: control

            model:[]
            delegate: ItemDelegate
            {
                width: control.width
                contentItem: Text {
                    text: modelData
                    color:  comboBoxComponentItem.color;
                    elide: Text.ElideRight
                    verticalAlignment: Text.AlignVCenter
                }
                highlighted: control.highlightedIndex == index
            }

            indicator: Canvas {
                id: canvas
                x: control.width - width - control.rightPadding
                y: control.topPadding + (control.availableHeight - height) / 2
                width: 12
                height: 8
                contextType: "2d"

                onPaint: {
                    context.reset();
                    context.moveTo(0, 0);
                    context.lineTo(width, 0);
                    context.lineTo(width / 2, height);
                    context.closePath();
                    context.fillStyle =  comboBoxComponentItem.color ;
                    context.fill();
                }
            }

            contentItem: Text {
                leftPadding: 10
                topPadding: 5
                bottomPadding: 5
                rightPadding: control.indicator.width + control.spacing + 15
                text: control.currentText
                color:  comboBoxComponentItem.color
                horizontalAlignment: Text.AlignLeft
                verticalAlignment: Text.AlignVCenter
                elide: Text.ElideRight
            }

            background: Rectangle{
                radius: 3
                border{
                    width: 1
                    color: "#BBBBBB"
                }
            }
        }

        TextField{
            id:inputField
            selectionColor:  Qt.lighter(Theme.colorPrimary,0.3)
            selectByMouse: true
            verticalAlignment: TextInput.AlignVCenter
            height: 30
            rightPadding: 10
            visible: currentIndex === customIndex
            background: Rectangle{
                radius: 3
                border{
                    width: 1
                    color: "#BBBBBB"
                }
            }
        }
    }

    function getText(){
        if(inputField.visible)
            return inputField.text
        return currentText
    }


}
