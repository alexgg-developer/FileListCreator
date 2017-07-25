import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3
import QtQuick.Dialogs 1.2

//import Custom.Backend 1.0
import Custom.FilesViewModel 1.0

ApplicationWindow {
    visible: true
    width: 1440
    height: 810
    title: qsTr("File list creator")


//    BackEnd {
//        id: backend
//    }
    FilesViewModel
    {
        id: filesViewModel
    }

    FileDialog {
        id: fileDialog
        title: "Please choose a file"
        folder: shortcuts.home
        selectFolder: true
        selectMultiple: false
        onAccepted: {
            console.log("You chose: " + fileDialog.fileUrls);
            var path = String(fileDialog.fileUrls)
            pathToSearchTextField.text = path.substring(7, path.length)
            //Qt.quit()
        }
    }

    ColumnLayout {
        id: leftColumn
        TableView {
            TableViewColumn {
                role: "FileName"
                title: "File name"
                width: 300
            }
            TableViewColumn {
                role: "Size"
                title: "Size"
                width: 100
            }
            TableViewColumn {
                role: "Path"
                title: "Path"
                width: 2000
            }
            id: foundFiles
            model: foundFilesModel
            anchors.left: parent.left
            Layout.preferredWidth:  parent.width
            Layout.preferredHeight: parent.height * 0.75
            Layout.alignment: Qt.AlignTop
        }
        TextField {
            id: pathToSearchTextField
            placeholderText: qsTr("Enter folder to search files")
            anchors.top: foundFiles.bottom
            anchors.topMargin: 20
            anchors.rightMargin: 5
            anchors.leftMargin: 5
            anchors.right: selectFolderButton.left
            anchors.left: parent.left
            Layout.alignment: Qt.AlignLeft
        }
        Button
        {
            id: selectFolderButton
            text: "Select folder"
            anchors.top: foundFiles.bottom
            anchors.topMargin: 20
            anchors.right:  searchButton.left
            anchors.rightMargin: 5
            //Layout.margins: 50

            //onClicked: filesViewModel.onGenerateListPressed()
            onClicked: {
                fileDialog.folder = "file://" + pathToSearchTextField.text
                fileDialog.visible = true
            }
        }
        Button
        {
            id: searchButton
            text: "Search"
            anchors.top: foundFiles.bottom
            anchors.topMargin: 20
            //anchors.left: selectFolderButton.right
            //anchors.right: parent.right
            Layout.alignment: Qt.AlignRight
            onClicked: {
                filesViewModel.listFiles(pathToSearchTextField.text)
            }
        }


        width: parent.width * 0.45
        height: parent.height
        anchors.left: parent.left
    }

    ColumnLayout {
        id: rightColumn
        width: parent.width * 0.45
        height: parent.height
        anchors.right: parent.right

        TableView {
            TableViewColumn {
                role: "FileName"
                title: "File name"
                width: 300
            }
            TableViewColumn {
                role: "Size"
                title: "Size"
                width: 100
            }
            TableViewColumn {
                role: "Path"
                title: "Path"
                width: 2000
            }
            id: selectedFiles
            model: selectedFilesModel
            anchors.right: parent.right
            Layout.preferredWidth:  parent.width
            Layout.preferredHeight: parent.height * 0.75
            Layout.alignment: Qt.AlignTop
        }

        Button
        {
            id: generateButton
            text: "Generate random list"
            anchors.top: selectedFiles.bottom
            anchors.topMargin: 20
            Layout.alignment: Qt.AlignHCenter

            onClicked: filesViewModel.onGenerateListPressed()
        }
    }
}
