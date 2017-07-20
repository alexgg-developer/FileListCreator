#ifndef QTGLOBALS_H
#define QTGLOBALS_H

#include <QQmlApplicationEngine>

class QtGlobals
{
public:
    QQmlApplicationEngine* engine;
    static QtGlobals* getInstance();
private:
    static QtGlobals *single;
    QtGlobals() { }
};

#endif // QTGLOBALS_H
