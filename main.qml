import QtQuick 2.0
import QtQml 2.1
import QtQuick.Window 2.2
import QtQuick.Controls 2.1
import QtQuick.Controls 1.4

Window{
    id: mainWindow
    visible: true
    width: 600
    height: 400
    title: "DB Consult"
    //properties
    property string _name
    property string _dialogText
    property double _salary
    property int cIndex: -1 //for current selected UI item
    property int _age
    property int _id

    //split view
    SplitView{
        anchors.fill: parent
        //1st element in SplitView
        //table view for db data display
        TableView{
            //height: mainWindow.height - 100
            width: mainWindow.width - 200
            model: dbHandler
            //TableViewColumns
            TableViewColumn{ title: "ID"; width: 50; delegate: Text { text: model.id } }
            TableViewColumn{ title: "Name"; delegate: Text { text: model.name } }
            TableViewColumn{ title: "Age"; width: 50; delegate: Text { text: model.age } }
            TableViewColumn{ title: "Salary"; delegate: Text { text: model.salary } }
            //when click one of the elements in TableView
            onClicked: { cIndex = currentRow; dbHandler.loadRowData(cIndex) }
        }//end of TableView
        //second element in SplitView
        Rectangle{
            width: mainWindow.width
            color: "white"
            //columns for UI elements
            Column{
                spacing: 8
                anchors.centerIn: parent
                //button
                Image {
                    id: insertBtn
                    width: 50
                    height: 50
                    source: "qrc:/icon/Insert.jpg.ico"
                    fillMode: Image.PreserveAspectFit
                    //event for effects
                    MouseArea{  anchors.fill: insertBtn;
                        hoverEnabled: true
                        onPressed: insertBtn.scale = 0.2
                        onReleased: insertBtn.scale = 1
                        onEntered: insertBtn.scale = 0.8
                        onExited: insertBtn.scale = 1
                        //when click then open insert formulary
                        onClicked: {
                            //if(cIndex >= 0)
                                insertForm.visible = true//open insert window
                            //if not then
                            //else { _dialogText = "Item must be select !"; errDialog.open() }
                        }
                    }
                }
                //button
                Image {
                    id: searchBtn
                    width: 50
                    height: 50
                    source: "qrc:/icon/Search.png"
                    fillMode: Image.PreserveAspectFit
                    //event for effects
                    MouseArea{anchors.fill: searchBtn; onPressed: searchBtn.scale = 0.2
                        hoverEnabled: true
                        onReleased: searchBtn.scale = 1
                        onEntered: searchBtn.scale = 0.8
                        onExited: searchBtn.scale = 1
                        onClicked: {
                            //if(cIndex >= 0) //if record selected then preceed
                                searchForm.visible = true
                            //if not then
                            //else { _dialogText = "Must select item\nbefore operation!"; errDialog.open() }
                        }
                    }
                }
                //button
                Image {
                    id: updateDBBtn
                    width: 50
                    height: 50
                    source: "qrc:/icon/Update.png"
                    fillMode: Image.PreserveAspectFit
                    //event for effects
                    MouseArea{anchors.fill: updateDBBtn; onPressed: updateDBBtn.scale = 0.2
                        hoverEnabled: true
                        onReleased: updateDBBtn.scale = 1
                        onEntered: updateDBBtn.scale = 0.8
                        onExited: updateDBBtn.scale = 1
                        //when click then open insert formulary
                        onClicked: {
                            if(cIndex >= 0)
                                updateDBForm.visible = true//open insert window
                            //if not then
                            else { _dialogText = "Must select item\nfor modification"; errDialog.open() }//open dialog
                        }
                    }
                }
                //button
                Image {
                    id: deleteBtn
                    width: 50
                    height: 50
                    source: "qrc:/icon/Delete.ico"
                    fillMode: Image.PreserveAspectFit
                    //event for effects
                    MouseArea{anchors.fill: deleteBtn; onPressed: deleteBtn.scale = 0.2
                        hoverEnabled: true
                        onReleased: deleteBtn.scale = 1
                        onEntered: deleteBtn.scale = 0.8
                        onExited: deleteBtn.scale = 1
                        //on clicked delete selected row
                        onClicked: {
                            if(cIndex >= 0)
                            dbHandler.dbOperations(cIndex, -1, false)
                            //if not then
                            else { _dialogText = "Select item for deletion!"; errDialog.open() }
                        }
                    }
                }
                //button
                Image {
                    id: updateTBtn
                    width: 50
                    height: 50
                    source: "qrc:/icon/UpdateT.jpg.ico"
                    fillMode: Image.PreserveAspectFit
                    //event for effects
                    MouseArea{anchors.fill: updateTBtn; onPressed: updateTBtn.scale = 0.2
                        hoverEnabled: true
                        onReleased: updateTBtn.scale = 1
                        onEntered: updateTBtn.scale = 0.8
                        onExited: updateTBtn.scale = 1
                        //on clicked delete selected row
                        onClicked: dbHandler.updateTable()
                    }
                }
            } //end of Column
        }//end of Rectangle
    }//end of SplitView

    //window insert form
    Window{
        id: insertForm
        width: 300
        height: 80
        maximumWidth: 300
        maximumHeight: 80
        visible: false
        //row for UI elements
        Row{
            id: rowLayout
            TextField{id: nameText; placeholderText: "Name ..."}
            SpinBox{id: ageSpin; minimumValue: 0; maximumValue: 88}
            SpinBox{id: salarySpin; minimumValue: 0; maximumValue: 9999999999}
        }
        Button{ id: okBtn; anchors.top: rowLayout.bottom; text: "Ok";
            onClicked: {
                //make some checks and then add new record to db
                if(nameText.text != "" || ageSpin.value != 0 && salarySpin.value != 0)
                    //ading new record
                    var result = dbHandler.dbOperations(cIndex, nameText.text, ageSpin.value,
                                                        salarySpin.value, false)
                if(result) { _dialogText = "Record Added !"; errDialog.open(); errDialogAnimation.running = true }
                insertForm.close(); //closing formulary
            }
        }
    }
    //window update form
    Window{
        id: updateDBForm
        width: 300
        height: 80
        maximumWidth: 300
        maximumHeight: 80
        visible: false
        //row for UI elements
        Row{
            id: rowLayoutUpdateForm
            TextField{id: nameTextUpdate; placeholderText: "Name ..."; text: _name}
            SpinBox{id: ageSpinUpdate; minimumValue: 0; maximumValue: 88; value: _age}
            SpinBox{id: salarySpinUpdate; minimumValue: 0; maximumValue: 9999999999; value: _salary}
        }
        Button{ id: okUpdateBtn; anchors.top: rowLayoutUpdateForm.bottom; text: "Ok";
            onClicked: {
                //make some checks and then add new record to db
                if(nameTextUpdate.text != "" && ageSpinUpdate.value != 0 && salarySpinUpdate.value != 0)
                    //updating selected record
                    var result = dbHandler.dbOperations(cIndex, nameTextUpdate.text, ageSpinUpdate.value,
                                                        salarySpinUpdate.value, true)
                if(result) console.log("record updated")
                updateDBForm.close(); //closing formalaty
            }
        }
    }
    //window search form
    Window{
        id: searchForm
        width: 200
        height: 50
        maximumWidth: 200
        maximumHeight: 50
        visible: false
        //row for UI elements
        Row{
            id: rowLayoutSearchForm
            SpinBox{id: idSearchSpin; width: searchForm.width; height: 25
                minimumValue: 0; maximumValue: 100; //value: _id
            }
        }
        Button{ id: okSearchBtn; anchors.top: rowLayoutSearchForm.bottom; text: "Ok";
            onClicked: {
                //make some checks and then add new record to db
                if(idSearchSpin.value != 0)
                    //updating selected record
                    var result = dbHandler.dbOperations(cIndex, idSearchSpin.value, true)
                if(result) { _dialogText = "Record found!"; errDialog.open(); errDialogAnimation.running = true }
                searchForm.close(); //closing formalaty
            }
        }
    }
    //err dialogs
    Dialog{
        id: errDialog
        x: mainWindow.width / 2 - 50
        y: mainWindow.height / 2 - 20
        Text {
            id: dialogText
            text: _dialogText
            font.bold: true
            font.pixelSize: 18
            color: "blue"
            opacity: 0.5
        }
    }
    //err dialog effect

    NumberAnimation {
        id: errDialogAnimation
        target: errDialog
        property: "opacity"
        duration: 3000
        from: 0.5
        to: 0
        running: false
        //easing.type: Easing.InOutQuad
    }
    //connections from C++
    Connections{
        target: dbHandler //everytime UI get clicked then load data
        onRowLoaded: { _name = name; _age = age; _salary = salary; _id = id }
    }
}

