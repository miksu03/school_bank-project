#include "cardreaderdll.h"
#include <QDebug>
#include <QList>

CardReaderDLL::CardReaderDLL(QObject* parent) : QObject(parent)
{
    m_serial = new QSerialPort("COM5", this); // Use port 7
    if(m_serial->open(QIODevice::ReadWrite)) {
        connect(m_serial, &QSerialPort::readyRead, this, &CardReaderDLL::onDataReady);
    } else {
        qDebug() << "Failed to open serial port: " << m_serial->errorString();
    }
}
