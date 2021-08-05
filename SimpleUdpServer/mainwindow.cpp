#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QNetworkInterface>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    connect(this, &MainWindow::serverStarted,
            &csv, &CsvHandler::startDataCollect);

    connect(this, &MainWindow::triggerAccData,
            &csv, &CsvHandler::collectData);

    connect(this, &MainWindow::serverFinished,
            &csv, &CsvHandler::finishDataCollect);

    createIpList();
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
    }
}

void MainWindow::on_startServer_clicked() {
    int portNumber = ui->portNumber->value();
    if (!socket.bind(QHostAddress("0.0.0.0"), portNumber)) {
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
    QString fileName = ui->fileNameInput->toPlainText();
    emit serverFinished(fileName);
    ui->serverStatus->setStyleSheet("background-color: rgb(255, 0, 0);");
    socket.close();
}

void MainWindow::createIpList() {
    const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
    //for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
    for (auto &address: QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost)
            ui->ipList->addItem(address.toString());
    }
}
