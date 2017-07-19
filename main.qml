import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Custom.Backend 1.0

ApplicationWindow {
    visible: true
    width: 1440
    height: 810
    title: qsTr("Hello World")

    BackEnd {
            id: backend
        }

    ListModel {
        id: libraryModel
        ListElement {
            title: "A Masterpiece"
            author: "Gabriel"
        }
        ListElement {
            title: "Brilliance"
            author: "Jens"
        }
        ListElement {
            title: "Outstanding"
            author: "Frederik"
        }
    }

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex



        Page {
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
                    width: 500
                }
                id: foundFiles
                model: foundFilesModel
                anchors.left: parent.left
                width: parent.width * 0.4
                height: parent.height * 0.75
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
                model: animalModel
                anchors.right: parent.right
                width: parent.width * 0.4
                height: parent.height * 0.75
            }
        }

        Page {
//            TextField {
//                text: backend.userName
//                placeholderText: qsTr("User lel")
//                anchors.centerIn: parent

//                onTextChanged: backend.userName = text
//            }
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
