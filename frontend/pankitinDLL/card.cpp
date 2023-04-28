#include "card.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Card::Card(QObject *parent)
    : QObject{parent}
{

}
void Card::getAll()
{
    databaseUrl.setPath("/card");
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
    databaseUrl.setPath("/card");
}

void Card::getById(int id)
{
    databaseUrl.setPath("/card" + QString::number(id));
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
    databaseUrl.setPath("/card");
}

void Card::add(QString cardNumber, QString password, QString pinCode, QString Account_idCard, QString Customer_idCustomer, int id)
{
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["cardNumber"] = cardNumber;
    json["password"] = password;
    json["pinCode"] = pinCode;
    json["Account_idCard"] = Account_idCard;
    json["Customer_idCustomer"] = Customer_idCustomer;
    json["idCard"] = id;
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

void Card::update(int id, QString cardNumber, QString password, QString pinCode, QString Account_idCard, QString Customer_idCustomer)
{
    databaseUrl.setPath("/card" + QString::number(id));
    QNetworkRequest request(databaseUrl);
    request.setRawHeader("ngrok-skip-browser-warning", "true");
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    QJsonObject json;
    json["cardNumber"] = cardNumber;
    json["password"] = password;
    json["pinCode"] = pinCode;
    json["Account_idCard"] = Account_idCard;
    json["Customer_idCustomer"] = Customer_idCustomer;
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
    databaseUrl.setPath("/card");
}

void Card::deleteById(int id)
{
    databaseUrl.setPath("/card" + QString::number(id));
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
    databaseUrl.setPath("/card");
}
