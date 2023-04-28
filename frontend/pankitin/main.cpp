#include "mainwindow.h"
#include <QApplication>
#include "dialogcardpayment.h"
#include <QObject>
#include <../cardReaderDLL/cardReaderDLL.h>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    CardReaderDLL cardReader;
    DialogCardPayment cp;
    // Connect the cardReader object's cardDetected signal to a lambda function
    // that opens the DialogCardPayment and sets the text of a QLabel widget to show what card is used
    QObject::connect(&cardReader, &CardReaderDLL::cardDetected, [&cp](const QString& cardData) {
        cp.show();
        cp.findChild<QLabel*>("Label1")->setText(QString(cardData));
    });
    w.show();
    return a.exec();
}
