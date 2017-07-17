#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "BackEnd.h"
#include "FileListing.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);


    qmlRegisterType<BackEnd>("Custom.Backend", 1, 0, "BackEnd");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    FileListing fileListing;
    //fileListing.listFiles(QString("C:/Users/Shuttle/Documents/Pruebas/SecondTest/TestingFolder"));
    fileListing.listFiles(QString("TestingFolder"));
    return app.exec();
}
