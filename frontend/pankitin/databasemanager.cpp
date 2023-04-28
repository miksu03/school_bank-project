#include "databasemanager.h"


DatabaseManager::DatabaseManager()
{
    QObject::connect(&car, &Card::dataReceived, this, &DatabaseManager::receiveCards);
    QObject::connect(&eve, &Events::dataReceived, this, &DatabaseManager::receiveEvents);
    QObject::connect(&cus, &Customers::dataReceived, this, &DatabaseManager::receiveCustomers);
    QObject::connect(&acc, &Account::dataReceived, this, &DatabaseManager::receiveAccounts);
    car.getAll();
    eve.getAll();
    cus.getAll();
    acc.getAll();
}

void DatabaseManager::add(EventObject eveObject, int id)
{
    eve.add(eveObject.value, eveObject.idAccount, eveObject.date, id);
}

void DatabaseManager::update(AccountObject account)
{
    acc.update(account.id, account.value, account.maxCredit, account.idCard, account.idCustomer);
}

//list updater and generater
void DatabaseManager::receiveCards(const QJsonArray data)
{
    for (const auto& obj : data)
    {
        const auto readData = obj.toObject();
        CardObject newCard;
        newCard.idCard = readData["idCard"].toInt();
        newCard.password = readData["password"].toString();
        newCard.CardNumber = readData["cardNumber"].toString();
        newCard.Customer_idCustomer = readData["Customer_idCustomer"].toInt();
        newCard.Account_id = readData["Account_idCard"].toInt();
        newCard.pinCode = readData["pinCode"].toString();
        listOfCards.insert(newCard.idCard, newCard);
    }
}

//list updater and generater
void DatabaseManager::receiveEvents(const QJsonArray data)
{
    for (const auto& obj : data)
    {
        const auto readData = obj.toObject();
        EventObject newEvent;
        newEvent.id = readData["idEvent"].toInt();
        newEvent.idAccount = readData["idAccount"].toInt();
        newEvent.value = readData["value"].toDouble();
        newEvent.date = readData["date"].toString();
        listOfEvents.insert(newEvent.id, newEvent);
    }
}

//list updater and generater
void DatabaseManager::receiveAccounts(const QJsonArray data)
{
    for (const auto& obj : data)
    {
        const auto readData = obj.toObject();
        AccountObject newAccount;
        newAccount.id = readData["id"].toInt();
        newAccount.maxCredit = readData["maxCredit"].toDouble();
        newAccount.value = readData["value"].toDouble();
        newAccount.idCard = readData["idCard"].toInt();
        newAccount.idCustomer = readData["idCustomer"].toInt();
        listOfAccounts.insert(newAccount.id, newAccount);
    }
}

//list updater and generater
void DatabaseManager::receiveCustomers(const QJsonArray data)
{
    for (const auto& obj : data)
    {
        const auto readData = obj.toObject();
        CustomerObject newCustomer;
        newCustomer.idCustomer = readData["idCustomer"].toInt();
        newCustomer.name = readData["name"].toString();
        newCustomer.surName = readData["surName"].toString();
    }
}

