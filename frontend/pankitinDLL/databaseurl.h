#ifndef DATABASEURL_H
#define DATABASEURL_H
#include <QtNetwork/QNetworkAccessManager>
#include "pankitinDLL_global.h"


class PANKITINDLL_EXPORT databaseUrl:public QObject
{
    Q_OBJECT
public:
    databaseUrl(QObject *parent = nullptr);
    static QUrl database;
    bool passwordChecer(QString password, QString hashed);
private:
        QNetworkAccessManager m_manager;
};

#endif // DATABASEURL_H
