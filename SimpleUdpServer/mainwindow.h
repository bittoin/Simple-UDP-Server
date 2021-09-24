#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkDatagram>

#include <QObject>
#include <QDateTime>
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <csvhandler.h>


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
    void serverFinished(QString);
    void changeFileSavePath(QString);

public slots:
    void readInfo();

private slots:
    void on_startServer_clicked();
    void on_closeServer_clicked();
    void createIpList();
    void updateSavedDataPath(QString);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButton_clicked();

    void on_button_file_path_clicked();

private:
    Ui::MainWindow *ui;
    QUdpSocket socket;

    CsvHandler csv;
    QTimer timer;

    QString currentDirPath;

    const int DEFAULT_SEC = 1000;
};
#endif // MAINWINDOW_H
