#ifndef FILESVIEWMODEL_H
#define FILESVIEWMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "FileModel.h"

class FilesViewModel
{
public:
    FilesViewModel(QQmlApplicationEngine& engine);
    void updateModels();
    void listFiles(QString const & path);
private:
    QQmlApplicationEngine& m_engine;
    FileModel m_foundFilesModel;
};

#endif // FILESVIEWMODEL_H
