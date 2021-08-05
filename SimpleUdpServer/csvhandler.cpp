#include "csvhandler.h"

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
    qInfo() << "Saving data to: " << QDir::currentPath();
    //QDateTime fileCreationDateTime;
    //QString nameComplement = fileCreationDateTime.currentDateTime().toString("h:m:s ap");
    //QString nameComplement = ui->fileNameInput->toPlainText();
    QString nameComplement = fileName;
    QString filePath = QDir::currentPath() + "/tello-data-" + nameComplement + ".csv";
    QtCSV::Writer::write(filePath, csvStateData);

    csvStateData.clear();
}
