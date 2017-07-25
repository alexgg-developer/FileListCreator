#ifndef FILESVIEWMODEL_H
#define FILESVIEWMODEL_H

#include <QObject>
#include <QAbstractListModel>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "FileModel.h"

class FilesViewModel: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString userName READ userName)
public:
    explicit FilesViewModel(QObject *parent = nullptr);
    void updateModels();
    QString userName();
private:
    FileModel m_foundFilesModel, m_selectedFilesModel;
    void makeRandomSelection();
signals:
public slots:
    void onGenerateListPressed();
    void listFiles(QString const & path);
};

#endif // FILESVIEWMODEL_H
