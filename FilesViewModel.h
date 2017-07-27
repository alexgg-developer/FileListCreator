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
    void makeRandomSelection(int maxSize);
    void listFiles(QString const & path, QString const & extensions);
    bool createDir(QString & path) const;
    void copyFiles(QString const & path) const;
signals:
public slots:
    void onGenerateListPressed(int size);
    void onSearchFilesPressed(QString const & path, QString const & extensions);
    void onCopyFilesPressed();
};

#endif // FILESVIEWMODEL_H
