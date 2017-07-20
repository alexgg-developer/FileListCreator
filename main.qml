import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

//import Custom.Backend 1.0
import Custom.FilesViewModel 1.0

ApplicationWindow {
    visible: true
    width: 1440
    height: 810
    title: qsTr("Hello World")

//    BackEnd {
//        id: backend
//    }
    FilesViewModel
    {
        id: filesViewModel
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            ColumnLayout {
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
                        width: 1000
                    }
                    id: foundFiles
                    model: foundFilesModel
                    anchors.left: parent.left
                    //width: parent.width
                    //height: parent.height * 0.75
                    Layout.preferredWidth:  parent.width
                    Layout.preferredHeight: parent.height * 0.75
                    Layout.alignment: Qt.AlignTop
                }
                Button
                {
                    id: generateButton
                    text: "Generate random list"
                    anchors.top: foundFiles.bottom
                    anchors.topMargin: 20
                    Layout.alignment: Qt.AlignHCenter
                    Layout.margins: 50

                    signal generateRandomListSignal()

                    onClicked: generateRandomListSignal()
                }
                width: parent.width * 0.4
                height: parent.height
            }


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
                    width: 100
                }
                id: selectedFiles
                model: foundFilesModel
                anchors.right: parent.right
                width: parent.width * 0.4
                height: parent.height * 0.75
            }
        }

        Page {
            TextField {
                text: filesViewModel.userName
                placeholderText: qsTr("User lel")
                anchors.centerIn: parent

                onTextChanged: backend.userName = text
            }
            ListView {
                width: 100; height: 100

                model: myModel
                delegate: Rectangle {
                    height: 25
                    width: 100
                    Text { text: modelData }
                }
            }
        }
    }

    footer: TabBar {
        id: tabBar
        currentIndex: swipeView.currentIndex
        TabButton {
            text: qsTr("First")
        }
        TabButton {
            text: qsTr("Second")
        }
    }
}
