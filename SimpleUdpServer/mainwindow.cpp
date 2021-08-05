#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    connect(this, &MainWindow::serverStarted,
            this, &MainWindow::startDataCollect);

    connect(this, &MainWindow::triggerAccData,
            this, &MainWindow::collectData);

    connect(this, &MainWindow::serverFinished,
            this, &MainWindow::finishDataCollect);
}

MainWindow::~MainWindow() {
    socket.close();
    delete ui;
}

void MainWindow::readInfo() {
    while (socket.hasPendingDatagrams()){
        QNetworkDatagram datagram = socket.receiveDatagram();
        QByteArray data = datagram.data();
        emit triggerAccData(data);
        //qInfo() << "Incoming data: " << data;
    }
}

void MainWindow::on_startServer_clicked() {
    if (!socket.bind(QHostAddress("0.0.0.0"), 6666)) {
        qInfo() << socket.errorString();
        return;
    }else{
        connect(&socket, &QUdpSocket::readyRead,
                this, &MainWindow::readInfo);
        emit serverStarted();
        ui->serverStatus->setStyleSheet("background-color: rgb(0, 255, 0);");
        qInfo() << "Socket created!";
    }
}

void MainWindow::on_closeServer_clicked() {
    disconnect(&socket, &QUdpSocket::readyRead,
            this, &MainWindow::readInfo);
    emit serverFinished();
    ui->serverStatus->setStyleSheet("background-color: rgb(255, 0, 0);");
    socket.close();
}

void MainWindow::startDataCollect() {
    csvStateData.clear();
    currentDataCollection.clear();

    currentDataCollection << "acc_x" << "acc_y" << "acc_z";
    csvStateData.addRow(currentDataCollection);
    currentDataCollection.clear();
}

void MainWindow::collectData(QString accData) {
    QStringList accList = accData.split(",");
    if (accList.length() != 3){
        qInfo() << "Incorrect information coming!";
        return;
    }

    currentDataCollection << accList[0] << accList[1] << accList[2];
    csvStateData.addRow(currentDataCollection);
    currentDataCollection.clear();
}

void MainWindow::finishDataCollect() {
    qInfo() << "Saving data to: " << QDir::currentPath();
    //QDateTime fileCreationDateTime;
    //QString nameComplement = fileCreationDateTime.currentDateTime().toString("h:m:s ap");
    QString nameComplement = ui->fileNameInput->toPlainText();
    QString filePath = QDir::currentPath() + "/tello-data-" + nameComplement + ".csv";
    QtCSV::Writer::write(filePath, csvStateData);

    csvStateData.clear();
}
