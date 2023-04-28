#include "account.h"

Account::Account(QObject *parent)
    : QObject{parent}
{

}/*
void Account::getAll()
{
    databaseUrl.setPath("/account");
    QNetworkRequest request(databaseUrl);
    QJsonObject json;
    json["ngrok-skip-browser-warning"] = 0;
    QJsonDocument doc(json);
    QByteArray data = doc.toJson();
    QByteArray verb = "GET";
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QNetworkReply *reply = m_manager.sendCustomRequest(request, verb, data);
    connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray data = reply->readAll();
            QJsonArray data = QJsonDocument::fromJson(reply->readAll()).array();
            qDebug() << data;
            emit dataReceived(data);
        } else {
            qDebug() << "Error: " << reply->errorString();
        }
        reply->deleteLater();
    });
    databaseUrl.setPath("/account");
}*/
void Account::getAll()
{
    databaseUrl.setPath("/account");
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
    databaseUrl.setPath("/account");
}

void Account::getById(int id)
{
    databaseUrl.setPath("/account" + QString::number(id));
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
    databaseUrl.setPath("/account");
}

void Account::add(double value, double maxCredit, int idCard, int idCustomer, int id)
{
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["value"] = value;
    json["maxCredit"] = maxCredit;
    json["idCard"] = idCard;
    json["idCustomer"] = idCustomer;
    json["id"]=id;
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

void Account::update(int id, double value, double maxCredit, int idCard, int idCustomer)
{
    databaseUrl.setPath("/account" + QString::number(id));
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["value"] = value;
    json["maxCredit"] = maxCredit;
    json["idCard"] = idCard;
    json["idCustomer"] = idCustomer;
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
    databaseUrl.setPath("/account");
}

void Account::deleteById(int id)
{
    databaseUrl.setPath("/account" + QString::number(id));
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
    databaseUrl.setPath("/account");
}
