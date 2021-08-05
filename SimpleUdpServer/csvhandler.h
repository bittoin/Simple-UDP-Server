#ifndef CSVHANDLER_H
#define CSVHANDLER_H

#include <QObject>
#include <QDir>
#include <QDebug>

#include "qtcsv/stringdata.h"
#include "qtcsv/reader.h"
#include "qtcsv/writer.h"

class CsvHandler : public QObject
{
    Q_OBJECT
public:
    explicit CsvHandler(QObject *parent = nullptr);
    ~CsvHandler();

signals:

public slots:
    void startDataCollect();
    void collectData(QString);
    void finishDataCollect(QString);

private:
    QtCSV::StringData csvStateData;
    QStringList currentDataCollection;
};

#endif // CSVHANDLER_H
