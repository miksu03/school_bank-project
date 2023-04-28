#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include "pankitinDLL_global.h"
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QJsonArray>
#include "databaseurl.h"

class PANKITINDLL_EXPORT Customers : public QObject
{
    Q_OBJECT
public:
    explicit Customers(QObject *parent = nullptr);

signals:
    void dataReceived(QJsonArray data);

public slots:
    void getAll();
    void getById(int id);
    void update(int id, QString name, QString surName);
    void add(QString name, QString surName, int id);
    void deleteById(int id);

private:
    databaseUrl du;
    QNetworkAccessManager m_manager;
    QUrl databaseUrl = du.database;
};

#endif // CUSTOMERS_H
