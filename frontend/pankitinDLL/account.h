#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "pankitinDLL_global.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "databaseurl.h"

class PANKITINDLL_EXPORT Account : public QObject
{
    Q_OBJECT
public:
    explicit Account(QObject *parent = nullptr);

signals:
    void dataReceived(QJsonArray document);

public slots:
    void getAll();
    void getById(int id);
    void update(int id, double value, double maxCredit, int idCard, int idCustomer);
    void add(double value, double maxCredit, int idCard, int idCustomer, int id);
    void deleteById(int id);

private:
    databaseUrl du;
    QNetworkAccessManager m_manager;
    QUrl databaseUrl = du.database;
};

#endif // ACCOUNT_H
