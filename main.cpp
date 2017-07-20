#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "BackEnd.h"
#include "FileListing.h"
#include "FilesViewModel.h"
#include "QtGlobals.h"

#include <iostream>


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    //qmlRegisterType<BackEnd>("Custom.Backend", 1, 0, "BackEnd");
    qmlRegisterType<FilesViewModel>("Custom.FilesViewModel", 1, 0, "FilesViewModel");


//    FileListing fileListing;
//    //fileListing.listFiles(QString("C:/Users/Shuttle/Documents/Pruebas/SecondTest/TestingFolder"));
//    fileListing.listFiles(QString("TestingFolder"));

    QStringList dataList;
    for(int i = 0; i < 100000; ++i) {
        dataList.append(QString::number(i));
    }


    QQmlApplicationEngine engine;
    QtGlobals::getInstance()->engine = &engine;
    //QtGlobals::engine = &engine;
//    FilesViewModel filesViewModel(engine);
//    filesViewModel.listFiles(QString("TestingFolder"));
//    filesViewModel.updateModels();


    engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(dataList));
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    QObject *button = engine.rootContext()->contextObject()->findChild<QObject*>("generateButton");
    if (button){
        std::cout << "lel" << std::endl;
    }


    return app.exec();
}
