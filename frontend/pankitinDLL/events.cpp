#include "events.h"

Events::Events(QObject *parent)
    : QObject{parent}
{
}
void Events::getAll()
{
    databaseUrl.setPath("/events");
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            //QByteArray bytedata = reply->readAll();
            QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
            emit dataReceived(data);
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
    });
    databaseUrl.setPath("/events");
}

void Events::getById(int id)
{
    databaseUrl.setPath("/events" + QString::number(id));
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            //QByteArray data = reply->readAll();
            QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
            emit dataReceived(data);
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
    });
    databaseUrl.setPath("/events");
}

void Events::add(double value, int idAccount, QString date, int id)
{
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["value"] = value;
    json["idAccount"] = idAccount;
    json["date"] = date;
    json["idEvent"] = id;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = m_manager.post(request, data);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            //QByteArray data = reply->readAll();
            QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
            emit dataReceived(data);
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
    });
}

void Events::update(int id, double value, int idAccount, QString date)
{
    databaseUrl.setPath("/events" + QString::number(id));
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["value"] = value;
    json["idAccount"] = idAccount;
    json["date"] = date;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = m_manager.put(request, data);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            //QByteArray data = reply->readAll();
            QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
            emit dataReceived(data);
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
    });
    databaseUrl.setPath("/events");
}

void Events::deleteById(int id)
{
    databaseUrl.setPath("/events" + QString::number(id));
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    QNetworkReply *reply = m_manager.deleteResource(request);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            //QByteArray data = reply->readAll();
            QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
            emit dataReceived(data);
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
    });
    databaseUrl.setPath("/events");
}
