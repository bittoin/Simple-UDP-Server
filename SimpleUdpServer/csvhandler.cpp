#include "csvhandler.h"
#include <QRandomGenerator>

CsvHandler::CsvHandler(QObject *parent) : QObject(parent) {

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
    qInfo() << "Saving data to: " << QDir::currentPath();

    if (fileName.length() == 0){
        qInfo() << "Campo vazio!";
        quint32 randomValue = QRandomGenerator::global()->bounded(0, 99999);
        filePath = QDir::currentPath() + "/data-" + QString::number(randomValue) + ".csv";
    } else{
        filePath = QDir::currentPath() + "/tello-data-" + fileName + ".csv";
    }

    QtCSV::Writer::write(filePath, csvStateData);
    csvStateData.clear();
}
