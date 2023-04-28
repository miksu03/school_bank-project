#ifndef EVENTS_H
#define EVENTS_H

#include "pankitinDLL_global.h"
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include "databaseurl.h"

class PANKITINDLL_EXPORT Events : public QObject
{
    Q_OBJECT
public:
    explicit Events(QObject *parent = nullptr);

signals:
    void dataReceived(QJsonArray document);

public slots:
    void getAll();
    void getById(int id);
    void update(int id, double value, int idAccount, QString date);
    void add(double value, int idAccount, QString date, int id);
    void deleteById(int id);

private:
    databaseUrl du;
    QNetworkAccessManager m_manager;
    QUrl databaseUrl = du.database;
};

#endif // EVENTS_H
