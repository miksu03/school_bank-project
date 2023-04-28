#include "databaseurl.h"
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>

QUrl databaseUrl::database = QUrl("https://localhost");

databaseUrl::databaseUrl(QObject *parent)
    : QObject{parent}
{

}

bool databaseUrl::passwordChecer(QString password, QString hashed)
{
    QUrl db = database;
    db.setPath("/checker");
    QNetworkRequest request(db);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["password"] = password;
    json["hash"] = hashed;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = m_manager.post(request, data);
    QEventLoop loop;
    QObject::connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        QString read = QString(reply->readAll());
        qDebug() << read;
        if (read == "true") {
            return true;
        } else {
            qDebug() << read;
            return false;
        }
    } else {
        qDebug() << "Error: " << reply->errorString();
        return false;
    }
}
