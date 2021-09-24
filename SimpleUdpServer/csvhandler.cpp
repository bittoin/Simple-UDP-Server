#include "csvhandler.h"
#include <QRandomGenerator>

CsvHandler::CsvHandler(QObject *parent) : QObject(parent) {
    dirPath = QDir::currentPath();
}

CsvHandler::~CsvHandler() {

}

void CsvHandler::startDataCollect() {
    csvStateData.clear();
    currentDataCollection.clear();

    currentDataCollection << "acc_x" << "acc_y" << "acc_z";
    csvStateData.addRow(currentDataCollection);
    currentDataCollection.clear();
}

void CsvHandler::collectData(QString accData) {
    QStringList accList = accData.split(",");
    if (accList.length() != 3){
        qInfo() << "Incorrect information coming!";
        return;
    }

    currentDataCollection << accList[0] << accList[1] << accList[2];
    csvStateData.addRow(currentDataCollection);
    currentDataCollection.clear();
}

void CsvHandler::finishDataCollect(QString fileName) {
    QString filePath = "";

    if (fileName.length() == 0){
        qInfo() << "Campo vazio!";
        quint32 randomValue = QRandomGenerator::global()->bounded(0, 99999);

        filePath = dirPath + "/data-" + QString::number(randomValue) + ".csv";

    } else{
        filePath = dirPath + "/data-" + fileName + ".csv";
    }

    QtCSV::Writer::write(filePath, csvStateData);

    //qInfo() << "Saving data to: " << dirPath;
    emit savedDataPath(dirPath);

    csvStateData.clear();
}

void CsvHandler::setDirPath(QString path) {
    dirPath = path;
}
