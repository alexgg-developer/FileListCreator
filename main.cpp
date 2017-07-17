#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QQmlContext>

#include "BackEnd.h"
#include "FileListing.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    qmlRegisterType<BackEnd>("Custom.Backend", 1, 0, "BackEnd");


    FileListing fileListing;
    //fileListing.listFiles(QString("C:/Users/Shuttle/Documents/Pruebas/SecondTest/TestingFolder"));
    fileListing.listFiles(QString("TestingFolder"));

    QStringList dataList;
    for(int i = 0; i < 100000; ++i) {
        dataList.append(QString::number(i));
    }


    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("myModel", QVariant::fromValue(dataList));
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
