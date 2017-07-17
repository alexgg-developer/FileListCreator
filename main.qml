import QtQuick 2.7
import QtQuick.Controls 1.4
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import Custom.Backend 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
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
                    role: "title"
                    title: "Title"
                    width: 100
                }
                TableViewColumn {
                    role: "author"
                    title: "Author"
                    width: 200
                }
                model: myModel
                anchors.centerIn: parent
                anchors.fill: parent
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
