#ifndef FILELISTING_H
#define FILELISTING_H

#include <QString>
#include <vector>
#include <QDir>

class FileListing
{
public:
    FileListing();
    void listFiles(QString const & path);
private:
    std::vector<QFileInfo> m_filesFound;
    QString m_rootPath;
};

#endif // FILELISTING_H
