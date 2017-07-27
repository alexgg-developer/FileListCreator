#include "FileModel.h"

FileModel::FileModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void FileModel::addFile(const QFileInfo &file)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_fileInfoList << file;
    endInsertRows();
}

int FileModel::rowCount(const QModelIndex & parent) const {
    Q_UNUSED(parent);
    return m_fileInfoList.count();
}

QVariant FileModel::data(const QModelIndex & index, int role) const {
    if (index.row() < 0 || index.row() >= m_fileInfoList.count())
        return QVariant();

    const QFileInfo &file= m_fileInfoList[index.row()];
    if (role == FileName)
        return file.fileName();
    else if (role == Size)
        return formatSize(file.size());
    else if (role == Path)
        return file.absoluteFilePath();
    return QVariant();
}

const QFileInfo& FileModel::getRow(int row) const
{
    return m_fileInfoList[row];
}


QString FileModel::formatSize(qint64 size) const {
    double formattedSize = size;
    int nameSelected = 0;
    QList<QString> nameBytes = {"B", "KB", "MB", "GB", "TB"};
    while(formattedSize > 1000.0) {
        formattedSize /= 1000.0;
        ++nameSelected;
    }
    return QString::number(formattedSize, 'f', 2) + nameBytes[nameSelected];
}

QHash<int, QByteArray> FileModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FileName] = "FileName";
    roles[Size] = "Size";
    roles[Path] = "Path";
    return roles;
}

void FileModel::emptyList()
{
    beginResetModel();
    m_fileInfoList.clear();
    endResetModel();
}
