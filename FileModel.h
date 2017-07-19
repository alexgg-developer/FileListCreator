#ifndef FILEMODEL_H
#define FILEMODEL_H

#include <QObject>
#include <QDir>
#include <QString>
#include <QAbstractListModel>

class FileModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum FileModelRoles {
        FileName = Qt::UserRole + 1,
        Size,
        Path
    };

    explicit FileModel(QObject *parent = nullptr);
    void addFile(const QFileInfo &file);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

protected:
    QHash<int, QByteArray> roleNames() const;

private:
    QList<QFileInfo> m_filesFound;
    QString formatSize(qint64 size) const;

signals:

public slots:
};

#endif // FILEMODEL_H
