#ifndef CARDREADERDLL_H
#define CARDREADERDLL_H

#include "cardReaderDLL_global.h"
#include <QObject>
#include <QDebug>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>

class CARDREADERDLL_EXPORT CardReaderDLL: public QObject {
    Q_OBJECT

public:
    explicit CardReaderDLL(QObject* parent = nullptr);
signals:
    void cardDetected(const QString& cardData);

private slots:
    void onDataReady() {
        QByteArray data = m_serial->readAll();
        QString cardData = QString(data);
        cardData.remove(0,3);
        cardData.chop(3);
        emit cardDetected(cardData);
    }
private:
    QSerialPort* m_serial;
};

#endif // CARDREADERDLL_H
