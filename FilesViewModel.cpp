#include "FilesViewModel.h"
#include "QtGlobals.h"

#include <queue>
#include <iostream>
#include <random>

using namespace std;

FilesViewModel::FilesViewModel(QObject *parent)
{
    QtGlobals::getInstance()->engine->rootContext()->setContextProperty("foundFilesModel", &m_foundFilesModel);
    QtGlobals::getInstance()->engine->rootContext()->setContextProperty("selectedFilesModel", &m_selectedFilesModel);
    //listFiles(QString("TestingFolder"));
    //listFiles(QString("TestingFolder"));
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

//void FilesViewModel::updateModels()
//{
//    QtGlobals::engine->rootContext()->setContextProperty("foundFilesModel", &m_foundFilesModel);
//}


QString FilesViewModel::userName()
{
    return "m_userName";
}


void FilesViewModel::onGenerateListPressed()
{
    cout << "Pressed" << endl;
    m_selectedFilesModel.emptyList();
    makeRandomSelection();
}

void FilesViewModel::makeRandomSelection()
{
    std::random_device r;
    std::default_random_engine e1(r());
    int rows = m_foundFilesModel.rowCount();
    std::uniform_int_distribution<int> uniform_dist(0, rows - 1);
    int max_size = 1000;
    int i = 0;
    std::vector<int> selectedRows(rows, 0);
    int currentSize = 0;
    int maxIterations = rows * 100;
    int rowsChecked = 0;
    while(rowsChecked < rows && i < maxIterations) {
        int row = uniform_dist(e1);
        //cout << mean << endl;
        if(selectedRows[row] == 0) {
            const QFileInfo& fileSelected = m_foundFilesModel.getRow(row);
            int fileSize = fileSelected.size() / 1000;
            selectedRows[row] = 1;
            if(currentSize + fileSize < max_size) {
                m_selectedFilesModel.addFile(fileSelected);
                currentSize += fileSize;
                cout << i << ":" << currentSize << endl;
            }
            ++rowsChecked;
        }
        ++i;
    }
}

