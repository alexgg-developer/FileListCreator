#include "FilesViewModel.h"
#include <queue>

FilesViewModel::FilesViewModel(QQmlApplicationEngine& engine):
    m_engine(engine)
{

}

void FilesViewModel::listFiles(QString const & path)
{
    QDir dir(QDir::toNativeSeparators(path));
    std::queue<QFileInfoList> fileInfoLists;
    QStringList filters;
    if(!dir.exists()) {
        return;
    }
    fileInfoLists.push(dir.entryInfoList(filters));
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
                m_foundFilesModel.addFile(fileInfo);
            }
        }
    }
}

void FilesViewModel::updateModels()
{
    m_engine.rootContext()->setContextProperty("foundFilesModel", &m_foundFilesModel);
}
