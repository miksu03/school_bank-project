#ifndef DIALOGCARDPAYMENT_H
#define DIALOGCARDPAYMENT_H

#include <QDialog>
#include "databasemanager.h"
#include <../pankitinDLL/databaseurl.h>

namespace Ui {
class DialogCardPayment;
}

class DialogCardPayment : public QDialog
{
    Q_OBJECT
public:
    explicit DialogCardPayment(QWidget *parent = nullptr);
    ~DialogCardPayment();
    Ui::DialogCardPayment *ui;
private:
    DatabaseManager dm;
    databaseUrl du;
    QString getCurrentDateTime()
    {
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString formattedDateTime = currentDateTime.toString("yyyy:MM:dd HH:mm:ss");
        return formattedDateTime;
    }
    bool okClikked = false;
    bool credit = false;
};

#endif // DIALOGCARDPAYMENT_H
