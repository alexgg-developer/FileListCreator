#include "FileListing.h"
#include <queue>
#include <iostream>

FileListing::FileListing()
{

}

void FileListing::listFiles(QString const & path)
{
    m_rootPath = path;
    QDir dir(QDir::toNativeSeparators(path));
    std::queue<QFileInfoList> fileInfoLists;
    QStringList filters;
    if(!dir.exists()) {
        return;
    }
    fileInfoLists.push(dir.entryInfoList(filters));
    //foldersWatched.append(path);

    while(!fileInfoLists.empty()) {
        QFileInfoList fileInfoList = fileInfoLists.front();
        fileInfoLists.pop();
        for(QFileInfo const & fileInfo : fileInfoList) {
            if(fileInfo.isDir()) {
                //std::cout << fileInfo.fileName().toStdString() << std::endl;
                if(fileInfo.fileName() != "." && fileInfo.fileName() != ".." ) {
                    QDir newDir(fileInfo.absoluteFilePath());
                    fileInfoLists.push(newDir.entryInfoList(filters));
                }
            }
            else {
                m_filesFound.push_back(fileInfo);
            }
        }
    }
}
