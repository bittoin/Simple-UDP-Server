#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include <QObject>
#include <QDateTime>
#include <QHash>
#include <QStringList>
#include <QDir>
#include <QDebug>

#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void triggerAccData(QString);
    void serverStarted();
    void serverFinished();

public slots:
    void readInfo();

private slots:
    void on_startServer_clicked();
    void on_closeServer_clicked();

    void startDataCollect();
    void collectData(QString);
    void finishDataCollect();
private:
    Ui::MainWindow *ui;
    QUdpSocket socket;

    QtCSV::StringData csvStateData;
    QStringList currentDataCollection;
};
#endif // MAINWINDOW_H
