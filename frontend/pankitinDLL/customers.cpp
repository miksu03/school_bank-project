#include "customers.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Customers::Customers(QObject *parent)
    : QObject(parent)
{
}
void Customers::getAll()
{
    databaseUrl.setPath("/customer");
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
    databaseUrl.setPath("/customer");
}

void Customers::getById(int id)
{
    databaseUrl.setPath("/customer" + QString::number(id));
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
    databaseUrl.setPath("/customer");
}

void Customers::add(QString name, QString surName, int id)
{
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["name"] = name;
    json["surName"] = surName;
    json["idCustomer"] = id;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = m_manager.post(request, data);
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
}

void Customers::update(int id, QString name, QString surName)
{
    databaseUrl.setPath("/customer" + QString::number(id));
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["name"] = name;
    json["surName"] = surName;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QNetworkReply *reply = m_manager.put(request, data);
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
    databaseUrl.setPath("/customer");
}

void Customers::deleteById(int id)
{
    databaseUrl.setPath("/account" + QString::number(id));
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    QNetworkReply *reply = m_manager.deleteResource(request);
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
    databaseUrl.setPath("/customer");
}
