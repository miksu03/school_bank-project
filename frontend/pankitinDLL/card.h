#ifndef CARD_H
#define CARD_H
#include "pankitinDLL_global.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <QJsonArray>
#include "databaseurl.h"

class PANKITINDLL_EXPORT Card : public QObject
{
    Q_OBJECT
public:
    explicit Card(QObject *parent = nullptr);

signals:
    void dataReceived(QJsonArray data);

public slots:
    void getAll();
    void getById(int id);
    void update(int id, QString cardNumber, QString password, QString pinCode, QString Account_idCard, QString Customer_idCustomer);
    void add(QString cardNumber, QString password, QString pinCode, QString Account_idCard, QString Customer_idCustomer, int id);
    void deleteById(int id);

private:
    databaseUrl du;
    QNetworkAccessManager m_manager;
    QUrl databaseUrl = du.database;
};

#endif // CARD_H
