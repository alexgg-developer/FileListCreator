import QtQuick 2.7
import QtQuick.Controls 2.0
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

    SwipeView {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex



        Page {
            Label {
                text: qsTr("Second 2")
                anchors.centerIn: parent
            }
        }

        Page {
            TextField {
                text: backend.userName
                placeholderText: qsTr("User lel")
                anchors.centerIn: parent

                onTextChanged: backend.userName = text
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
