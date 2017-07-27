#include "FilesViewModel.h"
#include "QtGlobals.h"

#include <queue>
#include <iostream>
#include <random>

#include <QDate>

using namespace std;

FilesViewModel::FilesViewModel(QObject *parent)
{
    QtGlobals::getInstance()->engine->rootContext()->setContextProperty("foundFilesModel", &m_foundFilesModel);
    QtGlobals::getInstance()->engine->rootContext()->setContextProperty("selectedFilesModel", &m_selectedFilesModel);
    //listFiles(QString("TestingFolder"));
    //listFiles(QString("TestingFolder"));
}

void FilesViewModel::onSearchFilesPressed(QString const & path, QString const & extensions)
{
    m_foundFilesModel.emptyList();
    listFiles(path, extensions);
}

void FilesViewModel::listFiles(QString const & path, QString const & extensions)
{
    const int MIN_FILE_SIZE = 1000 * 1000; //1MB
    QDir dir(QDir::toNativeSeparators(path));
    std::queue<QFileInfoList> fileInfoLists;
    QStringList filters, extensionList;
    if(extensions != "") {
        extensionList = extensions.split(';');
    }
    //filters << "*.pdf";
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
                QString suffix = fileInfo.completeSuffix();
                if(extensionList.empty() || extensionList.contains(suffix, Qt::CaseInsensitive)) {
                    if(fileInfo.size() > MIN_FILE_SIZE) {
                        m_foundFilesModel.addFile(fileInfo);
                    }
                }
            }
        }
    }
}

QString FilesViewModel::userName()
{
    return "m_userName";
}


void FilesViewModel::onGenerateListPressed(int size)
{
    cout << "Pressed" << size << endl;
    m_selectedFilesModel.emptyList();
    makeRandomSelection(size * 1024);
}

void FilesViewModel::makeRandomSelection(int maxSize)
{
    std::random_device r;
    std::default_random_engine e1(r());
    int rows = m_foundFilesModel.rowCount();
    std::uniform_int_distribution<int> uniform_dist(0, rows - 1);
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
            if(currentSize + fileSize < maxSize) {
                m_selectedFilesModel.addFile(fileSelected);
                currentSize += fileSize;
            }
            ++rowsChecked;
        }
        ++i;
    }
}

void FilesViewModel::onCopyFilesPressed()
{
    QString path = "";
    if(createDir(path)) {
        copyFiles(path);
    }
}

bool FilesViewModel::createDir(QString & path) const
{
    QString originalPath;
    originalPath = path = QDate::currentDate().toString("files_dd_MM_yyyy");
    QDir dir(QDir::toNativeSeparators(path));
    int i = 1;
    while(dir.exists()) {
        path = originalPath + QString("_") + QString::number(i);
        dir.setPath(path);
        ++i;
    }
    QDir root = QDir::currentPath();
    return root.mkdir(path);
}

void FilesViewModel::copyFiles(QString const & path) const
{
    int rowCount = m_selectedFilesModel.rowCount();
    for(int i = 0; i < rowCount; ++i) {
        QFileInfo const &file = m_selectedFilesModel.getRow(i);
        QFile::copy(file.absoluteFilePath(), path + QString("/") + file.fileName());
    }
}
